import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///news.db")

@app.route("/")
def index():


    return render_template("home.html")


@app.route("/save", methods=["GET", "POST"])
@login_required
def save():
    """Save results in user's history page"""

    #if request.method == "POST":

        # insert result fields in database

    return render_template("myres.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        elif db.execute("SELECT username FROM users WHERE username = :username", username=request.form.get("username")):
            return apology("username already taken! :(")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Tests password and confirmation
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("password and confirmation do not match!")

        contupc = 0
        contloc = 0
        contsymb = 0
        contnum = 0

        # Require users' passwords to have some number of letters, numbers, and/or symbols
        for letter in str(request.form.get("password")):
            if ord(letter) >= 65 and ord(letter) <= 90:
                contupc += 1
            elif ord(letter) >= 97 and ord(letter) <= 122:
                contloc += 1
            elif (ord(letter) >= 1 and ord(letter) <= 47) or (ord(letter) >= 58 and ord(letter) <= 64) or (ord(letter) >= 91 and ord(letter) <= 96) or (ord(letter) >= 123 and ord(letter) <= 126):
                contsymb += 1
            elif ord(letter) >= 48 and ord(letter) <= 57:
                contnum += 1
        if contupc < 1 or contloc < 3 or contsymb < 1 or contnum < 1:
            return apology("password must contain at least: 1 uppercase letter, 3 lowercase letters, 1 numeral and 1 symbol")

        # Register new user
        hashp = generate_password_hash(request.form.get("password"))
        newuser = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hashp)",
                             username=request.form.get("username"),
                             hashp=hashp)

        session["user_id"] = db.execute("SELECT id FROM users WHERE username = :username",
                                        username=request.form.get("username"))[0]["id"]

        return redirect("/")

    else:
        return render_template("/register.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""

    username = request.args.get("username")

    tunames = (db.execute("SELECT username FROM users WHERE username = :username", username=username))

    if username and tunames:
        return jsonify(False)
    elif username and not tunames:
        return jsonify(True)
    else:
        return jsonify(True)


@app.route("/changepwd", methods=["GET", "POST"])
@login_required
def changepwd():

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure current password was submitted
        if not request.form.get("curpassword"):
            return apology("must provide current password")

        # Ensure new password was submitted
        elif not request.form.get("newpassword"):
            return apology("must provide new password")

        # Check current password
        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("curpassword")):
            return apology("current password does not match!")

        # Test new password and confirmation
        elif not request.form.get("newpassword") == request.form.get("confirmation"):
            return apology("new password and confirmation do not match!")

        db.execute("UPDATE users SET hash=:hashp WHERE id = :id", hashp=generate_password_hash(
            request.form.get("newpassword")), id=session["user_id"])

        return redirect("/")

    else:
        return render_template("/changepwd.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
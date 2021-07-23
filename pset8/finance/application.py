import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

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


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    portf = db.execute(
        "SELECT stock, SUM(shares) as totshares FROM history WHERE id = :id GROUP BY stock HAVING totshares > 0", id=session["user_id"])

    curprice = {}
    totstocks = 0

    for banco in portf:
        curprice[banco["stock"]] = lookup(banco["stock"])
        totstocks += curprice[banco["stock"]]["price"] * banco["totshares"]

    cashnow = float(db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]["cash"])
    grandtot = float(cashnow + totstocks)

    return render_template("/portfolio.html", portf=portf, curprice=curprice, cashnow=cashnow, totstocks=totstocks, grandtot=grandtot)


@app.route("/portfolio")
@login_required
def portfolio():
    """Show portfolio of stocks"""

    portf = db.execute(
        "SELECT stock, SUM(shares) as totshares FROM history WHERE id = :id GROUP BY stock HAVING totshares > 0", id=session["user_id"])

    curprice = {}
    totstocks = 0

    for banco in portf:
        curprice[banco["stock"]] = lookup(banco["stock"])
        totstocks += curprice[banco["stock"]]["price"] * banco["totshares"]

    cashnow = float(db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]["cash"])
    grandtot = float(cashnow + totstocks)

    return render_template("/portfolio.html", portf=portf, curprice=curprice, cashnow=cashnow, totstocks=totstocks, grandtot=grandtot)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock's symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide valid Stock's symbol", 400)

        # Ensure quantity of shares was submitted
        elif not request.form.get("shares") or (request.form.get("shares")).isdigit() == False:
            return apology("must provide a valid number of shares to buy (>0)", 400)

        # Check stock's price
        getprice = lookup(request.form.get("symbol"))

        if getprice == None or not getprice:
            return apology("invalid symbol/stock", 400)

        price = float(getprice["price"])

        curcash = float(db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]["cash"])

        if (curcash - (price * float(request.form.get("shares")))) < 0:
            return apology("not enough cash :(", 400)
        else:
            curcash = curcash - (price * float(request.form.get("shares")))
            db.execute("UPDATE users SET cash = :curcash WHERE id = :id", curcash=curcash, id=session["user_id"])
            db.execute("INSERT INTO history (id, op, stock, time, price, shares, amount, balance) VALUES (:id, :op, :symbol, :time, :price, :shares, :amount, :balance)",
                       id=session["user_id"],
                       op="BUY",
                       symbol=(request.form.get("symbol")).upper(),
                       time=datetime.now(),
                       price=price,
                       shares=request.form.get("shares"),
                       amount=price * float(request.form.get("shares")),
                       balance=curcash)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("/buy.html")


@app.route("/funds", methods=["GET", "POST"])
@login_required
def funds():
    """Add funds"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check value to be added to funds
        if float(request.form.get("cash")) < 0:
            return apology("Would you throw money away?...", 400)
        elif not request.form.get("cash") or float(request.form.get("cash")) == 0:
            return apology("¬¬", 400)

        # Query database for username
        db.execute("UPDATE users SET cash = cash + :addfund WHERE id = :id",
                   addfund=request.form.get("cash"), id=session["user_id"])

        # Register in history
        db.execute("INSERT INTO history (op, stock, time, price, shares, amount, id, balance) VALUES (:op, :symbol, :time, :price, :shares, :amount, :id, :balance)",
                   op="CREDIT",
                   symbol="-",
                   time=datetime.now(),
                   price=request.form.get("cash"),
                   shares=0,
                   amount=0,
                   id=session["user_id"],
                   balance=(db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"]))[0]["cash"] + float(request.form.get("cash")))

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("/funds.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    hist = db.execute("SELECT * FROM history WHERE id = :id", id=session["user_id"])
    if not hist:
        return render_template("/blank.html")

    return render_template("/history.html", hist=hist)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        quote = lookup(request.form.get("symbol"))

        if quote == None or not quote:
            return apology("invalid symbol/stock", 400)

        return render_template("/quoted.html", quote=quote, price=usd(quote["price"]))

    else:
        return render_template("/quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif db.execute("SELECT username FROM users WHERE username = :username", username=request.form.get("username")):
            return apology("username already taken! :(", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Tests password and confirmation
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("password and confirmation do not match!", 400)

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
            return apology("password must contain at least: 1 uppercase letter, 3 lowercase letters, 1 numeral and 1 symbol", 403)

        # Register new user
        hashp = generate_password_hash(request.form.get("password"))
        newuser = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hashp)",
                             username=request.form.get("username"),
                             hashp=hashp)

        session["user_id"] = db.execute("SELECT id FROM users WHERE username = :username",
                                        username=request.form.get("username"))[0]["id"]

        db.execute("INSERT INTO history (op, stock, time, price, shares, amount, id, balance) VALUES (:op, :symbol, :time, :price, :shares, :amount, :id, :balance)",
                   op="CREDIT",
                   symbol="-",
                   time=datetime.now(),
                   price=(db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"]))[0]["cash"],
                   shares=0,
                   amount=0,
                   id=session["user_id"],
                   balance=(db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"]))[0]["cash"])

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


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        tosell = db.execute(
            "SELECT stock, SUM(shares) as totshares FROM history WHERE id = :id GROUP BY stock HAVING totshares > 0", id=session["user_id"])

        # Ensure stock's symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide valid Stock's symbol", 400)

        # Ensure quantity of shares was submitted
        elif not request.form.get("shares") or (request.form.get("shares")).isdigit() == False:
            return apology("must provide a valid number of shares to sell (>0)", 400)

        # Ensure stock is actually owned by user
        elif not tosell[0]["stock"] == (request.form.get("symbol")).upper():
            return apology("you do not own any shares of this company", 400)

        # Ensure quantity of shares is actually owned by user
        elif not tosell[0]["totshares"] >= int(request.form.get("shares")):
            return apology("you do not own this much shares", 400)

        # Check stock's price
        getprice = lookup(request.form.get("symbol"))
        price = float(getprice["price"])

        curcash = float(db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]["cash"])

        curcash = curcash + (price * float(request.form.get("shares")))
        db.execute("UPDATE users SET cash = :curcash WHERE id = :id", curcash=curcash, id=session["user_id"])
        db.execute("INSERT INTO history (id, op, stock, time, price, shares, amount, balance) VALUES (:id, :op, :symbol, :time, :price, :shares, :amount, :balance)",
                   id=session["user_id"],
                   op="SELL",
                   symbol=(request.form.get("symbol")).upper(),
                   time=datetime.now(),
                   price=price,
                   shares=int(request.form.get("shares")) * -1,
                   amount=price * float(request.form.get("shares")),
                   balance=curcash)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        ownedstocks = db.execute(
            "SELECT stock FROM history WHERE id = :id GROUP BY stock HAVING stock != '-'", id=session["user_id"])

        return render_template("sell.html", stocks=ownedstocks)


@app.route("/changepwd", methods=["GET", "POST"])
@login_required
def changepwd():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure current password was submitted
        if not request.form.get("curpassword"):
            return apology("must provide current password", 400)

        # Ensure new password was submitted
        elif not request.form.get("newpassword"):
            return apology("must provide new password", 400)

        # Check current password
        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("curpassword")):
            return apology("current password does not match!", 400)

        # Test new password and confirmation
        elif not request.form.get("newpassword") == request.form.get("confirmation"):
            return apology("new password and confirmation do not match!", 400)

        db.execute("UPDATE users SET hash=:hashp WHERE id = :id", hashp=generate_password_hash(
            request.form.get("newpassword")), id=session["user_id"])

        return redirect("/")

    else:
        return render_template("/changepwd.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
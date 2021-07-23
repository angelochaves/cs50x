import os
import requests
import urllib.parse

from newsapi import NewsApiClient
from flask import redirect, render_template, request, session
from functools import wraps


def apology(message):
    """Render message as an apology to user."""

   # TODO
   # must flash user with error messages passed as parameter

    return


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/1.0/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def search(keyword):
    """Search the news with input keywords."""

    # Contact API
    try:
        newsapi = NewsApiClient(api_key='9d96cf253acd4cbea033a354a4381ac1')

        api_headlines = newsapi.get_top_headlines(q=keyword,
                                                  sources='bbc-news,the-verge',
                                                  category='business',
                                                  language='en',
                                                  country='us')

        newsapi.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        headlines = api_headlines.json()
        return {
            "nresults": int(headlines["totalResults"]),
            "title": headlines["articles"],
            "date": headlines["articles"]
                }
    except (KeyError, TypeError, ValueError):
        return None
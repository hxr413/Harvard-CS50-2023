import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # Display HTML table with
    # all stocks owned
    rows = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) != 0", user_id)
    total_sum = 0

    for row in rows:
        symbol = row["symbol"].upper()

        row["name"] = lookup(symbol)["name"]

        # number of shares of each stock
        shares = row["shares"]

        # current price of each stock
        row["price"] = lookup(symbol)["price"]

        # total value of each holding (= shares * price)
        row["stock_total"] = shares * row["price"]

        total_sum += row["stock_total"]

    # Display the user's current cash balance
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Display total value of stocks and cash together(= stocks' total value + cash)
    total = cash + total_sum

    # Looping in template
    return render_template("index.html", rows=rows, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # When form is submitted via POST, purchase the stock so long as the user can afford it
    if request.method == "POST":

        # Buy form ask for symbol and number of shares
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # Check for valid input
        if not symbol:
            return apology("must provide symbol", 400)
        if not shares:
            return apology("must provide shares", 400)

        if lookup(symbol) == None:
            return apology("the stock doesn't exist", 400)

        if shares.isdigit() == False or int(shares) < 0:
            return apology("the number of shares must be a positive integer", 400)

        price = lookup(symbol)["price"]
        transaction_amount = int(shares) * price
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = cash[0]["cash"]
        if transaction_amount > user_cash:
            return apology("there isn't enough cash in your account", 400)

        # Add stock to portfolio
        # Run SQL statement on database to purchase stock
        db.execute("INSERT INTO transactions (stock_name, symbol, shares, price, type, user_id) VALUES (?, ?, ?, ?, ?, ?)",
                   lookup(symbol)["name"], symbol, shares, price, "Buy", user_id)

        # Update cash to reflect purchased stock
        current_cash = user_cash - transaction_amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash, user_id)

        flash("Bought!")
        return redirect("/")

    # When requested via GET, display form to buy a stock
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Display a table with a history of all transactions, listing one row for every buy and sell
    user_id = session["user_id"]
    rows = db.execute("SELECT symbol, shares, price, time FROM transactions WHERE user_id = ?", user_id)

    for row in rows:
        symbol = row["symbol"].upper()
        time = row["time"]
        shares = row["shares"]
        price = row["price"]
        row["name"] = db.execute(
            "SELECT stock_name FROM transactions WHERE user_id = ? AND symbol = ? AND time = ?", user_id, symbol, time)[0]["stock_name"]
        row["action"] = db.execute(
            "SELECT type FROM transactions WHERE user_id = ? AND symbol = ? AND time = ?", user_id, symbol, time)[0]["type"]

    # Looping in template
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

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

    # When form is submitted via POST, look up the stock symbol by calling `lookup`, and display the results
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()

        if not symbol:
            return apology("must provide symbol", 400)

        # If lookup fails, function returns `None`
        if lookup(symbol) == None:
            # Return an apology to tell user the stock doesn't exist
            return apology("the stock doesn't exist", 400)

        # `lookup` takes a stock symbol and returns a stock quote
        # If lookup is successful, function returns a dictionary with `name`, `price`, `symbol`
        else:
            # Display an HTML page to the user that contains information about the stock
            name = lookup(symbol)["name"]
            price = lookup(symbol)["price"]

            # Passing values into templates
            return render_template("quoted.html", name=name, price=price, symbol=symbol)

    # When requested via GET, display form to request a stock quote
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # When form is submitted via POST
    if request.method == "POST":

        # Check for possible errors
        # If any field is left blank, return an apology
        if not request.form.get("username"):
            return apology("must provide username", 400)
        if not request.form.get("password"):
            return apology("must provide password", 400)
        if not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        # If password and confirmation don't match, return an apology
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("password and confirmation don't match", 400)

        username = request.form.get("username")
        # If the username is already taken, return an apology
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) != 0:
            return apology("the username is already taken", 400)

        # Then insert the new user into `users` table
        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

        # Log user in
        user_id = db.execute("SELECT id FROM users WHERE username = ?", username)[0]["id"]
        session["user_id"] = user_id
        return redirect("/")

    # When requested via GET, display registration form
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    # When form is submitted via POST, check for errors
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # Users fail to select a stock
        if not symbol:
            return apology("must provide symbol", 400)
        if not shares:
            return apology("must provide shares", 400)
        if lookup(symbol) == None:
            return apology("the stock doesn't exist", 400)

        # Users don't have the number of shares of stock they want to sell
        shares_owned = db.execute("SELECT SUM(shares) AS shares FROM transactions WHERE user_id = ? AND symbol = ?", user_id, symbol)[
            0]["shares"]
        if shares_owned <= 0:
            return apology("you don't own any shares of the stock", 400)
        if shares_owned < int(shares):
            return apology("you don't own enough shares of the stock", 400)

        # Users can't sell a negative number of shares
        if shares.isdigit() == False or int(shares) < 0:
            return apology("the number of shares must be a positive integer", 400)

        # Then sell the specified number of shares of stock and update the user's cash
        price = lookup(symbol)["price"]
        # Run SQL statement on database to sell stock
        db.execute("INSERT INTO transactions (stock_name, symbol, shares, price, type, user_id) VALUES (?, ?, ?, ?, ?, ?)",
                   lookup(symbol)["name"], symbol, -int(shares), price, "Sell", user_id)

        # Update cash to reflect sold stock
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        current_cash = user_cash + int(shares) * price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash, user_id)

        flash("Sold!")
        return redirect("/")

    # When requested via GET, display form to sell a stock
    else:
        stocks = db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = ?", user_id)
        for stock in stocks:
            symbol = stock["symbol"].upper()
        return render_template("sell.html", stocks=stocks)


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    """Manage cash"""
    user_id = session["user_id"]

    # When form is submitted via POST, purchase the stock so long as the user can afford it
    if request.method == "POST":
        operation = request.form.get("operation")
        amount = request.form.get("amount")
        na = "N/A"

        # Check for valid input
        if not amount:
            return apology("must provide amount", 400)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        if operation == "add":
            # Run SQL statement on database to add cash
            db.execute("INSERT INTO transactions (stock_name, symbol, shares, price, type, user_id) VALUES (?, ?, ?, ?, ?, ?)",
                       na, na, na, amount, "Add Cash", user_id)

            # Update cash to reflect addition
            current_cash = cash + float(amount)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash, user_id)

        elif operation == "subtract":
            if float(amount) < cash:
                return apology("there isn't enough cash in your account", 400)
            else:
                # Run SQL statement on database to add cash
                db.execute("INSERT INTO transactions (stock_name, symbol, shares, price, type, user_id) VALUES (?, ?, ?, ?, ?, ?)",
                           na, na, na, amount, "Subtract Cash", user_id)

            # Update cash to reflect addition
            current_cash = cash + amount
            db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash, user_id)

        return redirect("/")

    # When requested via GET, display form to buy a stock
    else:
        return render_template("index.html")
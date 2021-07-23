from cs50 import get_float

while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

owed = round(change * 100)

quarter = owed // 25
owed = owed % 25

dime = owed // 10
owed = owed % 10

nickel = owed // 5
owed = owed % 5

penny = owed

coins = quarter + dime + nickel + penny

print("The minimal number of coins are: ", coins)
print(f"Being {quarter} quarter(s), {dime} dime(s), {nickel} nickel(s) and {penny} penny(ies)")
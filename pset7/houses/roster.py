import os
import sys
from cs50 import SQL


def main():

    # link database
    db = SQL("sqlite:///students.db")

    # test arguments
    if not (len(sys.argv) == 2 and sys.argv[0] != "" and sys.argv[1] != ""):
        sys.exit("Usage: python roster.py <Hogwart's housename>")

    # retrieve data from student's database
    data = list(db.execute("SELECT first, middle, last, birth FROM students WHERE house = :house ORDER BY last, first",
                           house=sys.argv[1]))

    for i in data:
        if list(i.values())[1] is None:
            print(list(i.values())[0] + " " + list(i.values())[2] + ", born " + str(list(i.values())[3]))
        else:
            print(list(i.values())[0] + " " + str(list(i.values())[1]) + " " +
                  list(i.values())[2] + ", born " + str(list(i.values())[3]))


if __name__ == "__main__":
    main()
import os
import sys
import csv
from cs50 import SQL


def main():

    # link database
    db = SQL("sqlite:///students.db")

    # test arguments
    if not (len(sys.argv) == 2 and sys.argv[0] != "" and sys.argv[1] != ""):
        sys.exit("Usage: python import.py <csvfilename>.csv")

    # open csv file
    csvfile = open(sys.argv[1], "r")
    # read csvfile as a dictionary and put in a list
    csvdict = list(csv.DictReader(csvfile))

    keys = list(csvdict[0].keys())

    for i in range(0, len(list(csvdict))):
        # split name into first, middle and last names
        name = (list(csvdict[i].values())[0]).split(" ")
        # allocate names in right position
        if len(name) == 2:
            first = name[0]
            middle = None
            last = name[1]
        elif len(name) == 3:
            first = name[0]
            middle = name[1]
            last = name[2]
        # get house and birthdate
        house = list(csvdict[i].values())[1]
        birth = list(csvdict[i].values())[2]

        #print(first + "-" + str(middle) + "-" + last + "-" + house + "-" + birth)

        # insert current data into database
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (:first, :middle, :last, :house, :birth)",
                   first=first,
                   middle=middle,
                   last=last,
                   house=house,
                   birth=birth)


if __name__ == "__main__":
    main()
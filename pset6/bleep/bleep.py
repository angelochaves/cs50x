from cs50 import get_string
import sys


def main():

    if len(sys.argv) == 2 and sys.argv[1] != "":
        print("Success")
    else:
        sys.exit("Usage: python bleep.py dictionary")

    text = get_string("What message would you like to censor? ")

    f = open("banned.txt", "r")

    dtry = []
    for i in f:
        dtry.append(i.strip())
    dtry = set(dtry)
    dtry.update(["cat", "dog", "programmer", "politics"])

    ban = []
    word = []
    ks = "*"
    text = list(text.split(" "))

    for j in text:
        if str.lower(j) in dtry:
            for k in j:
                word.append(ks)
            ban.append("".join(word))
            word = []
        else:
            ban.append(j)

    sep = " "
    result = sep.join(ban)
    print(result)


if __name__ == "__main__":
    main()

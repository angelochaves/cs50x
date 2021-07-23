from cs50 import get_string
import sys
import crypt
import string


def main():

    # Tests arguments
    if len(sys.argv) != 2 or sys.argv[1] == "":
        sys.exit("Usage: python crack.py hash")

    # Defines 5 letter variable for password
    tp = ["", "", "", "", ""]
    # Writes salt
    salt = sys.argv[1][0:2]
    hashtry = ""
    # Defines set of characters to iterate through
    letters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

    for m in letters:
        for l in letters:
            for k in letters:
                for j in letters:
                    for i in letters[1:]:

                        tp[0] = i
                        tp[1] = j
                        tp[2] = k
                        tp[3] = l
                        tp[4] = m

                        guess = str("".join(tp).strip())
                        hashtry = crypt.crypt(guess, salt)
                        print(guess)

                        # Tests the hashes
                        if hashtry == sys.argv[1]:
                            print("The password is: " + guess)
                            sys.exit()


if __name__ == "__main__":
    main()
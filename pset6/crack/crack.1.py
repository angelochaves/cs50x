from cs50 import get_string
import sys
import crypt


def main():

    # Just encrypts any 5 letter password to test 'crack'
    if len(sys.argv) != 2 or sys.argv[1] == "":
        sys.exit("Usage: python crack.py hash")

    y = crypt.crypt(sys.argv[1], "50")

    print(y)


if __name__ == "__main__":
    main()
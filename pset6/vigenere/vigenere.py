from cs50 import get_string
import sys


def main():

    if len(sys.argv) == 2 and sys.argv[1].isalpha() == True:
        key = (sys.argv[1].strip()).lower()
    else:
        sys.exit("Usage: python vigenere.py k")

    ptext = get_string("plaintext: ")
    ctext = []
    sepkey = []
    j = 0

    for k in key:
        sepkey.append(ord(k) - 97)

    for i in ptext:

        if j >= len(sepkey):
            j = 0
        else:
            j = j

        if ord(i) >= 65 and ord(i) <= 90:
            if ord(i) + sepkey[j] > 90:
                i = str(chr((65 - 1) + sepkey[j] - (90 - ord(i))))
                ctext.append(i)
                j += 1
            else:
                i = str(chr(ord(i) + sepkey[j]))
                ctext.append(i)
                j += 1

        elif ord(i) >= 97 and ord(i) <= 122:
            if ord(i) + sepkey[j] > 122:
                i = str(chr((97 - 1) + sepkey[j] - (122 - ord(i))))
                ctext.append(i)
                j += 1
            else:
                i = str(chr(ord(i) + sepkey[j]))
                ctext.append(i)
                j += 1
        else:
            ctext.append(i)

    sep = ""
    result = sep.join(ctext)
    print("ciphertext: " + result)


if __name__ == "__main__":
    main()
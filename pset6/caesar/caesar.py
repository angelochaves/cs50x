from cs50 import get_string
import sys


def main():

    if len(sys.argv) == 2 and sys.argv[1].isdigit() == True and int(sys.argv[1]) > 0:
        print("Success")
    else:
        sys.exit("Usage: ./caesar key")

    key = int(sys.argv[1])

    # Reduces value of argv[1] to a meaninful value for key (i.e. < 26)
    while key > 26:
        key -= 26

    ptext = get_string("plaintext: ")
    ctext = []

    for i in ptext:

        if ord(i) >= 65 and ord(i) <= 90:
            if ord(i) + key > 90:
                i = str(chr((65 - 1) + key - (90 - ord(i))))
                ctext.append(i)
            else:
                i = str(chr(ord(i) + key))
                ctext.append(i)

        elif ord(i) >= 97 and ord(i) <= 122:
            if ord(i) + key > 122:
                i = str(chr((97 - 1) + key - (122 - ord(i))))
                ctext.append(i)
            else:
                i = str(chr(ord(i) + key))
                ctext.append(i)
        else:
            ctext.append(i)

    sep = ""
    result = sep.join(ctext)
    print("ciphertext: " + result)


if __name__ == "__main__":
    main()
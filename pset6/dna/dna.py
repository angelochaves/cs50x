from cs50 import get_string
import sys
import csv


def main():

    if not (len(sys.argv) == 3 and sys.argv[1] != "" and sys.argv[2] != ""):
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # open files (database and sequence to be analyzed)
    seq = open(sys.argv[2], "r")
    dbase = open(sys.argv[1], "r")

    # read database as a dictionary and put in a list
    ldbase = list(csv.DictReader(dbase))
    # read sequence and remove eventual blank spaces in sequence
    lseq = (seq.read()).strip()

    # create a list of database's STRs to search for in sequences
    genes = list(ldbase[0].keys())

    par = [0]*(len(genes)-1)

    # log = open('log.txt', 'w')

    i = 1
    j = 0
    temp = 0

    # search for STRs in given sequence
    while i < len(genes):
        while j <= len(lseq):
            #log.write(lseq[j:j+len(genes[i])] + "  " + genes[i] + "\n")
            # detect a possible STR
            if (lseq[j:(j+len(genes[i]))]) == genes[i]:
                j += len(genes[i])
                temp = 1
                while ((lseq[j:(j+len(genes[i]))]) == genes[i]):
                    temp += 1
                    j += len(genes[i])
                if temp > par[i-1]:
                    par[i-1] = temp
                    temp = 0
            else:
                j += 1
        i += 1
        j = 0

    # log.close()

    cont = 0

    # find person with genetic profile that have STRs detected in sample
    for line in range(0, (len(list(ldbase)))):
        for x in range(0, len(genes)-1):
            # print(str(par[x]) + "   " + str((list(ldbase[line].values())[x+1])))
            if par[x] == int(list(ldbase[line].values())[x+1]):
                cont += 1
                # print("cont: " + str(cont))
            if cont == (len(genes)-1):
                print(list(ldbase[line].values())[0])
                return
        cont = 0

    print("No match")


if __name__ == "__main__":
    main()
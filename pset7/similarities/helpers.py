from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    lista = a.split("\n")
    listb = b.split("\n")
    listc = []

    for i in lista:
        if i in listc:
            continue
        elif i in listb:
            listc.append(i)
    return listc


def sentences(a, b):
    """Return sentences in both a and b"""

    lista = sent_tokenize(a)
    listb = sent_tokenize(b)
    listc = []

    for i in lista:
        if i in listc:
            continue
        elif i in listb:
            listc.append(i)
    return listc


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    lista = []
    listb = []
    listc = []

    # QUEBRAR NLISTA E NLISTB EM TODAS A SUBSTRINGS POSSIVEIS DE 'N' TAMANHO
    for i in range(0, len(a)-n+1):
        lista.append(a[i:i+n])

    for j in range(0, len(b)-n+1):
        listb.append(b[j:j+n])

    for i in lista:
        if i in listc:
            continue
        elif i in listb:
            listc.append(i)

    return listc
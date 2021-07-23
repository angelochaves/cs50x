# a is a long string, for instance, a text

lista = []
nlista = []
tempa = []

# Breaks a long string in separate words
lista = a.split(" ")
# Selects every word of the list
for i in lista:
    # Selects every character of the word
    for j in i:
        # Tests for alfanumeric characters
        if j.isalnum():
            # Appends to a temporary list if it is alfanumeric
            tempa.append(j)
    # After the word/letters loop, if recomposes the word without any non-alfanumeric character
    nlista.append("".join(tempa))
    # Empties the temporary list for another word
    tempa = []
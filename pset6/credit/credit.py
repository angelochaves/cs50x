from cs50 import get_string

while True:
    card = get_string("Please insert credit card number: ")
    if card.isdigit() == False:
        continue
    number = int(card)
    if number > 0:
        break

lenght = len(card)

# Size-based validation
if lenght != 13:
    if lenght != 15:
        if lenght != 16:
            result = "INVALID"

cnumbers = []
sumn = 0

for i in card:
    cnumbers.append(i)

# Algorithm-based validation
# 1st step for validation: Multiplication by 2
rest = cnumbers[::-2]

for i in range(0, lenght - 1, 2):
    if (int(cnumbers[lenght - 2 - i]) * 2) > 9:
        sumn += (int(cnumbers[lenght - 2 - i]) * 2) - 9
    else:
        sumn += (int(cnumbers[lenght - 2 - i]) * 2)

# 2nd step for validation: sums all digits
for i in rest:
    sumn += int(i)
print(sumn)

# 3rd step for validation: checksum with final 0
if (sumn % 10) != 0:
    result = "INVALID"
elif card[0] == "4":
    result = ("VISA")
elif card[0] == "5":
    if int(card[1]) > 0 and int(card[1]) < 6:
        result = ("MASTERCARD")
elif card[0] == "3":
    if card[1] == "4" or card[1] == "7":
        result = ("AMEX")
    else:
        result = ("INVALID")
else:
    result = ("INVALID")

print(result)
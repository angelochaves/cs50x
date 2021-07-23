from cs50 import get_string

text = get_string("Text: ")

l = w = s = 0

# Count letters and detect sentences
for char in text:
    if (ord(char) > 64 and ord(char) < 91) or (ord(char) > 96 and ord(char) < 123):
        l += 1
    elif ord(char) == 33 or ord(char) == 46 or ord(char) == 63:
        s += 1

# Count number of spaces between words to determine number of words indirectly
w = text.count(' ') + 1

print(f"letters: {l}")
print(f"words: {w}")
print(f"sentences: {s}")

lf = l / w * 100
sf = s / w * 100

# Calculate index of readability
index = round(0.0588 * lf - 0.296 * sf - 15.8)

# output index value
if index < 1:
    print("Before Grade 1")
elif index >= 1 and index <= 16:
    print(f"Grade {index}")
else:
    print("Grade 16+")
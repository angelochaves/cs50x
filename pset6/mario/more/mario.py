from cs50 import get_int

while True:
    height = get_int("Please choose height of pyramid: ")
    if height > 0 and height <= 8:
        break

for i in range(height):
    space = (height - i - 1) * " "
    block = "#" * (i + 1)
    print(space + block + "  " + block)
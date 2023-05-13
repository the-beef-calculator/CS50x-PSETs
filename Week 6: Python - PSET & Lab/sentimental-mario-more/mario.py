from cs50 import get_int

def main():
    height = get_int("Height: ")

    while (height < 1 or height > 8):
        height = get_int("Height: ")


main()
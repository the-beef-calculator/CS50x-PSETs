from cs50 import get_int

def main():
    height = get_int("Height: ")

    while (height < 1 or height > 8):
        height = get_int("Height: ")

    spaces = height - 1
    hashnumber = 1

    for i in range(0, height):
        for j in range(0, spaces):
            print(" ",end="")
        for z in range(0, hashnumber):
            print("#",end="")

        print("  ",end="")

        for z in range(0, hashnumber):
            print("#",end="")
        print("")

        hashnumber += 1
        spaces -=1






main()
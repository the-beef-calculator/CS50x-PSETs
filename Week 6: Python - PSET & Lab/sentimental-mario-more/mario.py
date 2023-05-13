from cs50 import get_int

def main():
    height = get_int("Height: ")

    while (height < 1 or height > 8):
        height = get_int("Height: ")

    # there will always be at least one hash. spaces will be one less than height
    spaces = height - 1
    hashnumber = 1

    #building the pyramid
    for i in range(0, height):
        for j in range(0, spaces):
            print(" ",end="")
        for z in range(0, hashnumber):
            print("#",end="")

        print("  ",end="")
        #end keyword to modify print to not add a new line
        for z in range(0, hashnumber):
            print("#",end="")
        print("")

        #incrementing and decrementing
        hashnumber += 1
        spaces -=1

main()
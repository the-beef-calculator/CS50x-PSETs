from cs50 import get_int

def main():

    cents = get_int("How many cents?")

    while (cents < 0):
        cents = get_int("How many cents?")

    quarterCoins = (cents / 25)
    dimeCoins = (cents / 10 )
    nickelCoins = (cents / 5)
    pennyCoins = (cents / 1)

    coins[] = {quarterCoins, dimeCoins, nickelCoins, pennyCoins}

    





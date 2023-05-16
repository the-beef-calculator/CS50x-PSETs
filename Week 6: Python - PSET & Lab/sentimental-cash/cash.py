from cs50 import get_float

def main():

    coinTotal = 0

    cents = get_float("Change owed: ")

    while (cents < 0):
        cents = get_float("Change owed: ")

    quarterCoins = get_quarterCoins(cents) * 0.25
    cents = cents - quarterCoins

    dimeCoins = get_dimeCoins(cents) * 0.1
    cents = cents - dimeCoins

    nickelCoins = get_nickelCoins(cents) * 0.05
    cents = cents - nickelCoins

    pennyCoins = get_pennyCoins(cents) * 0.01
    cents = cents - pennyCoins

    coins = [quarterCoins, dimeCoins, nickelCoins, pennyCoins]

    for i in range(len(coins)):
        coinTotal += i


    print(coinTotal)




def get_quarterCoins(cents):

    quarterCoins = (cents / 25) * 100
    return int(quarterCoins)

def get_dimeCoins(cents):

    dimeCoins = (cents / 10) * 100
    return int(dimeCoins)

def get_nickelCoins(cents):

    nickelCoins = (cents / 5) * 100
    return int(nickelCoins)

def get_pennyCoins(cents):

    pennyCoins = (cents / 1 ) * 100
    return int(pennyCoins)


main()









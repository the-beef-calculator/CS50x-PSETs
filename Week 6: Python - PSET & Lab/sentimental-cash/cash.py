from cs50 import get_float

def main():

    cents = get_float("Change owed: ")

    while (cents < 0):
        cents = get_float("Change owed: ")

    quarterCoins = (cents / 25)
    dimeCoins = (cents / 10 )
    nickelCoins = (cents / 5)
    pennyCoins = (cents / 1)
    coinTotal = 0


    coins = [quarterCoins, dimeCoins, nickelCoins, pennyCoins]



    for i in range(len(coins)):
        coinTotal += i


    print(coinTotal)


main()

def get_quarterCoins(cents):

    quarterCoins = (cents / 25) * 100
    return int(quarterCoins)

def get_dimeCoins(cents):

    dimeCoins = (cents / 10) * 100
    return int(dimeCoins)

def get_nickelCoins(cents):

    nickelCoins = (cents / 5) * 100
    return int(nickelCoins)

def get_pennyCoins(cents)












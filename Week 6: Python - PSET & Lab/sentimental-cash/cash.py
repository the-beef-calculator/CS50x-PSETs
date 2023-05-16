from cs50 import get_float

def main():

    coinTotal = 0
    coins = []

    cents = get_float("Change owed: ")

    while (cents < 0):
        cents = get_float("Change owed: ")

    quarterCoins = get_quarterCoins(cents) * 0.25
    coins.append(get_quarterCoins(cents))
    cents = round((cents - quarterCoins), 2)

    dimeCoins = get_dimeCoins(cents) * 0.1
    coins.append(get_dimeCoins(cents))
    cents = round((cents - dimeCoins), 2)

    nickelCoins = get_nickelCoins(cents) * 0.05
    coins.append(get_nickelCoins(cents))
    cents = round((cents - nickelCoins), 2)

    pennyCoins = get_pennyCoins(cents) * 0.01
    coins.append(get_pennyCoins(cents))
    cents = round((cents - pennyCoins), 2)



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









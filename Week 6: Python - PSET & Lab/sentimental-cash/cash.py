from cs50 import get_int

def main():

    cents = get_int("How many cents? ")

    while (cents < 0):
        cents = get_int("How many cents? ")

    quarterCoins = (cents / 25)
    dimeCoins = (cents / 10 )
    nickelCoins = (cents / 5)
    pennyCoins = (cents / 1)
    coinTotal = 0


    coins = [quarterCoins, dimeCoins, nickelCoins, pennyCoins]

    for i in range(len(coins)):
        if i == 0:
            cents = (cents - coins[i] * 25)
        if i == 1:
            cents = (cents - coins[i] * 10)
        if i == 2:
            cents = (cents - coins[i] * 5)
        if i == 3:
            cents = (cents - coins[i] * 1)

    for i in range(len(coins)):
        coinTotal += i


    print(coinTotal)

main()









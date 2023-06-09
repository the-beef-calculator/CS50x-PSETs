# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")


    # TODO: Read teams into memory from file
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)


        # consise way of appending to a team while declaring the variable in one line.
        # this way, you do not need to declare a for loop.

        teams = [dict(row) for row in reader]
        

        # changing ratings value from strings to integers
        for team in teams:
            team["rating"] = int(team["rating"])

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts

    for team in teams:

        #add teams to counts dictionary with integer value 0
        counts[team["team"]] = 0


    tournament_count = N

    while(tournament_count != 0):
        winner = simulate_tournament(teams)
        counts[winner] +=1
        tournament_count -=1
 # Print each team's chances of winning, according to simulation


   #code for writing to a  text file
   #file = open('tourneyresults ' + str(N) + '.txt', "w")

    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        #file.write(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")
        #file.write("\n")
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")



def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO

    winner = [simulate_round(teams)]

    while len(winner[0]) > 1:
        winner = [simulate_round(winner[0])]

    return winner[0][0]["team"]

if __name__ == "__main__":
    main()

from cs50 import get_string

# 0.0588 * L - 0.296 * S - 15.8

def main():

    input = get_string("Text: ")

    L = ((count_letters(input) / count_words(input)) * 100)
    S = ((count_sentences(input) / count_words(input) * 100 ))

    


def count_letters(sentence):

    return (len([char for char in sentence if char.isAlpha()]))

def count_words(sentence):

    words = sentence.split()
    return len(words)

def count_sentences(input):

    sentences = input.count(".")
    sentences += input.count("!")
    sentences += input.count("?")

    return sentences

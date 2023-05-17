from cs50 import get_string

# 0.0588 * L - 0.296 * S - 15.8

def main():

    input = get_string("Text: ")




def count_letters(sentence):

    return (len([char for char in sentence if char.isAlpha()]))

def count_words(sentence):

    words = sentence.split()
    return len(words)

def count_sentences(input)

    

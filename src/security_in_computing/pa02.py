#*=============================================================================
#|  Assignment: pa02 - Encrypting a plaintext file using the Hill cipher
#|
#|     Author:  Hasita Kode
#|   Language:  python
#| To Compile:  n/a
#| To Execute:  python3 pa02.py kX.txt pX.txt
#|              where kX.txt is the keytext file
#|              and pX.txt is plaintext file
#|     Note:
#|              All input files are simple 8 bit ASCII input
#|              All execute commands above have been tested on Eustis
#|
#|     Class:    CIS3360 - Security in Computing
#|     Instructor: McAlpin
#|     Due Date:   per assignment
#+=============================================================================*/

import sys


def read_key_file(key_filename):
    #Read the key file and return the dimension of the key matrix and the matrix itself
    with open(key_filename, "r") as f:
        tokens = f.read().split()

    #fist number will be the matrix's dimensions
    n = int(tokens[0])

    #read the next n squared values
    values = list(map(int, tokens[1:1 + n * n]))

    matrix = []
    idx = 0

    #here I actually build the matrix row by row
    for _ in range(n):
        row = values[idx:idx + n]
        matrix.append(row)
        idx += n

    return n, matrix


def read_plaintext_file(plaintext_filename, block_size):
    #for this function I read the plaintext and remove all the non letter
    #characters and convert the remaining letters to lowercase
    #Also to keep the length as a multiple of the block size I pad it iwth x
    with open(plaintext_filename, "r") as f:
        raw = f.read()

    #here I keep only the alphabet and convert them to lowercase
    letters = [ch.lower() for ch in raw if ch.isalpha()]

    #here i'm determining whether to pad or not
    remainder = len(letters) % block_size
    if remainder != 0:
        pad_needed = block_size - remainder
        letters.extend(["x"] * pad_needed)

    return "".join(letters)


def print_key_matrix(n, matrix):
    #for this function I print the key matrix 
    print("\nKey matrix:")
    #I print each row with the for loop 
    for row in matrix:
        line = "".join("%4d" % val for val in row)
        print(line)


def print_wrapped(title, text):
    #
    print("\n" + title + ":")
    for i in range(0, len(text), 80):
        print(text[i:i + 80])


def encrypt_hill_cipher(plaintext, n, matrix):
    #in this function I encrypt the plain text using the Hill Cipher

    #for each group of the letters (n of them) I convert them into
    #numbers and multiple by the key matrix and then do mod 26 
    #nd then conver thtem back to letters
    ciphertext_chars = []

    #I go through one sized n block at a time with the loop
    for block_start in range(0, len(plaintext), n):
        #the current plaintext block
        block = plaintext[block_start:block_start + n]
        #I convert the letters to numbers
        p_vector = [ord(ch) - ord('a') for ch in block]

        c_vector = [0] * n

        #I do the matrix multiplication
        for i in range(n):
            total = 0
            for k in range(n):
                total += matrix[i][k] * p_vector[k]
            #doing the mod here
            c_vector[i] = total % 26

        #I convert the numbers that are now encrypted back to letters
        for val in c_vector:
            ciphertext_chars.append(chr(val + ord('a')))

    return "".join(ciphertext_chars)


def main():

    #checking to see the correct number of command line arguements 
    if len(sys.argv) != 3:
        print("Usage: python3 pa02.py <key_file> <plaintext_file>")
        sys.exit(1)

    #I read the file names here
    key_filename = sys.argv[1]
    plaintext_filename = sys.argv[2]

    #reading the input files here
    n, matrix = read_key_file(key_filename)
    plaintext = read_plaintext_file(plaintext_filename, n)
    #encrypting the plaintext
    ciphertext = encrypt_hill_cipher(plaintext, n, matrix)

    print_key_matrix(n, matrix)
    print_wrapped("Plaintext", plaintext)
    print_wrapped("Ciphertext", ciphertext)


if __name__ == "__main__":
    main()

#*=============================================================================
#|     I Hasita Kode (5725800) affirm that this program is
#|  entirely my own work and that I have neither developed my code together with
#|  any another person, nor copied any code from any other person, nor permitted
#|  my code to be copied  or otherwise used by any other person, nor have I
#|  copied, modified, or otherwise used programs created by others. I acknowledge
#|  that any violation of the above terms will be treated as academic dishonesty.
#+=============================================================================*/
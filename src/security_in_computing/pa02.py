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
    """Read the encryption key file and return (n, matrix) where matrix is a
    list of lists of ints, n rows by n columns."""
    with open(key_filename, "r") as f:
        tokens = f.read().split()

    n = int(tokens[0])
    values = list(map(int, tokens[1:1 + n * n]))

    matrix = []
    idx = 0
    for _ in range(n):
        row = values[idx:idx + n]
        matrix.append(row)
        idx += n

    return n, matrix


def read_plaintext_file(plaintext_filename, block_size):
    """Read the plaintext file, keep only alphabetic characters, convert
    them to lowercase, and pad with 'x' so the length is a multiple of
    block_size."""
    with open(plaintext_filename, "r") as f:
        raw = f.read()

    letters = [ch.lower() for ch in raw if ch.isalpha()]

    remainder = len(letters) % block_size
    if remainder != 0:
        pad_needed = block_size - remainder
        letters.extend(["x"] * pad_needed)

    return "".join(letters)


def print_key_matrix(n, matrix):
    print("\nKey matrix:")
    for row in matrix:
        line = "".join("%4d" % val for val in row)
        print(line)


def print_wrapped(title, text):
    print("\n" + title + ":")
    for i in range(0, len(text), 80):
        print(text[i:i + 80])


def encrypt_hill_cipher(plaintext, n, matrix):
    """Encrypt plaintext (already lowercase letters only, length is a
    multiple of n) using the Hill cipher with the given n x n key matrix.
    Each block of n letters is treated as a column vector and multiplied
    by the key matrix, modulo 26."""
    ciphertext_chars = []

    for block_start in range(0, len(plaintext), n):
        block = plaintext[block_start:block_start + n]
        p_vector = [ord(ch) - ord('a') for ch in block]

        c_vector = [0] * n
        for i in range(n):
            total = 0
            for k in range(n):
                total += matrix[i][k] * p_vector[k]
            c_vector[i] = total % 26

        for val in c_vector:
            ciphertext_chars.append(chr(val + ord('a')))

    return "".join(ciphertext_chars)


def main():
    if len(sys.argv) != 3:
        print("Usage: python3 pa02.py <key_file> <plaintext_file>")
        sys.exit(1)

    key_filename = sys.argv[1]
    plaintext_filename = sys.argv[2]

    n, matrix = read_key_file(key_filename)
    plaintext = read_plaintext_file(plaintext_filename, n)
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
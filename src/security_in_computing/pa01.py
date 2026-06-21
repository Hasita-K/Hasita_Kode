#!/usr/bin/env python3
"""
=============================================================================
  Assignment:  pa01 - Calculate the checksum of an input file given:
                 -> the name of the input file,
                 -> the checksum size of either 8, 16, or 32 bits
       Author:  Hasita Kode
     Language:  python
   To Compile:  N/A (interpreted)
   To Execute:  python3 pa01.py inputFilename.txt checksumSize
                 where inputFilename.txt is the input file
                 and checksumSize is either 8, 16, or 32
        Note:
                All input files are simple 8 bit ASCII input
        Class:  CIS3360 - Security in Computing
   Instructor:  McAlpin
    Due Date:   per assignment
=============================================================================
"""

import sys


def main():
    # ---- 1. Validate / collect command line arguments ----
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} inputFilename checksumSize", file=sys.stderr)
        sys.exit(1)

    filename = sys.argv[1]

    try:
        checkSumSize = int(sys.argv[2])
    except ValueError:
        checkSumSize = -1

    if checkSumSize not in (8, 16, 32):
        print("Valid checksum sizes are 8, 16, or 32", file=sys.stderr)
        sys.exit(1)

    # ---- 2. Open and read the input file (binary, to preserve every byte) ----
    try:
        with open(filename, "rb") as f:
            data = f.read()
    except OSError:
        print(f"Error: could not open file {filename}", file=sys.stderr)
        sys.exit(1)

    characterCnt = len(data)  # original file length, includes the terminating LF (0x0A)

    # ---- 3. Pad the data with 'X' characters so its length is an exact   ----
    # ---- multiple of the checksum word size (1, 2, or 4 bytes).          ----
    # ---- This padded buffer is what gets echoed AND checksummed.        ----
    wordSizeBytes = checkSumSize // 8
    remainder = characterCnt % wordSizeBytes
    padAmount = (wordSizeBytes - remainder) if remainder != 0 else 0
    padded = data + (b"X" * padAmount)
    paddedLen = len(padded)

    # ---- 4. Echo the padded text to the screen, 80 characters per row ----
    # (a blank line goes before and after the echoed block, per the expected output format)
    stdout_buf = sys.stdout.buffer
    stdout_buf.write(b"\n")
    pos = 0
    while pos < paddedLen:
        rowLen = min(80, paddedLen - pos)
        stdout_buf.write(padded[pos:pos + rowLen])
        pos += rowLen
        if pos < paddedLen:
            stdout_buf.write(b"\n")
    stdout_buf.write(b"\n")
    stdout_buf.flush()

    # ---- 5. Calculate the checksum: sum of checkSumSize-bit words, ----
    # ---- accumulated with no overflow beyond checkSumSize bits.    ----
    checksumAccum = 0
    for i in range(0, paddedLen, wordSizeBytes):
        word = int.from_bytes(padded[i:i + wordSizeBytes], byteorder="big")
        checksumAccum += word

    checksumMask = (1 << checkSumSize) - 1
    checksum = checksumAccum & checksumMask

    # ---- 6. Print the checksum line (chars count reflects the padded length) ----
    print("%2d bit checksum is %8x for all %4d chars" %
          (checkSumSize, checksum, paddedLen))


if __name__ == "__main__":
    main()

"""
=============================================================================
  I Hasita Kode (5725800) affirm that this program is
  entirely my own work and that I have neither developed my code together with
  any another person, nor copied any code from any other person, nor permitted
  my code to be copied  or otherwise used by any other person, nor have I
  copied, modified, or otherwise used programs created by others. I acknowledge
  that any violation of the above terms will be treated as academic dishonesty.
=============================================================================
"""

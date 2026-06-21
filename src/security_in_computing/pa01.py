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
    #check for valid number of command line args
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} inputFilename checksumSize", file=sys.stderr)
        sys.exit(1)

    #get the file name
    filename = sys.argv[1]

    #convert the checksum size to an integer
    try:
        checkSumSize = int(sys.argv[2])
    except ValueError:
        checkSumSize = -1

    #validate the checksum size
    if checkSumSize not in (8, 16, 32):
        print("Valid checksum sizes are 8, 16, or 32", file=sys.stderr)
        sys.exit(1)

    #I'm oppening the file and reading everything
    try:
        with open(filename, "rb") as f:
            data = f.read()
    except OSError:
        print(f"Error: could not open file {filename}", file=sys.stderr)
        sys.exit(1)

    #store the original length
    characterCnt = len(data)  # this includes the terminating 0x0A btw

    #get teh word size
    wordSizeBytes = checkSumSize // 8

    #find how many X characters are needed to pad
    remainder = characterCnt % wordSizeBytes
    padAmount = (wordSizeBytes - remainder) if remainder != 0 else 0

    #create the padded data
    padded = data + (b"X" * padAmount)
    paddedLen = len(padded)

    # print all the padded text
    stdout_buf = sys.stdout.buffer
    stdout_buf.write(b"\n")
    pos = 0
    while pos < paddedLen:
        rowLen = min(80, paddedLen - pos)
        stdout_buf.write(padded[pos:pos + rowLen])
        pos += rowLen

        #here i'm just printing a new line if there's more text 
        if pos < paddedLen:
            stdout_buf.write(b"\n")
    stdout_buf.write(b"\n")
    stdout_buf.flush()

    #initialized the checksum 
    checksumAccum = 0

    #looped through the padded data 
    for i in range(0, paddedLen, wordSizeBytes):
        word = int.from_bytes(padded[i:i + wordSizeBytes], byteorder="big")
        checksumAccum += word

    #creating mask for the correct checksum size
    checksumMask = (1 << checkSumSize) - 1

    #here I keep only the lower bit of the checksum
    checksum = checksumAccum & checksumMask

    #printing the final checksum 
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

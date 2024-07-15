# Advanced TextEditor with AVL Tree Storage, Spell Checking, and Huffman Coding Compression

## Overview

HuffAVLTextEditor is an advanced text editor that combines efficient word management using AVL Tree storage, robust spell checking capabilities, and powerful text compression via Huffman coding. This project allows users to interactively insert, replace, and delete words while maintaining an optimized text structure using AVL trees. It also provides encoding and decoding functionalities to demonstrate the effectiveness of Huffman coding.

## Features

1. **Text Editor**: 
    - **Insert Words**: Efficiently insert words into the text editor using AVL trees.
    - **Replace Words**: Replace existing words with new ones using AVL trees.
    - **Delete Words**: Remove words from the text editor using AVL trees.
    - **Display Sentence**: Display the current sentence using pre-order traversal of the AVL tree.

2. **Huffman Coding**:
    - **Frequency Calculation**: Calculate the frequency of characters in the sentence.
    - **Huffman Tree Construction**: Build a Huffman tree based on character frequencies.
    - **Encoding**: Encode the sentence using Huffman coding.
    - **Decoding**: Decode the encoded string back to the original sentence.
    - **Compression Ratio**: Display the compression ratio achieved by Huffman coding.

3. **Spell Checker**:
    - **Dictionary Loading**: Load a dictionary of words for spell checking.
    - **Similar Words Identification**: Identify similar words based on edit distance.

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)
- Standard C++ library
- Input/Output streams
### Usage
When you run the HuffAVLTextEditor program, you'll interact with it using the following commands:

Insert a Word:

Enter 1 to insert a word.
You'll be prompted to enter the word you want to insert.
Optionally, perform a spell check for the inserted word to find similar words.
Replace a Word:

Enter 2 to replace a word.
You'll be prompted to enter the old word followed by the new word.
Delete a Word:

Enter 3 to delete a word.
You'll be prompted to enter the word you want to delete.
Exit and Encode/Decode Text:

Enter 4 to exit the program.
The program will display the current sentence formed from the words stored in the AVL tree.
It will then proceed to encode and decode the sentence using Huffman coding.
Details such as original size, encoded size, and compression ratio will be shown.
Encoded data will be saved to encode.txt, and decoded data will be saved to decode.txt.
This interactive workflow allows you to manage text efficiently with AVL tree-based operations, explore Huffman coding for text compression, and utilize spell checking capabilities seamlessly.
### Example 
The input.txt file should contain a list of words to load into the spell checker dictionary.

### Output 
encode.txt: This file contains the Huffman encoded string.
decode.txt: This file contains the Huffman decoded string.

### Acknowledgements
1. AVL Tree Implementation and Balancing Logic: Efficiently managing and balancing words in the text editor using AVL trees.
2. Huffman Coding Implementation for Text Compression: Encoding and decoding text using Huffman coding for effective compression.
3. Spell Checker with Edit Distance Tolerance: Implementing spell checking functionality with tolerance for edit distance to suggest similar words.

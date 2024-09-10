/* Function: compress
 * Usage: compress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman compressor.  Compresses
 * the file whose contents are specified by the input
 * ibstream, then writes the result to outfile. */
void compress(ibstream& infile, obstream& outfile) {
    /* Calculates the frequencies of each character within text */
    Map<ext_char, int> frequenciesTable = getFrequencyTable(infile);

    /* Buffer-vector for cypher tree creation */
    Vector<Node*> vec;
    /* Add nodes for each sumbol and put them to vec */
    buildNodesVector(vec, frequenciesTable);
    /* Main Huffman tree building */
    Node* root = buildEncodingTree(vec);

    /* ENCODE TREE INTO CYPHER FILE HEADER */
    encodeTreeToFileHeader(root, outfile);
    outfile.put(' ');//put some char to divide header from main text cypher

    /* ENCODE FILE MAIN TEXT INTO CYPHER FILE */
    infile.rewind();
    encodeMainTextToFile(infile, root, outfile);

    /* Memory cleaning */
    deleteTree(root);
}
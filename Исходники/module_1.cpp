codeWords generateHuffmanCodeWordsR_CW(int noOfCodeWords, bool firstCode)
{
	codeWords temp;

	int toplevel = (int) ((log10l(noOfCodeWords)/log10l(2)) + 1);
	int total = (int) (powl(2,(double)toplevel));

	int noOnPreLevel = total - noOfCodeWords;

	int codeWordCount = 0;

	recDownCodeWords(toplevel, noOfCodeWords - noOnPreLevel, noOfCodeWords, 0, codeWordCount, temp, *(new codeWord), false);

	return temp;

}
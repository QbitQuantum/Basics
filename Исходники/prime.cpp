int main ()
{
	ReadFile crossword;
	crossword.MapFile();
	//long size = crossword.getFileSize();
	
	//qsort (letters, linesOfFile, sizeof(unsigned long long int), compare);
	
	for(int i=0;i<linesOfFile; i++) {
		cout << letters[i].word <<"\t" << letters[i].value <<endl;
	}
	
	
}
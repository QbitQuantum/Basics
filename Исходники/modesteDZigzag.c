int main(){
	
	int numPeaks=0,numPits=0,numRows=0,numLetters=0,row=0,col=0,count=0,loc=-1,maxCols=0,i=0;
	char encrypted[10000],decrypted[10000];
	FILE* in= fopen("input.txt","r");
	FILE* out= fopen("output.txt","w");
	
	if(in==NULL){//Checks to see if the input file exist
		printf("Input File Invalid");
		fprintf(out,"INPUT FILE INVALID");
		return 1;
	}
	
	fscanf(in,"%d",&numRows); //Stores the number of rows
	fscanf(in,"%s",&encrypted); //Stores the encrypted message
	fclose(in);
	
	numLetters= strlen(encrypted); //Gets the length of the encrypted message
	
	if(numLetters<=0 || numRows <=0){//Checks to see if the input in the input file is fairly valid
		printf("This input can not be deciphered or there is no input to be deciphered");
		return 1;	
	}
	
	if(numLetters <= numRows){//All characters fall in first column therefore may be printed directly without deciphering
		fprintf(out,"%s",encrypted);
		fclose(out);
		printf("CHECK OUTPUT.TXT FOR RESULTS");
		return 0;
	}
	
	numPeaks=1+(numLetters/(2*numRows-2)); //Number of peaks in the encrypted message
	numPits=1+((numLetters-numRows)/(2*numRows-2)); //Number of pits in the encrypted message
	
	row=1;
	while(row <= numRows){ //Loops from current row to number of rows
		
		col=1;
		maxCols=getMax(numPeaks,numPits,row,numLetters,numRows); //Retrieves maximum number of columns/characters in row
		
		while(col <= maxCols){
			//loc is the location the character belongs in, in the deciphered array
			//Places characters row by row into their correct position in deciphered array
			
			if(col==1){ //Characters in first column is automatically has correct loc index
				loc=row;
			}
			
			else if(row == 1 || row == numRows){ //Row is first or final row
				loc=(col-1)*(2*numRows -2) +row;
			}
					
			else if(col%2==0){ //Column is even and has 1 more large gaps between characters than small ones
				loc=(col/2)*((2*numRows) - (2*row)) + (col/2 -1)*((2*numRows) - (2*(numRows-row +1))) + row ;
			}
				
			else{//Column is odd and has the same number of large and small gaps before the current character
				loc = (col/2)* (((2*numRows) - (2*row)) + ((2*numRows) - 2*(numRows-row +1))) + row;
			}
			
			loc-=1; //To accommodate for array location starting at 0 
			decrypted[loc]=encrypted[count++];
			col++;		
		}
		row++;
	}
	decrypted[numLetters]='\0'; //Adds end of string character at the end of array to make it a string
	fprintf(out,"%s",decrypted);
	
	printf("CHECK OUTPUT.TXT FOR RESULTS");
	fclose(out);
	return 0;
}
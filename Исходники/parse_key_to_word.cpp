int main(){
	FILE *fin=fopen("phone.cin","r");
	FILE *fout;
	
	char file[100];
	wchar_t str[100];
	
	for(int i=0;i<26045;i++){
		fwscanf(fin,L"%S",str);
		sprintf(file,"_%s_",str);
		
		for(int i=0;file[i];i++)
			if(file[i]=='/')
				file[i]='=';

		fwscanf(fin,L"%s",str);
		
		fout=fopen(file,"a");
		fwprintf(fout,L"%s",str);
		fclose(fout);
	}
	
	fclose(fin);
	
	return 0;
}
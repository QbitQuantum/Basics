int main(int argc, char *argv[]){
	FILE *fp;
	int c;

// ./mcat-lib file
// afficher le fichier
	if(argc==2){
		if(!(fp=fopen(argv[1],"r"))){
			perror("Error opening file.");
			exit(EXIT_FAILURE);
		}

		c = fgetc(fp);
		while(c!=EOF){
			printf("%c",(char)c);
			c = fgetc(fp);
		}
		fclose(fp);
	}

// ./mcat-lib file1 file2 file3
// concat file1, file2 et exporter a file3
	else if(argc==4){
		FILE *fp2, *fp3;
		if( !(fp=fopen(argv[1],"r")) || !(fp2=fopen(argv[2],"r")) || !(fp3=fopen(argv[3],"w+")) ){
			perror("Error opening/creating file.");
			exit(EXIT_FAILURE);
		}

		c = fgetc(fp);
		while(c!=EOF){
			fputc(c,fp3);
			c = fgetc(fp);
		}
		fclose(fp);
		c = fgetc(fp2);
		while(c!=EOF){
			fputc(c,fp3);
			c = fgetc(fp2);
		}
		fclose(fp2);
	}

// ./mcat-lib file1 file2 > file3
// concat file1, file2 et exporter a file3
	else if(argc==3){
		FILE *fp2, *fp3;
		if( !(fp=fopen(argv[1],"r")) || !(fp2=fopen(argv[2],"r"))){
			perror("Error opening file.");
			exit(EXIT_FAILURE);
		}

		c = fgetc(fp);
		while(c!=EOF){
			printf("%c",(char)c);
			c = fgetc(fp);
		}
		fclose(fp);
		c = fgetc(fp2);
		while(c!=EOF){
			printf("%c",(char)c);
			c = fgetc(fp2);
		}
		fclose(fp2);
	}
}
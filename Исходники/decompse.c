int main(int argc,char *argv[])
{
	int n=0;
	int *parray=readfile(FILENAM,&n);
	int *darray=decompose(atoi(argv[1]),parray,n);
	printdarr(darray,parray);
	return 0;	
}
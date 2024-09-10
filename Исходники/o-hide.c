int merge(int argc,char** argv,int ask_pass,char* pass)
{
FILE *image,*text,*merg;
unsigned int cha,lenpass;
int i;
image = fopen(argv[2],"rb");
text = fopen(argv[3],"rb");
merg = fopen(argv[4],"wb");

if( ask_pass == 1 )
	lenpass = strlen(pass);

while(1)
{
cha=fgetc(image);
if(cha==EOF)
break;
fputc(cha,merg);
} // finished reading 1st file.
i=0;
if( ask_pass == 1 )
{
fputc('E'+pass[i],merg);
i = (i+1) %lenpass;
fputc('N'+pass[i],merg);
i = (i+1) %lenpass;
fputc('D'+pass[i],merg);
i = (i+1) %lenpass;
fputc('I'+pass[i],merg);
i = (i+1) %lenpass;
}
else if( ask_pass == 0)
{
fputc('E',merg);
fputc('N',merg);
fputc('D',merg);
fputc('I',merg);
}
while(1)
{
cha=fgetc(text);
if(cha==EOF)
break;
/// Encript the text file here ////
if( ask_pass == 1 ){
cha += pass[i];
i = (i+1)%lenpass;
}

fputc(cha,merg);
}
fcloseall();
return 0;
}
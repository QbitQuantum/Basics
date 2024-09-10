int main(int argc, char **argv)
{
	FILE *infile = NULL;
	FILE *outfile = NULL;
	unsigned char *buffer = NULL;
	unsigned char *keybuf = key;
	int len=0, i=0, keynum=0, method=0;
	
	if(argc<3)
	{
		printf("usage: %s infile outfile (optional: keynum(1, 2, 3))\n",argv[0]);
		return 0;
	}
	
	infile = fopen(argv[1],"rb");
	
	if(!infile)
	{
		printf("Could not open %s\n",argv[1]);
		return -1;
	}
	
	if(argc==4)
	{
		keynum = atoi(argv[3])-1;
		
		if(keynum<0 || keynum>2)
		{
			printf("Invalid key, range is 1-3\n");
			return -2;
		}
	}
	
	fseek(infile,0,SEEK_END);
	len = ftell(infile);
	rewind(infile);
	
	buffer = (unsigned char*)calloc(len,sizeof(unsigned char));
	
	if(buffer==NULL)
	{
		printf("Could not allocate %d bytes for the buffer\n",len);
		return -3;
	}
	
	fread(buffer,1,len,infile);
	
	/*
		Encryption:
		
		00404A27   33C9             XOR ECX,ECX
		00404A29   8BC1             MOV EAX,ECX
		00404A2B   99               CDQ
		00404A2C   F7FB             IDIV EBX
		00404A2E   8A0439           MOV AL,BYTE PTR DS:[ECX+EDI]
		00404A31   8A92 D4B25B00    MOV DL,BYTE PTR DS:[EDX+5BB2D4]
		00404A37   02D1             ADD DL,CL
		00404A39   2AC2             SUB AL,DL
		00404A3B   880439           MOV BYTE PTR DS:[ECX+EDI],AL
		00404A3E   41               INC ECX
		00404A3F   81F9 00A0DA00    CMP ECX,AIKAEN.00DAA000
		00404A45  ^7C E2            JL SHORT AIKAEN.00404A29
	*/
	
	if(argc!=4) /* key search */
	{
		int found=0, x=0;
		
		printf("Attempting to determine which key to use for decryption...\n");
		
		for(x=0; x<3; x++)
		{
			found = 1;
			
			for(i=0; i<0x10; i++)
			{
				if(buffer[i] - (keybuf[i%keylen[x]] + i) != 0)
				{
					found = 0;
					break;
				}
			}
		
			if(found==1)
			{
				printf("Key %d seems likely. If the results are incorrect then you can manually set the key by passing the key number as an argument.\n",x);
				
				keynum = x;
				break;
			}
				
			keybuf += keylen[x];
		}
		
		if(found==0)
		{
			printf("It seems like none of the keys worked. This could possibly be a new encryption key or an incorrect file.\nHere's a hex dump of the first 0x40 bytes to help you determine which it is:\n\n");
		
			for(i=0; i<0x40; i+=0x10)
			{
				printf("%08x\t",i);
				
				for(x=i; x<i+0x10; x++)
					printf("%02x ",buffer[x]);
					
				printf("\n");
			}
			
			if(buffer[0]==0 && buffer[1]==1 && buffer[2]==2 && buffer[3]==3)
			{
				method = 1;
				printf("\nDetected as possibly not using a key\n");
			}
			else if(buffer[0]==0 && buffer[1]==0 && buffer[2]==0 && buffer[3]==0)
			{
				printf("\nThis doesn't look like an encrypted file, exiting...");
				return -5;
			}
			else
			{
				printf("\nDefaulting to key 1...\n");
				keynum = 0;
			}
			//return -4;
		}
	}
	else
	{
		for(i=0; i<keynum; i++)
			keybuf += keylen[i];
	}
	
	for(i=0; i<len; i++)
	{
			buffer[i] -= i%5;
	}
	
	outfile = fopen(argv[2],"wb");
	fwrite(buffer,1,len,outfile);
	
	free(buffer);
	fclose(infile);
	fclose(outfile);
	
	return 0;
}
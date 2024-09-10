void unpackStrings(int game)
{
char filePath[255];
switch (game)
	{
	case UWDEMO:
	case UW1:
		strcpy_s(filePath, UW1_STRINGS_FILE);break;	
	case UW2:
		strcpy_s(filePath, UW2_STRINGS_FILE);break;	
	case SHOCK:
		strcpy_s(filePath, SHOCK_STRINGS_FILE);break;	
	}
huffman_node *hman;
block_dir *blocks;
unsigned char *Buffer;
long NoOfNodes; long NoOfStringBlocks;
long address_pointer=0;
//char *str;

	FILE *file = NULL;      // File pointer
	//fopen_s(file,filePath, "rb");
    if (fopen_s(&file,filePath, "rb") != 0)
        {
        printf("Could not open specified file\n");
        }
	else
		{
		// Get the size of the file in bytes
		long fileSize = getFileSize(file);
	 
		// Allocate space in the buffer for the whole file
	    
		Buffer = new unsigned char[fileSize];
		fread(Buffer, fileSize, 1,file);
		fclose(file);
		NoOfNodes=getValAtAddress(Buffer,address_pointer,16);
		int i=0;
		hman = new huffman_node [NoOfNodes];
		address_pointer=address_pointer+2;
		while (i<NoOfNodes)
			{
			hman[i].symbol= Buffer[address_pointer+0];
			hman[i].parent= Buffer[address_pointer+1];
			hman[i].left= Buffer[address_pointer+2];
			hman[i].right= Buffer[address_pointer+3];
			printf("Node:%d parent=%d, left=%d, right=%d, symbol=%c\n",i,hman[i].parent, hman[i].left, hman[i].right, hman[i].symbol);
			i++;
			address_pointer=address_pointer+4;
			}
		//next is the number of string blocks
		NoOfStringBlocks=getValAtAddress(Buffer,address_pointer,16);
		blocks=new block_dir[NoOfStringBlocks];
		address_pointer=address_pointer+2;
		i=0;
		while (i<NoOfStringBlocks)
			{
			blocks[i].block_no = getValAtAddress(Buffer,address_pointer,16);
			address_pointer=address_pointer+2;
			blocks[i].address = getValAtAddress(Buffer,address_pointer,32);	
			address_pointer=address_pointer+4;
			blocks[i].NoOfEntries = getValAtAddress(Buffer,blocks[i].address,16);	//look ahead and get no of entries.
			
			i++;
			}
		i=0;	
		while (i<NoOfStringBlocks)
			{
			//printf("Block %d is at address %d. It has %d entries\n",blocks[i].block_no,blocks[i].address, blocks[i].NoOfEntries );
			address_pointer=2 + blocks[i].address + blocks[i].NoOfEntries *2;
			//printf("It's strings begin at %d\n", address_pointer);
			//printf("It should end at %d\n",blocks[i+1].address );
			printf("\n+=====================================+\n");
			printf("Block Name: %d\n", blocks[i].block_no);
			long strAdd;
			int blnFnd;
			strAdd= address_pointer;
			for (int j=0;j< blocks[i].NoOfEntries;j++)
			{
				//Based on abysmal /uwadv implementations.
				blnFnd=0;
				char c;
				
				int bit = 0;
				int raw = 0;
				int node=0;
				do {
					node = NoOfNodes - 1; // starting node

					// huffman tree decode loop
					while (char(hman[node].left) != -1
						&& char(hman[node].right) != -1)
					{

						if (bit == 0) {
							bit = 8;
							raw = Buffer[address_pointer++];	//stream.get<uint8_t>();
						}

						// decide which node is next
						node = raw & 0x80 ? short (hman[node].right)
							   : short (hman[node].left);

						raw <<= 1;
						bit--;
					}

					// have a new symbol
					if ((hman[node].symbol !='|') && (hman[node].symbol !=10)){
						if (blnFnd==0)
							//{printf("\nBlock %d String %d at %d:",blocks[i].block_no, j, strAdd);	}
							{printf("\n%03d=",j);	}
						printf("%c",hman[node].symbol);
						blnFnd = 1;
					}
				} while (hman[node].symbol != '|');		
			}
			i++;
			}	
		}
}
int main(int argc, char **argv)
{
	FILE *hexfile = NULL;
	long fsize = 0;
	nibstor *nibbles = NULL;
	long nibblenum = 0;
	int byte = 0;
	char hilo = -1;
	int i = 0;
	int j = 0;
	int k = 0;
	int inststart = 0;
	unsigned char inst[5];
	uint16_t addr = 0;
	uint8_t args = 0;

	if(argc < 2)
	{
		return 0;
	}
	if(!strcmp("-i", argv[1]))
	{
		if(argc < 3)
		{
			return 0;
		}
		return interactive(argv[2]);
	}
	hexfile = fopen(argv[1], "rb");
	if(hexfile == NULL)
	{
		perror("Could not open hexfile");
		return 1;
	}
	
	fseek(hexfile, 0, SEEK_END);
	fsize = ftell(hexfile);
	if(fsize == 0)
	{
		fprintf(stderr, "File size is zero!\n");
		return 2;
	}
	rewind(hexfile);

	nibbles = calloc(sizeof(nibstor), fsize + 1);
	if(nibbles == NULL)
	{
		perror("Could not allocate memory");
		return 3;
	}

	byte = fgetc(hexfile);
	hilo = 0;
	while(byte != EOF)
	{
		nibbles[i].hi = (char)((byte >> 4) & 0xF);
		nibbles[i].lo = (char)(byte & 0xF);
		i++;
		byte = fgetc(hexfile);
	}
	nibblenum = i;
	fclose(hexfile);
	printf("      ");
	for(i = 0; i < 5; i++)
	{
		printf("%X ", i);
	}
	puts("");
	printf("%04X: ", 0);
	for(i = 0; i < nibblenum; i++)
	{
		printf("%X ", nibbles[i].hi);
		inst[k] = nibbles[i].hi;
		k++;
		j++;
		if((j % 5) == 0)
		{
			k = 0;
			printf("   ");
			printdisasm(inst);
			puts("");
			printf("%04X: ", j);
		}
		printf("%X ", nibbles[i].lo);
		inst[k] = nibbles[i].lo;
		k++;
		j++;
		if((j % 5) == 0)
		{
			k = 0;
			printf("   ");
			printdisasm(inst);
			if(i+1 != nibblenum)
			{
				puts("");
				printf("%04X: ", j);
			}
		}
	}
	if(k != 0)
	{
		printf("   ");
		for(i = 0; i < (5-k); i++)
		{
			printf("  ");
		}
		printf(".data %i 0x", k);
		for(i = 0; i < k; i++)
		{
			printf("%X", inst[i]);
		}
		puts("");
	}
	free(nibbles);
	return 0;
}
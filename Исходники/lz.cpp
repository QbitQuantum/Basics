int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		puts("Usage: ");
		printf("    Compress : %s c sourcefile destfile\n", argv[0]);
		printf("  Decompress : %s d sourcefile destfile\n", argv[0]);
		return 0;
	}

	BYTE soubuf[65536];
	BYTE destbuf[65536 + 16];

	FILE* in;
	FILE* out;
	//打开源文件
	in = fopen(argv[2], "rb");
	if (in == NULL)
	{
		puts("Can't open source file");
		return 0;
	}
	//打开目标文件
	out = fopen(argv[3], "wb");
	if (out == NULL)
	{
		puts("Can't open dest file");
		fclose(in);
		return 0;
	}
	fseek(in, 0, SEEK_END);
	long soulen = ftell(in);
	fseek(in, 0, SEEK_SET);

	SortHeap = new struct STIDXNODE[_MAX_WINDOW_SIZE];


	WORD flag1, flag2;
	
	if (argv[1][0] == 'c') // 对源文件进行压缩
	{
		int last = soulen, act;
		while ( last > 0 )
		{
			act = min(65536, last);
			fread(soubuf, act, 1, in);
			last -= act;
			if (act == 65536)			// 超过65536字节
				flag1 = 0;		
			else					
				flag1 = act;
			fwrite(&flag1, sizeof(WORD), 1, out);

			int destlen = compress((BYTE*)soubuf, act, (BYTE*)destbuf);
			if (destlen == 0)		// 不能压缩块
			{
				flag2 = flag1;
				fwrite(&flag2, sizeof(WORD), 1, out);
				fwrite(soubuf, act, 1, out);
			}
			else
			{
				flag2 = (WORD)destlen;
				fwrite(&flag2, sizeof(WORD), 1, out);				
				fwrite(destbuf, destlen, 1, out);				
			}
		}
	}
	else if (argv[1][0] == 'd') // 解压缩源文件
	{
		int last = soulen, act;
		while (last > 0)
		{
			fread(&flag1, sizeof(WORD), 1, in);
			fread(&flag2, sizeof(WORD), 1, in);
			last -= 2 * sizeof(WORD);
			if (flag1 == 0)
				act = 65536;
			else
				act = flag1;
			last-= flag2 ? (flag2) : act;

			if (flag2 == flag1)
			{
				fread(soubuf, act, 1, in);				
			}
			else
			{
				fread(destbuf, flag2, 1, in);
				if (!decompress((BYTE*)soubuf, act, (BYTE*)destbuf))
				{
					puts("Decompress error");
					fclose(in);
					fclose(out);
					return 0;
				}
			}
			fwrite((BYTE*)soubuf, act, 1, out);				
		}
	}
	else
	{
		puts("Usage: ");
		printf("  Compress : %s c sourcefile destfile\n", argv[0]);
		printf("  Decompress : %s d sourcefile destfile\n", argv[0]);		
	}
	//关闭源文件和目标文件
	fclose(in);
	fclose(out);
	return 0;
}
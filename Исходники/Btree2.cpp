void LoadFromTheFileAndSave(char *source, char *destination)
{
	FILE *norfile, *binfile;
	errno_t e = fopen_s(&norfile, source, "r+");
	errno_t e1 = fopen_s(&binfile, "s.bin", "wb+");
	char stringdata[64];
	char name[24];
	char college[24];
	int rollno;
	struct LeafPage l;
	int data_offset = 0;
	struct Student s;
	struct NonLeafPage n;
	memset(&n, 0, sizeof(struct NonLeafPage));
	struct TableSector t;
	int BlocksCount = 1;
	int tableOffset = 0;
	int of_offsets = 0, key_offset = 0;
	if (e1 != 0 || e != 0)
	{
		printf("e1=%d\te2=%d\n", e, e1);
		printf("Error while loading pages");
		return;
	}
	while (!feof(norfile))
	{
		fgets(stringdata, 64, norfile);
		separateValues1(stringdata, name, college, &rollno);
		strcpy_s(s.clgname, college);
		strcpy_s(s.name, name);
		s.rollno = rollno;
		l.data[data_offset++] = s;
		if (data_offset == 10)
		{
			l.pagetype = 1;
			fseek(binfile, (BlocksCount*blocksize), SEEK_SET);
			l.pagetype = 1;
			l.tableid = 1;
			fwrite(&l, sizeof(struct LeafPage), 1, binfile);
			n.offsets[of_offsets++] = BlocksCount*blocksize;
			BlocksCount++;
			n.keys[key_offset++] = l.data[9].rollno + 1;
			if (of_offsets > 1)
			{
				n.offsets[0] = 512;
				n.pagetype = 2;
				fwrite(&n, sizeof(struct NonLeafPage), 1, binfile);
				//printf(" Non Leaf Block Count=%d\n", BlocksCount);
				BlocksCount++;
			}
			t.tableIds[tableOffset] = 1;
			t.rootNodeIds[tableOffset] = (BlocksCount-1)*blocksize;
			data_offset = 0;
		}
	}
	printf("Blocks Count=%d\n", BlocksCount);
	printf("table id=%d \t table root=%d\n", t.tableIds[0], t.rootNodeIds[0]);
	fseek(binfile, 0, SEEK_SET);
	fwrite(&t, sizeof(struct TableSector), 1, binfile);
	_fcloseall();
}
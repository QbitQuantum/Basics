int _tmain(int argc, _TCHAR* argv[])
{
	char* smol = "qwertyuiopasdfghjklzxcvbnm";
	FILE* fp = 0;
	fopen_s(&fp, "XD_fail.txt", "r");
	char output[51];
	char** aw = new char*[100];
	int nw = 0, ni = 0;//ni число слов содержащие не только маленькие буквы буквы
	do{
		fgets(output, 50, fp);
		if (feof(fp)) break;  //Истинный выход
		if (output[strlen(output) - 1] == '\n')    	output[strlen(output) - 1] = '\0';
		char* next_p;
		char p = strtok_s(output, " ,.-?!()#[]<>{};*=", &next_p);
		while (p){
				//	cout << p << endl;
			aw[nw] = new char[strlen(p)];
			for (int i = 0; i <= strlen(p); ++i)
				aw[nw][i] = p[i];
			nw++;
			int a=0, b=0;
			for (int i = 0; i < strlen(p); i++)
			{
				char* SmolCh = copyStr(p, i, 1);
				if (strstr(smol, SmolCh))a++; else b++;
			}
			if ((a != 0)&(b != 0)) ni++;
				p = strtok_s(0, " ,.-?!()#[]<>{};*=", &next_p);
		}
	} while (true);
	
	fclose(fp);
	cout << "**** Result ****" << endl;
	_itoa_s(ni, output, 50, 10);
	aw[nw] = output;
	for (int i = 0; i < nw; ++i) cout << aw[i] << endl;
	fp = 0;
	
	fopen_s(&fp, "XD_fail.txt", "a");
fputs(aw[nw], fp); fputs("\n", fp);
	fclose(fp);
	/*char str[10];
	ifstream b_file("XD_fail.txt");
	while (!b_file.eof())
	{
		b_file >> str;
		cout << str << " ";
	}
	cin.get();*/

	return 0;
}
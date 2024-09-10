bool DeckManager::LoadDeck(const wchar_t* file) {
	int sp = 0, ct = 0, mainc = 0, sidec = 0, code;
	wchar_t deck[64];
	myswprintf(deck, L"./deck/%ls.ydk", file);
	int cardlist[128];
	bool is_side = false;
#ifdef WIN32
	FILE* fp = _wfopen(deck, L"r");
#else
	char deckfn[256];
	BufferIO::EncodeUTF8(deck, deckfn);
	FILE* fp = fopen(deckfn, "r");
#endif
	if(!fp)
		return false;
	char linebuf[256];
	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fgets(linebuf, 256, fp);
	while(ftell(fp) < fsize && ct < 128) {
		fgets(linebuf, 256, fp);
		if(linebuf[0] == '!') {
			is_side = true;
			continue;
		}
		if(linebuf[0] < '0' || linebuf[0] > '9')
			continue;
		sp = 0;
		while(linebuf[sp] >= '0' && linebuf[sp] <= '9') sp++;
		linebuf[sp] = 0;
		code = atoi(linebuf);
		cardlist[ct++] = code;
		if(is_side) sidec++;
		else mainc++;
	}
	fclose(fp);
	LoadDeck(current_deck, cardlist, mainc, sidec);
	return true;
}
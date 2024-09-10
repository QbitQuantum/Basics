	bool KeyMagicKeyboard::ReadHeader(FILE * hFile, FileHeader * fh) {
		
		fread(fh, sizeof(FileHeader), 1, hFile);

		if (fh->magicCode[0] != 'K' || fh->magicCode[1] != 'M' || fh->magicCode[2] != 'K' || fh->magicCode[3] != 'L') {
			PERROR("Not KeyMagic keyboard file.\n");
			return false;
		}

		if (fh->majorVersion > MAJOR_VERSION) {
			PERROR("Can't load newer version of keyboard file.\n");
			return false;
		}

		if (fh->minorVersion > MINOR_VERSION) {
			PERROR("Can't load newer version of keyboard file.\n");
			return false;
		}

		if (fh->majorVersion == MAJOR_VERSION && fh->minorVersion == MINOR_VERSION) {
			return true;
		}

		// if older version 1.4
		if (fh->majorVersion == 1) {
			if (fh->minorVersion == 4) {
				FileHeader_1_4 fh14;
				fseek(hFile, 0, SEEK_SET);
				// read the header back
				fread(&fh14, sizeof(FileHeader_1_4), 1, hFile);
				// backward compability
				fh->stringCount = fh14.stringCount;
				fh->infoCount = fh14.infoCount;
				fh->ruleCount = fh14.ruleCount;
				
				fh->layoutOptions.trackCaps = fh14.layoutOptions.trackCaps;
				fh->layoutOptions.autoBksp = fh14.layoutOptions.autoBksp;
				fh->layoutOptions.eat = fh14.layoutOptions.eat;
				fh->layoutOptions.posBased = fh14.layoutOptions.posBased;
				fh->layoutOptions.rightAlt = true; // 1.4 dont have this option
			}
			else if (fh->minorVersion == 3) {
				FileHeader_1_3 fh13;
				fseek(hFile, 0, SEEK_SET);
				// read the header back
				fread(&fh13, sizeof(FileHeader_1_3), 1, hFile);
				// backward compability
				fh->stringCount = fh13.stringCount;
				fh->ruleCount = fh13.ruleCount;
				
				fh->layoutOptions.trackCaps = fh13.layoutOptions.trackCaps;
				fh->layoutOptions.autoBksp = fh13.layoutOptions.autoBksp;
				fh->layoutOptions.eat = fh13.layoutOptions.eat;
				fh->layoutOptions.posBased = fh13.layoutOptions.posBased;
				fh->layoutOptions.rightAlt = true; // 1.3 dont have this option
				
				fh->infoCount = 0; // 1.3 dont have infos, so set it to 0
			}
		}

		return true;
	}
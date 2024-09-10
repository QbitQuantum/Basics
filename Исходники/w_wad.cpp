void FWadCollection::AddFile (const char *filename, FileReader *wadinfo)
{
	int startlump;
	bool isdir = false;

	if (wadinfo == NULL)
	{
		// Does this exist? If so, is it a directory?
		struct stat info;
		if (stat(filename, &info) != 0)
		{
			Printf(TEXTCOLOR_RED "Could not stat %s\n", filename);
			PrintLastError();
			return;
		}
		isdir = (info.st_mode & S_IFDIR) != 0;

		if (!isdir)
		{
			try
			{
				wadinfo = new FileReader(filename);
			}
			catch (CRecoverableError &err)
			{ // Didn't find file
				Printf (TEXTCOLOR_RED "%s\n", err.GetMessage());
				PrintLastError ();
				return;
			}
		}
	}

	Printf (" adding %s", filename);
	startlump = NumLumps;

	FResourceFile *resfile;
	
	if (!isdir)
		resfile = FResourceFile::OpenResourceFile(filename, wadinfo);
	else
		resfile = FResourceFile::OpenDirectory(filename);

	if (resfile != NULL)
	{
		DWORD lumpstart = LumpInfo.Size();

		resfile->SetFirstLump(lumpstart);
		for (DWORD i=0; i < resfile->LumpCount(); i++)
		{
			FResourceLump *lump = resfile->GetLump(i);
			FWadCollection::LumpRecord *lump_p = &LumpInfo[LumpInfo.Reserve(1)];

			lump_p->lump = lump;
			lump_p->wadnum = Files.Size();
		}

		if (Files.Size() == IWAD_FILENUM && gameinfo.gametype == GAME_Strife && gameinfo.flags & GI_SHAREWARE)
		{
			resfile->FindStrifeTeaserVoices();
		}
		Files.Push(resfile);

		for (DWORD i=0; i < resfile->LumpCount(); i++)
		{
			FResourceLump *lump = resfile->GetLump(i);
			if (lump->Flags & LUMPF_EMBEDDED)
			{
				FString path;
				path.Format("%s:%s", filename, lump->FullName.GetChars());
				FileReader *embedded = lump->NewReader();
				AddFile(path, embedded);
			}
		}

		if (hashfile)
		{
			BYTE cksum[16];
			char cksumout[33];
			memset(cksumout, 0, sizeof(cksumout));

			FileReader *reader = wadinfo;

			if (reader != NULL)
			{
				MD5Context md5;
				reader->Seek(0, SEEK_SET);
				md5.Update(reader, reader->GetLength());
				md5.Final(cksum);

				for (size_t j = 0; j < sizeof(cksum); ++j)
				{
					sprintf(cksumout + (j * 2), "%02X", cksum[j]);
				}

				fprintf(hashfile, "file: %s, hash: %s, size: %ld\n", filename, cksumout, reader->GetLength());
			}

			else
				fprintf(hashfile, "file: %s, Directory structure\n", filename);

			for (DWORD i = 0; i < resfile->LumpCount(); i++)
			{
				FResourceLump *lump = resfile->GetLump(i);

				if (!(lump->Flags & LUMPF_EMBEDDED))
				{
					reader = lump->NewReader();

					MD5Context md5;
					md5.Update(reader, lump->LumpSize);
					md5.Final(cksum);

					for (size_t j = 0; j < sizeof(cksum); ++j)
					{
						sprintf(cksumout + (j * 2), "%02X", cksum[j]);
					}

					fprintf(hashfile, "file: %s, lump: %s, hash: %s, size: %d\n", filename,
						lump->FullName.IsNotEmpty() ? lump->FullName.GetChars() : lump->Name,
						cksumout, lump->LumpSize);

					delete reader;
				}
			}
		}
		return;
	}
}
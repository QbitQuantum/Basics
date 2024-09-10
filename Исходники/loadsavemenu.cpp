unsigned FSavegameManager::ExtractSaveData(int index)
{
	FResourceFile *resf;
	FSaveGameNode *node;

	if (index == -1)
	{
		if (SaveGames.Size() > 0 && SaveGames[0]->bNoDelete)
		{
			index = LastSaved + 1;
		}
		else
		{
			index = LastAccessed < 0? 0 : LastAccessed;
		}
	}

	UnloadSaveData();

	if ((unsigned)index < SaveGames.Size() &&
		(node = SaveGames[index]) &&
		!node->Filename.IsEmpty() &&
		!node->bOldVersion &&
		(resf = FResourceFile::OpenResourceFile(node->Filename.GetChars(), true)) != nullptr)
	{
		FResourceLump *info = resf->FindLump("info.json");
		if (info == nullptr)
		{
			// this should not happen because the file has already been verified.
			return index;
		}
		void *data = info->CacheLump();
		FSerializer arc(nullptr);
		if (arc.OpenReader((const char *)data, info->LumpSize))
		{
			FString comment;

			FString time = arc.GetString("Creation Time");
			FString pcomment = arc.GetString("Comment");

			comment = time;
			if (time.Len() > 0) comment += "\n";
			comment += pcomment;
			SaveCommentString = comment;

			// Extract pic
			FResourceLump *pic = resf->FindLump("savepic.png");
			if (pic != nullptr)
			{
				FileReader picreader;

				picreader.OpenMemoryArray([=](TArray<uint8_t> &array)
				{
					auto cache = pic->CacheLump();
					array.Resize(pic->LumpSize);
					memcpy(&array[0], cache, pic->LumpSize);
					pic->ReleaseCache();
					return true;
				});
				PNGHandle *png = M_VerifyPNG(picreader);
				if (png != nullptr)
				{
					SavePic = PNGTexture_CreateFromFile(png, node->Filename);
					delete png;
					if (SavePic && SavePic->GetDisplayWidth() == 1 && SavePic->GetDisplayHeight() == 1)
					{
						delete SavePic;
						SavePic = nullptr;
						SavePicData.Clear();
					}
				}
			}
		}
		delete resf;
	}
	return index;
}
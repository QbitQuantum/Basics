void
delete_directory_path(char *path,bool recur)
{
	BDirectory 	*dir;
	BPath		*pat,pt;
	BEntry		*ent;

	if ((pat = create_path(path)))
	{
		if	((dir = create_mydir((char *)pat->Path())))
		{
			if	(dir->Rewind() == B_OK)
			{
				if	((ent = new BEntry()))
				{
					while (dir->GetNextEntry(ent,false) == B_NO_ERROR)
					{
						if (ent->GetPath(&pt) == B_NO_ERROR)
						{
							if (recur)
							{
								if	(ent->IsDirectory())
								{
									delete_directory_path((char *)pt.Path(),recur);
								}
							}
						}

						ent->Remove();
					}

					delete ent;
				}
			}

			delete dir;
		}

		delete pat;
	}
}
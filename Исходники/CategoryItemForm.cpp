result
CategoryItemForm::ReadCustomListItems()
{
	result r = E_SUCCESS;
	String dirName(L"/Home/catalog/"+dir);
	Directory* pDir;
	DirEnumerator* pDirEnum;

	pDir = new Directory; // allocate Directory instance

	// Open directory
	r = pDir->Construct(dirName);

	// Read all directory entries
	pDirEnum = pDir->ReadN();

	String contentType;
	int i = 0;
	while(pDirEnum->MoveNext() == E_SUCCESS) {
		DirEntry dirEntry = pDirEnum->GetCurrentDirEntry();
		if(dirEntry.IsNomalFile()) {
			//AppLog("%S", dirEntry.GetName().GetPointer());
			if(!dirEntry.GetName().Equals("category.info", false)) {

				String fileName(dirName+"/"+dirEntry.GetName());

				String title, desc;
				String iTempStr, iTempStr2;

				File file;
				result r = file.Construct(fileName, L"r");
				if( IsFailed(r) )
				{
						AppLog("File::Consturct() is failed by %s", GetErrorMessage(r));
				}

				FileAttributes fileAttrs;
				file.GetAttributes(fileName, fileAttrs);
				long long size = fileAttrs.GetFileSize();


				ByteBuffer readBuffer;
				readBuffer.Construct((int)size + 1);

				r = file.Read(readBuffer);
				if( IsFailed(r) )
				{
						AppLog("File::Read() is failed by %s", GetErrorMessage(r));
				}

				char* data = new char[readBuffer.GetLimit()+1];
				readBuffer.SetPosition(0);
				readBuffer.GetArray((byte*)data, 0, readBuffer.GetLimit());
				data[readBuffer.GetLimit()] ='\0';
				//String str = String(data);

				String str;
				r = StringUtil::Utf8ToString(data, str);
				delete data;
				if(IsFailed(r)) {
					AppLog("File read error. File : %S", fileName.GetPointer());
					continue;
				}

				file.Seek(FILESEEKPOSITION_BEGIN, 0);
				file.Read(title);

				r = TextPic::GetTranslated(title);
				if (IsFailed(r)) {
					continue;
				}

				int linecount = 0;
				while(file.Read(iTempStr) != E_END_OF_FILE) {
					linecount++;
					iTempStr2.Append(iTempStr);
				}

				anciilist.Add(*(new String(iTempStr2)));
				titlelist.Add(*(new String(title)));
				filelist.Add(*(new String(fileName)));

				ItemListForm::AddListItem(*CategoryList, title, iTempStr2, i++, linecount);
				file.Flush();
			}
		}
	}

	delete pDirEnum;
	delete pDir;

	return r;
}
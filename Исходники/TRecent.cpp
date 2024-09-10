//---------------------------------------------------------------------------
//Called by user to indicate that file have been used
void __fastcall TRecent::FileUsed(const String &FileName)
{
  if(FMaxFiles)
  {
    RemoveMenuItems();//Remove shown menu items
    ReadFromRegistry();//Read data to get changes made by other version of program
    int Index = FileIndex(FileName);//Get index of FileName in list
    if(Index == -1)//If FileName not in list
    {
      if(FileList.size() == static_cast<unsigned>(FMaxFiles))//If list is full
        FileList.pop_back();//Erase last file name in list
    }
    else
      FileList.erase(FileList.begin() + Index);//Remove FileName from list

    FileList.push_front(std::pair<String, TActionClientItem*>(FileName, NULL));//Add FileName to start of list
    SaveToRegistry();//Write new file list to registry
    ShowMenuItems();//Show new list of menu items
  }
  
  //Add Filename to recent documents list in the start menu
  if(FAddToRecentDocs)
    SHAddToRecentDocs(SHARD_PATH, FileName.c_str());
}
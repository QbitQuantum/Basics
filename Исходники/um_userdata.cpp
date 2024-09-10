void AddDefaultUserdata(PluginPanelItem* Item,int level,int sortorder,int itemtype,PSID sid,const wchar_t* wide_name,const wchar_t* filename)
{
  TCHAR* item_filename=(TCHAR*)malloc((_tcslen(filename)+1)*sizeof(TCHAR));
  Item->FileName=item_filename;
  if(item_filename)
  {
    if(item_filename) _tcscpy(item_filename,filename);
  }
  PluginUserData *user_data;
  int user_data_size=sizeof(PluginUserData),sid_size=0,name_size=0;
  if(sid&&IsValidSid(sid))
    sid_size=GetLengthSid(sid);
  name_size=(wcslen(wide_name)+1)*sizeof(wchar_t);
  user_data_size+=sid_size+name_size;

  user_data=(PluginUserData *)malloc(user_data_size);
  if(user_data)
  {
    user_data->size=user_data_size;
    user_data->level=level;
    user_data->sortorder=sortorder;
    user_data->itemtype=itemtype;
    if(sid_size)
    {
      CopySid(sid_size,(PSID)(user_data+1),sid);
      user_data->user_diff=sizeof(PluginUserData);
    }
    if(name_size)
    {
      wchar_t *ptr=(wchar_t *)((char *)(user_data+1)+sid_size);
      user_data->wide_name_diff=sizeof(PluginUserData)+sid_size;
      wcscpy(ptr,wide_name);
    }
    Item->UserData.FreeData=FreeUserData;
    Item->UserData.Data=user_data;
  }
}
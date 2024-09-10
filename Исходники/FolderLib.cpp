void CFolderHelper::GenerateObjectName(TElTree* tv, TElTreeItem* node, AnsiString& name,AnsiString pref, bool num_first)
{
    int cnt = 0;
    if (num_first) name.sprintf("%s_%02d",pref,cnt++); else name = pref;
    while (FindItemInFolder(TYPE_OBJECT,tv,node,name))
    	name.sprintf("%s_%02d",pref,cnt++);
}
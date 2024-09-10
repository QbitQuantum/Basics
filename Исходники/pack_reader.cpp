static PackFile *PackOpen(char *name)
{
    FILE *fp;
    char tmp[MAX_PATH];

    RemoveExt(tmp, name);
    StrCat(tmp, MAX_PATH, ".txt");
    fp = FOpen(tmp, "r");
    if (fp) {
        fgets(tmp, MAX_PATH, fp);
        FClose(fp);
        packFile = FOpen(tmp, "rb");
        return PackOpenFromFile(tmp);        
    }
    packFile = FOpen(name, "rb");
    return PackOpenFromFile(name);
}    
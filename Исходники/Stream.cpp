void listsubdirs(const char *dir, vector<char *> &subdirs, int (__cdecl *sf)(const char **, const char **))
{
    listsubdir(dir, subdirs);
    string s;
    if(homedir[0])
    {
        formatstring(s)("%s%s", homedir, dir);
        listsubdir(s, subdirs);
    }
    loopv(packagedirs)
    {
        formatstring(s)("%s%s", packagedirs[i], dir);
        listsubdir(s, subdirs);
    }
#ifndef STANDALONE
    listzipdirs(dir, subdirs);
#endif
    subdirs.sort(sf);
    for(int i = subdirs.length() - 1; i > 0; i--)
    { // remove doubles
        if(!strcmp(subdirs[i], subdirs[i - 1])) delstring(subdirs.remove(i));
    }
}
    bool readDir(const ConstString& dirname, ACE_DIR *&dir, String& result) {
        bool ok = true;

        struct YARP_DIRENT **namelist;
        YARP_closedir(dir);
        dir = NULL;
        int n = YARP_scandir(dirname.c_str(),&namelist,NULL,YARP_alphasort);
        if (n<0) {
            return false;
        }
        for (int i=0; i<n; i++) {
            ConstString name = namelist[i]->d_name;
            free(namelist[i]);
            int len = (int)name.length();
            if (len<4) continue;
            if (name.substr(len-4)!=".ini") continue;
            ConstString fname = ConstString(dirname) + "/" + name;
            ok = ok && readFile(fname,result,false);
            result += "\n[]\n";  // reset any nested sections
        }
        free(namelist);

        /*
        struct YARP_DIRENT *ent = YARP_readdir(dir);
        while (ent) {
            ConstString name = ent->d_name;
            ent = ACE_OS::readdir(dir);
            int len = (int)name.length();
            if (len<4) continue;
            if (name.substr(len-4)!=".ini") continue;
            ConstString fname = dirname + "/" + name;
            ok = ok && readFile(fname,result,false);
            result += "\n[]\n";  // reset any nested sections
        }
        YARP_closedir(dir);
        dir = NULL;
        */
        return ok;
    }
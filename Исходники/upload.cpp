int main(int argc, char** argv)
{
   if (argc < 3)
   {
      cerr << "usage: upload <src file/dir> <dst dir>" << endl;
      return 0;
   }

   Sector client;
   if (Utility::login(client) < 0)
      return -1;

   string newdir = argv[argc - 1];
   SNode attr;
   int r = client.stat(newdir, attr);
   if ((r < 0) || (!attr.m_bIsDir))
   {
      cerr << "destination directory on Sector does not exist.\n";
      Utility::logout(client);
      return -1;
   }

   bool success = true;

   for (int i = 1; i < argc - 1; ++ i)
   {
      vector<string> fl;
      string path = argv[1];
#ifdef WIN32
      win_to_unix_path (path);
#endif
      bool wc = WildCard::isWildCard(path.c_str());
      if (!wc)
      {
         struct stat st;
         if (stat(argv[i], &st) < 0)
         {
            cerr << "ERROR: source file does not exist.\n";
            return -1;
         }
         getFileList(argv[i], fl);
      }
      else
      {
         string path = argv[i];
#ifdef WIN32
         win_to_unix_path (path);
#endif
         string orig = path;
         size_t p = path.rfind('/');
         if (p == string::npos)
         {
            path = ".";
         }
         else
         {
            path = path.substr(0, p);
            orig = orig.substr(p + 1, orig.length() - p);
         }

         dirent **namelist;
         int n = scandir(path.c_str(), &namelist, 0, alphasort);

         if (n < 0)
            return -1;

         for (int i = 0; i < n; ++ i)
         {
            // skip "." and ".." and hidden directory
            if (namelist[i]->d_name[0] == '.')
            {
               free(namelist[i]);
               continue;
            }

            if (WildCard::match(orig, namelist[i]->d_name))
            {
               if (path == ".")
                  getFileList(namelist[i]->d_name, fl);
               else
                  getFileList(path + "/" + namelist[i]->d_name, fl);
            }
         }
      }

      string olddir;
      string input_path = argv[1];
#ifdef WIN32
      win_to_unix_path (input_path);
#endif
      for (int j = input_path.length() - 1; j >= 0; -- j)
      {
         if (input_path[j] != '/')
         {
            olddir = input_path.substr(0, j);
            break;
         }
      }
      size_t p = olddir.rfind('/');
      if (p == string::npos)
         olddir = "";
      else
         olddir = olddir.substr(0, p);

      for (vector<string>::const_iterator i = fl.begin(); i != fl.end(); ++ i)
      {
         string dst = *i;
         if (olddir.length() > 0)
            dst.replace(0, olddir.length(), newdir);
         else
            dst = newdir + "/" + dst;

         struct stat s;
         if (stat(i->c_str(), &s) < 0)
            continue;

         if (S_ISDIR(s.st_mode))
            client.mkdir(dst);
         else
         {
            if (upload(i->c_str(), dst.c_str(), client) < 0)
               success = false;
         }
      }
   }

   Utility::logout(client);

   return success ? 0 : -1;
}
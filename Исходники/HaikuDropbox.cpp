/*
* Given a single line of the output of db_delta.py
* Figures out what to do and does it.
* (adds and removes files and directories)
*/
int
App::parse_command(BString command)
{
  command.RemoveAll("\n"); //remove trailing whitespace
  if(command.Compare("RESET") == 0)
  {
    printf("Burn Everything. 8D\n");

    status_t err = stop_watching(be_app_messenger);
    if(err != B_OK) printf("stop_watching error: %s\n",strerror(err));

    BDirectory dir = BDirectory(local_path_string);
    rm_rf(&dir);

    BString str = BString("/"); //create_local_path wants a remote path 
    create_local_directory(&str);

    this->recursive_watch(&dir);
  }
  else if(command.Compare("FILE ",5) == 0)
  {
    BString path, dirpath, partial_path;
    BPath *bpath;
    int32 last_space = command.FindLast(" ");
    command.CopyInto(path,5,last_space - 5);

    path.CopyInto(dirpath,0,path.FindLast("/"));

    create_local_directory(&dirpath);
    //TODO fix watching new dirs
    bpath = new BPath(db_to_local_filepath(path.String()).String());
    BEntry new_file = BEntry(bpath->Path());
    if(new_file.InitCheck() && new_file.Exists()) {
      this->new_paths.AddItem((void*)bpath);
    } else {
      this->edited_paths.AddItem((void*)bpath);
    }

    printf("create a file at |%s|\n",path.String());
    char *argv[3];
    argv[0] = "db_get.py";
    char not_const1[path.CountChars() + 1];
    strcpy(not_const1,path.String());
    argv[1] = not_const1;
    BString tmp = db_to_local_filepath(path.String());
    char not_const2[tmp.CountChars() + 1]; //plus one for null
    strcpy(not_const2,tmp.String());
    argv[2] = not_const2;

    //create/update file
    //potential problem: takes awhile to do this step
    // having watching for dir turned off is risky.    
    BString * b = run_python_script(argv,3);
    delete b;

    //start watching the new/updated file
    node_ref nref;
    new_file = BEntry(db_to_local_filepath(path.String()).String());
    new_file.GetNodeRef(&nref);
    status_t err = watch_node(&nref,B_WATCH_STAT,be_app_messenger);

    BString parent_rev;
    command.CopyInto(parent_rev,last_space + 1, command.CountChars() - (last_space+1));
    BNode node = BNode(db_to_local_filepath(path.String()).String());
    set_parent_rev(&node,&parent_rev);
  }
  else if(command.Compare("FOLDER ",7) == 0)
  {
    BString path;
    command.CopyInto(path,7,command.FindLast(" ") - 7);

    //ignore the creation message
    BPath bpath = BPath(db_to_local_filepath(path.String()).String());
    BPath *actually_exists = find_existing_subpath(&bpath);
    this->new_paths.AddItem((void*)actually_exists);

    //create all nescessary dirs in path
    printf("create a folder at |%s|\n", path.String());
    create_local_directory(&path);

    //start watching the new dir
    BDirectory existing_dir = BDirectory(actually_exists->Path());
    recursive_watch(&existing_dir);
  }
  else if(command.Compare("REMOVE ",7) == 0)
  {
    //TODO: deal with Dropbox file paths being case-insensitive
    //which here means all lower case
    BString path;
    command.CopyInto(path,7,command.Length() - 7);

    const char * pathstr = db_to_local_filepath(path.String()).String();
    BPath *bpath = new BPath(pathstr);
    //TODO: check if it exists...
    this->removed_paths.AddItem((void*)bpath);

    printf("Remove whatever is at |%s|\n", pathstr);

    BEntry entry = BEntry(pathstr);
    status_t err = entry.Remove();
    if(err != B_OK)
      printf("Removal error: %s\n", strerror(err));
  }
  else
  {
    printf("Did not recognize command.\n");
    return B_ERROR;
  }
  return B_OK;
}
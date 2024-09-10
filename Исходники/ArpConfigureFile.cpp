status_t ArpConfigureFile::SetFile(const char* name)
{
    ArpD(cdb << ADH << "ArpConfigureFile: setting file from path = "
         << name << endl);

    BEntry entry(&mFile);
    if( entry.InitCheck() != B_OK ) return entry.InitCheck();

    BPath path;
    status_t err = entry.GetPath(&path);
    if( err != B_OK ) return err;

    ArpD(cdb << ADH << "ArpConfigureFile: orig path = "
         << path << endl);

    err = path.InitCheck();
    if( err == B_OK ) err = path.GetParent(&path);
    if( err == B_OK ) err = path.Append(name);
    ArpD(cdb << ADH << "ArpConfigureFile: renamed path = "
         << path.Path() << endl);

    if( err != B_OK ) return err;

    entry.SetTo(path.Path());
    err = entry.InitCheck();
    if( err != B_OK ) return err;

    entry_ref ref;
    err = entry.GetRef(&ref);
    if( err != B_OK ) return err;

    return SetFile(ref);
}
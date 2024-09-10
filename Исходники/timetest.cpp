void RunList (char *filename)
{
    List<int> list;
    ListItr<int> listItr = list.zeroth();
    ifstream inf(filename);
    char comm, s[512];
    int value;
    inf.getline(s, 512);
    while (inf >> comm >> value) //While values are being read in.
    {
        if (comm == 'i') //if the file says to insert.
            list.insert(value, listItr);
        else //othwerise.
            list.remove(value);
    }//end while
}//RunList
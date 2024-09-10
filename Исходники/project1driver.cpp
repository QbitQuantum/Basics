void executeCmd(char command, list & aList)
{
    winery aWinery;
    char key[MAX_LEN];
    
    switch(command)
    {
        case 'a': getWinery(aWinery);
            aList.insert (aWinery);
            cout << endl << "the winery has been saved in the database. " << endl;
            break;
        case 'r': getString("\nPlease enter the name of the winery you want to remove: ", key);
            aList.remove(key);
            cout << endl << key << " has been removed from the database. " << endl;
            break;
        case 's': getString("\nPlease enter the name of the winery you want to search: ", key);
            aList.retrieve (key, aWinery);
            cout << endl << "Information about " << key << ": " << endl << '\t' << aWinery << endl;
            break;
        case 'l': display(aList);
            break;
        default: cout << "illegal command!" << endl;
            break;
    }
}
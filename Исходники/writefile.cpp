/**
 * @brief createTable creates the database and metadata.
 * @param registerSize is the size for each registry.
 * @param columnSizes is the sizes for each column.
 */
bool writefile::createTable(int* registerSize, array<int>* columnSizes ,
                            array<char*>* columnNames , string* pFile){

    int offset = 0;
    string add;

    string theFileName = createNewFile(*pFile);
    writefile::writeColumnNames(&theFileName, columnNames);
    ofstream database (theFileName.c_str() , ios::trunc);

    //check if buffer = true
    if(database.is_open()){
        //cout << "****Database succesfully created***" << endl;
    }else{
        //cout << "****Database could not be created***" << endl;
        return false;
    }

    //Register size valideichion.
    if(*registerSize >= K->MAX_REGISTER_SIZE){
        cout << "Error: Register size beyond max size" << endl;
        return false;
    }else{
        database << K->TRIPLE_NULL;
        add = toChar(*registerSize);
        checkSize(&add, K->DEFAULT_REGISTER_SIZE);
        database.write(add.c_str() , K->DEFAULT_REGISTER_SIZE);
    }

    //set column sizes on file
    array<int> tempArr = *columnSizes;
    for (int i = 0 ; i < tempArr.getLenght() ; i++)
    {
        int integerElem = tempArr[i];
        add = toChar(integerElem);
        checkSize(&add,K->DEFAULT_COLUMN_SIZE);
        database.write(add.c_str() , K->DEFAULT_COLUMN_SIZE);
    }

    //sets seek on the end, gets the address then turns it to char
    //to insert on the beginning.
    database.seekp(offset, ios::end);
    int meta = database.tellp();
    string metadata = intToChar(meta);
    checkSize(&metadata, K->METADATA_SIZE);
    database.seekp(K->ZE_ROW);
    if (metadata.length() <= 3){
        const char *p = metadata.c_str();
        while (*p != '\0')
            database.put( *(p++) );
    }else{
        //cout << "Invalid metadata size. Yoh ! Pls kontact ur admin...\n";
        return false;
    }
    database.seekp(K->ZE_ROW , ios::end);
    database.close();
    return true;
}
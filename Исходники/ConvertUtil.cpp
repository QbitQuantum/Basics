void ConvertUtil::CreateSQLiteFile(FdoIConnection *connection, FdoString *file)
{
    _wunlink(file);

    int    count = 0;
    wchar_t buffer[512];
    FdoString **names = NULL;
    
    swprintf(buffer, 512, L"File=%ls;UseFdoMetadata=TRUE", file);
    connection->SetConnectionString(buffer);

    FdoPtr<FdoICreateDataStore>    dataStore = static_cast<FdoICreateDataStore*>(connection->CreateCommand(FdoCommandType_CreateDataStore));
    FdoPtr<FdoIDataStorePropertyDictionary> dictionary = dataStore->GetDataStoreProperties();

    names = dictionary->GetPropertyNames(count);
    dictionary->SetProperty(names[0], file);

    dataStore->Execute();
}
//---------------------------------------------------------------------------
void TfrmMainFormServer::AddANewModule(){
    AnsiString name = InputBox("New Virtual Directory",
        "Enter an alias WITHOUT spaces",
        "ANewName");

    if(name.Length() > 0){
        adapter.AddANewModule(name);
        LoadModuleNames();
    }


}
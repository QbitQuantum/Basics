wxFileName CompilationDatabase::ConvertCodeLiteCompilationDatabaseToCMake(const wxFileName& compile_file)
{
    wxFFile fp(compile_file.GetFullPath(), wxT("rb"));
    if( fp.IsOpened() ) {
        wxString content;
        fp.ReadAll(&content, wxConvUTF8);

        if( content.IsEmpty() )
            return wxFileName();
        
        JSONRoot root(cJSON_Array);
        JSONElement arr = root.toElement();
        wxArrayString lines = ::wxStringTokenize(content, "\n\r", wxTOKEN_STRTOK);
        for(size_t i=0; i<lines.GetCount(); ++i) {
            wxArrayString parts = ::wxStringTokenize(lines.Item(i), wxT("|"), wxTOKEN_STRTOK);
            if( parts.GetCount() != 3 )
                continue;

            wxString file_name = wxFileName(parts.Item(0).Trim().Trim(false)).GetFullPath();
            wxString cwd       = parts.Item(1).Trim().Trim(false);
            wxString cmp_flags = parts.Item(2).Trim().Trim(false);

            JSONElement element = JSONElement::createObject();
            element.addProperty("directory", cwd);
            element.addProperty("command",   cmp_flags);
            element.addProperty("file",      file_name);
            arr.arrayAppend( element );
        }
        
        wxFileName fn(compile_file.GetPath(), "compile_commands.json");
        root.save( fn );
        // Delete the old file
        {
            wxLogNull nl;
            fp.Close();
            if ( compile_file.Exists() ) {
                ::wxRemoveFile( compile_file.GetFullPath() );
            }
        }
        return fn;
    }
    return wxFileName();
}
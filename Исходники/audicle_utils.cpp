fileData* 
winDirScanner::openFileDialog() { 

    char newname[512];
    newname[0] = '\0';
    
    if ( openfD ) { 
        delete openfD;
        openfD = NULL;
    }
    //XXX make this non-modal 
    //fprintf(stderr, "fetching WIN32 file dialog\n");
    BB_log( BB_LOG_INFO, "opening win32 open file dialog..." );
    BB_pushlog();
    
    ShowCursor(true);
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lpstrFile = newname;
    ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = m_types ? m_types : "All Files (*.*)\0*.*\0";
    ofn.lpstrFile = newname;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "txt";
    
    if( GetOpenFileName( &ofn ) && ofn.lpstrFile )
    {
        // fprintf(stderr, "file - %s %s\n", ofn.lpstrFile, ofn.lpstrFileTitle );
        // BB_log( BB_LOG_INFO, "file: %s %s", ofn.lpstrFile, ofn.lpstrFileTitle );
        openfD = new fileData();
        fileData * newFile = openfD;
        char * next = newname; 
        next += strlen(next) + 1;
        if( *next )
        { 
            char basepath[512];
            char fullpath[512];
            strncpy( basepath, newname, 512 );
            strcat( basepath, "\\" );
            do
            { 
                strcpy( fullpath, basepath );
                strcat( fullpath, next );
                fprintf( stderr, "returned multi file %s\n", fullpath );
                newFile->fileName = fullpath;
                next += strlen(next) + 1;
                if( *next )
                { 
                    newFile->next = new fileData();
                    newFile = newFile->next;
                }
            }while ( *next ) ;
        } 
        else
        {   //no extra files, we copied the full path in already
            // fprintf ( stderr, "returned single file %s\n", newname );
            // BB_log( BB_LOG_INFO, "got single file: %s", newname );
            openfD->fileName = newname;
        }
    }
    else
    {
        if( CommDlgExtendedError() == 0 )
        {
            BB_log( BB_LOG_INFO, "no file selected..." );
        }
        else
        {
            BB_log( BB_LOG_INFO, "openfile error: %d", CommDlgExtendedError() );
        }

        BB_poplog();

        return NULL;
    }

    ShowCursor(false);

    BB_poplog();
    
    return openfD;
}
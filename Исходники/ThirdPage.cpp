OSStatus
CThirdPage::LoadPrintDriverDefsFromFile(Manufacturers & manufacturers, const CString & filename, bool checkForDuplicateModels )
{
    HINF			handle	= INVALID_HANDLE_VALUE;
    const TCHAR *	section = TEXT( "Manufacturer" );
    LONG			sectionCount;
    TCHAR			line[ 1000 ];
    CString			klass;
    INFCONTEXT		manufacturerContext;
    BOOL			ok;
    OSStatus		err		= 0;

    // Make sure we can open the file
    handle = SetupOpenInfFile( filename, NULL, INF_STYLE_WIN4, NULL );
    translate_errno( handle != INVALID_HANDLE_VALUE, GetLastError(), kUnknownErr );
    require_noerr( err, exit );

    // Make sure it's a printer file
    ok = SetupGetLineText( NULL, handle, TEXT( "Version" ), TEXT( "Class" ), line, sizeof( line ), NULL );
    translate_errno( ok, GetLastError(), kUnknownErr );
    require_noerr( err, exit );
    klass = line;
    require_action( klass == TEXT( "Printer" ), exit, err = kUnknownErr );

    sectionCount = SetupGetLineCount( handle, section );
    translate_errno( sectionCount != -1, GetLastError(), kUnknownErr );
    require_noerr( err, exit );

    memset( &manufacturerContext, 0, sizeof( manufacturerContext ) );

    for ( LONG i = 0; i < sectionCount; i++ )
    {
        Manufacturers::iterator	iter;
        Manufacturer	*	manufacturer;
        CString				manufacturerName;
        CString				temp;
        CStringList			modelSectionNameDecl;
        CString				modelSectionName;
        CString				baseModelName;
        CString				model;
        INFCONTEXT			modelContext;
        LONG				modelCount;
        POSITION			p;

        if ( i == 0 )
        {
            ok = SetupFindFirstLine( handle, section, NULL, &manufacturerContext );
            err = translate_errno( ok, GetLastError(), kUnknownErr );
            require_noerr( err, exit );
        }
        else
        {
            ok = SetupFindNextLine( &manufacturerContext, &manufacturerContext );
            err = translate_errno( ok, GetLastError(), kUnknownErr );
            require_noerr( err, exit );
        }

        ok = SetupGetStringField( &manufacturerContext, 0, line, sizeof( line ), NULL );
        err = translate_errno( ok, GetLastError(), kUnknownErr );
        require_noerr( err, exit );
        manufacturerName = line;

        ok = SetupGetLineText( &manufacturerContext, handle, NULL, NULL, line, sizeof( line ), NULL );
        err = translate_errno( ok, GetLastError(), kUnknownErr );
        require_noerr( err, exit );

        // Try to find some model section name that has entries. Explanation of int file structure
        // can be found at:
        //
        // <http://msdn.microsoft.com/en-us/library/ms794359.aspx>
        Split( line, ',', modelSectionNameDecl );

        p					= modelSectionNameDecl.GetHeadPosition();
        modelSectionName	= modelSectionNameDecl.GetNext( p );
        modelCount			= SetupGetLineCount( handle, modelSectionName );
        baseModelName		= modelSectionName;

        while ( modelCount <= 0 && p )
        {
            CString targetOSVersion;

            targetOSVersion		= modelSectionNameDecl.GetNext( p );
            modelSectionName	= baseModelName + TEXT( "." ) + targetOSVersion;
            modelCount			= SetupGetLineCount( handle, modelSectionName );
        }

        if ( modelCount > 0 )
        {
            manufacturerName = NormalizeManufacturerName( manufacturerName );

            iter = manufacturers.find( manufacturerName );

            if ( iter != manufacturers.end() )
            {
                manufacturer = iter->second;
                require_action( manufacturer, exit, err = kUnknownErr );
            }
            else
            {
                try
                {
                    manufacturer = new Manufacturer;
                }
                catch (...)
                {
                    manufacturer = NULL;
                }

                require_action( manufacturer, exit, err = kNoMemoryErr );

                manufacturer->name					= manufacturerName;
                manufacturers[ manufacturerName ]	= manufacturer;
            }

            memset( &modelContext, 0, sizeof( modelContext ) );

            for ( LONG j = 0; j < modelCount; j++ )
            {
                CString modelName;
                Model * model;

                if ( j == 0 )
                {
                    ok = SetupFindFirstLine( handle, modelSectionName, NULL, &modelContext );
                    err = translate_errno( ok, GetLastError(), kUnknownErr );
                    require_noerr( err, exit );
                }
                else
                {
                    SetupFindNextLine( &modelContext, &modelContext );
                    err = translate_errno( ok, GetLastError(), kUnknownErr );
                    require_noerr( err, exit );
                }

                ok = SetupGetStringField( &modelContext, 0, line, sizeof( line ), NULL );
                err = translate_errno( ok, GetLastError(), kUnknownErr );
                require_noerr( err, exit );

                modelName = line;

                if (checkForDuplicateModels == true)
                {
                    if ( MatchModel( manufacturer, ConvertToModelName( modelName ) ) != NULL )
                    {
                        continue;
                    }
                }

                //
                // Stock Vista printer inf files embed guids in the model
                // declarations for Epson printers. Let's ignore those.
                //
                if ( modelName.Find( TEXT( "{" ), 0 ) != -1 )
                {
                    continue;
                }

                try
                {
                    model = new Model;
                }
                catch (...)
                {
                    model = NULL;
                }

                require_action( model, exit, err = kNoMemoryErr );

                model->infFileName		=	filename;
                model->displayName		=	modelName;
                model->name				=	modelName;
                model->driverInstalled	=	false;

                manufacturer->models.push_back(model);
            }
        }
    }

exit:

    if ( handle != INVALID_HANDLE_VALUE )
    {
        SetupCloseInfFile( handle );
        handle = NULL;
    }

    return err;
}
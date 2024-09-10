// *****************************************************************************
MStatus GtoIO::writer( const MFileObject &file, 
                       const MString &optionsString,
                       MPxFileTranslator::FileAccessMode mode )
{
    MTime fs = MAnimControl::currentTime(); 
    MTime fe = fs;
    double shutter = 0.0;
    MString filename = file.fullName();
    bool subd = false;
    bool normals = false;
    bool exportST = false;
    int maxRecurse = 1;
    bool normalize = false;
    bool hidden = true;
    bool verify = true;
    bool doAnim = false;
    bool diffPoints = false;
    bool diffMatrix = false;
    bool diffNormals = false;
    bool isDifferenceFile = false;
    bool quiet = false;
    bool allUserAttributes = false;
    bool allMayaAttributes = false;
    bool allXformAttributes = false;
    bool faceMaterials = false;
    bool ascii = false;

    if( ( mode == MPxFileTranslator::kExportAccessMode ) ||
        ( mode == MPxFileTranslator::kSaveAccessMode ) )
    {
        MGlobal::displayError( "The GTO plugin can only be used for Export "
                               "Selection...");
        return MS::kFailure;
    }

    MStringArray args;
    optionsString.split( ';', args );
    for( size_t i = 0; i < args.length(); ++i )
    {
        MStringArray thisArg;
        args[i].split( '=', thisArg );
        MString argName( thisArg[0] );
        MString argValue( thisArg[1] );

        if( argName == "recurse" && argValue == "1" )
        {
            maxRecurse = 100000;
        }
        else if( argName == "quiet" && argValue == "1" )
        {
            quiet = true;
        }
        else if( argName == "ascii" && argValue == "1" )
        {
            ascii = true;
        }
        else if( argName == "subd" && argValue == "1" )
        {
            subd = true;
        }
        else if( argName == "normals" && argValue == "1" )
        {
            normals = true;
        }
        else if( argName == "st" && argValue == "1" )
        {
            exportST = true;
        }
        else if( argName == "faceMat" && argValue == "1" )
        {
            faceMaterials = true;
        }
        else if( argName == "diffpositions" && argValue == "1" )
        {
            diffPoints = true;
        }
        else if( argName == "diffmatrices" && argValue == "1" )
        {
            diffMatrix = true;
        }
        else if( argName == "diffnormals" && argValue == "1" )
        {
            diffNormals = true;
        }
        else if( argName == "isdifference" && argValue == "1" )
        {
            isDifferenceFile = true;
        }
        else if( argName == "normalize" && argValue == "1" )
        {
            normalize = true;
        }
        else if( argName == "hidden" && argValue == "0" )
        {
            hidden = false;
        }
        else if( argName == "verify" && argValue == "0" )
        {
            verify = false;
        }
        else if( argName == "userAttr" && argValue == "1" )
        {
            allUserAttributes = true;
        }
        else if( argName == "mayaAttr" && argValue == "1" )
        {
            allMayaAttributes = true;
        }
        else if( argName == "xformAttr" && argValue == "1" )
        {
            allXformAttributes = true;
        }
        else if( argName == "anim" && argValue == "1" )
        {
            doAnim = true;
            // If user didn't include a # in the filename, but
            // is exporting multiple frames, do it automatically
            if( filename.index( '#' ) < 0 )
            {
                // By this point, Maya will have already appended a 
                // ".gto" to the filename if the user didn't include it,
                // so we're guaranteed to find a '.' in the filename
                filename = filename.substring( 0, filename.rindex( '.' ) )
                           + "#.gto";
            }
        }
        else if( argName == "fs" && doAnim )
        {
            fs = MTime( argValue.asDouble(), MTime::uiUnit() );
        }
        else if( argName == "fe" && doAnim  )
        {
            fe = MTime( argValue.asDouble(), MTime::uiUnit() );
        }
        else if( argName == "shutter" && doAnim )
        {
            shutter = argValue.asDouble() / 360.0;
        }
        else if( argName == "recurseLimit" )
        {
            if( argValue.asInt() > 0 )
            {
                maxRecurse = argValue.asInt();
            }
        }
    }
    
    if( ! isDifferenceFile )
    {
        diffPoints = false;
        diffMatrix = false;
        diffNormals = false;
    }
    
    // TODO: Find a more graceful way to get options to GtoExporter

    GtoExporter exporter( fs, fe, quiet, shutter, subd, normals, exportST, filename, 
                          maxRecurse, normalize, hidden, verify, 
                          isDifferenceFile, diffPoints, diffMatrix, 
                          diffNormals, allUserAttributes, allMayaAttributes, 
                          faceMaterials, ascii, allXformAttributes );

    MStatus result = exporter.doIt();
    return result;
}
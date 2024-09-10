static void ExportImagesFromDictionary(
    rw::TexDictionary *texDict, CFileTranslator *outputRoot,
    const filePath& txdFileName, const filePath& relPathFromRoot,
    MassExportModule::eOutputType outputType,
    const std::string& imgFormat
)
{
    rw::Interface *rwEngine = texDict->GetEngine();

    for ( rw::TexDictionary::texIter_t iter( texDict->GetTextureIterator() ); !iter.IsEnd(); iter.Increment() )
    {
        rw::TextureBase *texHandle = iter.Resolve();

        if ( rw::Raster *texRaster = texHandle->GetRaster() )
        {
            // Construct the target filename.
            filePath targetFileName = relPathFromRoot;

            if ( outputType == MassExportModule::OUTPUT_PLAIN )
            {
                // We are a plain path, which is just the texture name appended.
            }
            else if ( outputType == MassExportModule::OUTPUT_TXDNAME )
            {
                // Also put the TexDictionary name before it.
                targetFileName += txdFileName;
                targetFileName += "_";
            }
            else if ( outputType == MassExportModule::OUTPUT_FOLDERS )
            {
                // Instead put it inside folders.
                targetFileName += txdFileName;
                targetFileName += "/";
            }
        
            targetFileName += texHandle->GetName();
            targetFileName += ".";
            
            std::string lower_ext = imgFormat;
            std::transform( lower_ext.begin(), lower_ext.end(), lower_ext.begin(), ::tolower );

            targetFileName += lower_ext;

            // Create the target stream.
            CFile *targetStream = outputRoot->Open( targetFileName, "wb" );

            if ( targetStream )
            {
                try
                {
                    rw::Stream *rwStream = RwStreamCreateTranslated( rwEngine, targetStream );

                    if ( rwStream )
                    {
                        try
                        {
                            // Write it!
                            try
                            {
                                if ( stricmp( imgFormat.c_str(), "RWTEX" ) == 0 )
                                {
                                    rwEngine->Serialize( texHandle, rwStream );
                                }
                                else
                                {
                                    texRaster->writeImage( rwStream, imgFormat.c_str() );
                                }
                            }
                            catch( rw::RwException& )
                            {
                                // If we failed to write it, just live with it.
                            }
                        }
                        catch( ... )
                        {
                            rwEngine->DeleteStream( rwStream );

                            throw;
                        }

                        rwEngine->DeleteStream( rwStream );
                    }
                }
                catch( ... )
                {
                    delete targetStream;

                    throw;
                }

                delete targetStream;
            }
        }
    }
}
void GPCB_FPL_CACHE::Remove( const wxString& aFootprintName )
{
    std::string footprintName = TO_UTF8( aFootprintName );

    MODULE_CITER it = m_modules.find( footprintName );

    if( it == m_modules.end() )
    {
        THROW_IO_ERROR( wxString::Format( _( "library <%s> has no footprint '%s' to delete" ),
                                          m_lib_path.GetPath().GetData(),
                                          aFootprintName.GetData() ) );
    }

    // Remove the module from the cache and delete the module file from the library.
    wxString fullPath = it->second->GetFileName().GetFullPath();
    m_modules.erase( footprintName );
    wxRemoveFile( fullPath );
}
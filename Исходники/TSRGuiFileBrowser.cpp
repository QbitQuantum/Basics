// the initialization method
void TSRGuiFileBrowser::Initialize()
{
    m_Maxcharacters = 10;
    m_eType = TWISTER_GUI_COMPONENT_FILEBROWSER;
    m_bClickable    = true;
    SetTextAlign( GUI_ALIGN_TOPLEFT );
    SetFilter( "*.*" );
    m_FolderColor.Assign( 1.0f, 0.0f, 0.0f );
    m_FileColor.Assign( 0.0f, 0.0f, 1.0f );
    m_HotColor.Assign( 0.5f, 0.5f, 0.5f );
}
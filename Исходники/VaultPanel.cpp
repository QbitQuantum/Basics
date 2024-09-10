void VaultPanel::OnOptionsMenuOpen( wxMenuEvent& event )
{
    event.Skip();
    if ( event.GetMenu() == m_OptionsMenu )
    {
        for ( wxMenuItemList::iterator itr = event.GetMenu()->GetMenuItems().begin(), end = event.GetMenu()->GetMenuItems().end(); itr != end; ++itr )
        {
            (*itr)->Check( false );
        }

        HELIUM_ASSERT( m_CurrentViewMode != VaultViewMode::None );

        int id = -1;
        switch ( m_CurrentViewMode )
        {
        default:
        case VaultViewMode::List:
            id = VaultMenu::ViewResultList;
            break;
        case VaultViewMode::Details:
            id = VaultMenu::ViewResultDetails;
            break;
        case VaultViewMode::ThumbnailsSmall:
            id = VaultMenu::ViewThumbnailsSmall;
            break;
        case VaultViewMode::ThumbnailsMedium:
            id = VaultMenu::ViewThumbnailsMedium;
            break;
        case VaultViewMode::ThumbnailsLarge:
            id = VaultMenu::ViewThumbnailsLarge;
            break;
        }

        event.GetMenu()->Check( id, true );
    }
}
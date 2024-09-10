BEGIN_GUI_NAMESPACE

Menu::Menu( const std::string& root, HWND hwnd /*= NULL*/ )
    : Subscriber( root ), hwnd_( hwnd )
{
    if( hwnd_ )
    {
        hmenu_ = GetMenu( hwnd_ );
        if( hmenu_ )
        {
            while( GetMenuItemCount( hmenu_ ) != 0 )
                DeleteMenu( hmenu_, 0, MF_BYPOSITION );
        }
    }
    else
        hmenu_ = CreatePopupMenu();
    MENUINFO info = { sizeof( info ), MIM_BACKGROUND };
    info.hbrBack = GetSysColorBrush( COLOR_MENUBAR );
    SetMenuInfo( hmenu_, &info );
}
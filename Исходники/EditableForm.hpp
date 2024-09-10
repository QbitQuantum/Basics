    void ReCollocate( std::string  Layout)
    {
        _myLayout.swap(Layout);
        try 
        {
            ReCollocate( );
        }
        catch(std::exception& e)
        {
             (nana::msgbox(*_EdWd_owner, STR("std::exception during EditableWidget ReCollocation: "))
                    .icon(nana::msgbox::icon_error)
                                 <<STR("\n   in widget: ")  << nana::API::window_caption( _thisEdWd)
                                 <<STR("\n   Title: "    )  << _Titel
                                 <<STR("\n   owned by: "  ) << nana::API::window_caption(*_EdWd_owner)
                                 <<STR("\n   trying to layout: \n "  ) << _myLayout
                                 <<STR("\n   ocurred exception: ") << e.what() 
             ).show();
        }
		catch(...)
		{
             (nana::msgbox(*_EdWd_owner, STR("An uncaptured exception during EditableWidget ReCollocation: "))
                    .icon(nana::msgbox::icon_error)
                                 <<STR("\n   in widget: ")  << nana::API::window_caption( _thisEdWd)
                                 <<STR("\n   Title: "    )  << _Titel
                                 <<STR("\n   owned by: "  ) << nana::API::window_caption(*_EdWd_owner)
                                 <<STR("\n   trying to layout: \n "  ) << _myLayout
             ).show();
	    }
        _myLayout.swap(Layout); /// call ReCollocate again???
	}
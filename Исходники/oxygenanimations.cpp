    //____________________________________________________________________________________________
    bool Animations::registerWidget( GtkWidget* widget )
    {

        if( _allWidgets.find( widget ) != _allWidgets.end() ) return false;

        #if OXYGEN_DEBUG
        std::cerr << "Oxygen::Animations::registerWidget - " << widget << " (" << (widget ? G_OBJECT_TYPE_NAME( widget ):"0x0") << ")" << std::endl;
        #endif

        Signal destroyId;
        destroyId.connect( G_OBJECT( widget ), "destroy", G_CALLBACK( destroyNotifyEvent ), this );
        _allWidgets.insert( std::make_pair( widget, destroyId ) );
        return true;

    }
    //________________________________________________________
    void SignalHandler::connect( GObject* object, const std::string& signal, GCallback callback, gpointer data )
    {
        // check if object is already connected
        if( _objects.find( object ) == _objects.end() )
        {

            // insert object
            _objects.insert( object );

            // insert destroy signal
            Signal destroyId;
            destroyId.connect( object, "destroy", (GCallback) destroyNotifyEvent, this );
            _signals.push_back( destroyId );

        }

        // insert signal
        Signal signalId;
        signalId.connect( object, signal, callback, data );
        _signals.push_back( signalId );

    }
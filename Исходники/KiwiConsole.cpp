    void Console::post(scObject object, string const& message) noexcept
    {
#if defined(DEBUG) || defined(NO_GUI)
        cerr << object->getText() << " : " << message << endl;
#endif
        scInstance instance = nullptr;
        scPatcher  patcher  = nullptr;
        if(object)
        {
            instance= object->getInstance();
            patcher = object->getPatcher();
        }
        shared_ptr<const Message> mess = make_shared<Message>(instance, patcher, object, Message::Post, message);
        
        ListenerSet<Listener>& listeners(getListeners());
        listeners.call(&Listener::receive, mess);
    }
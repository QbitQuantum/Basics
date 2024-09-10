bool ClientApp::OnProcessMessageReceived(
        CefRefPtr<CefBrowser> browser,
        CefProcessId source_process,
        CefRefPtr<CefProcessMessage> message) {
    ASSERT(source_process == PID_BROWSER);

    bool handled = false;

    // Execute delegate callbacks.
    RenderDelegateSet::iterator it = render_delegates_.begin();
    for (; it != render_delegates_.end() && !handled; ++it) {
        handled = (*it)->OnProcessMessageReceived(this, browser, source_process, message);
    }

    if (!handled) {
        if (message->GetName() == "invokeCallback") {
            // This is called by the appshell extension handler to invoke the asynchronous 
            // callback function
            
            CefRefPtr<CefListValue> messageArgs = message->GetArgumentList();
            int32 callbackId = messageArgs->GetInt(0);
                    
            CefRefPtr<CefV8Context> context = callback_map_[callbackId].first;
            CefRefPtr<CefV8Value> callbackFunction = callback_map_[callbackId].second;
            CefV8ValueList arguments;
            context->Enter();
            
            // Sanity check to make sure the context is still attched to a browser.
            // Async callbacks could be initiated after a browser instance has been deleted,
            // which can lead to bad things. If the browser instance has been deleted, don't
            // invoke this callback. 
            if (context->GetBrowser()) {
                for (size_t i = 1; i < messageArgs->GetSize(); i++) {
                    arguments.push_back(ListValueToV8Value(messageArgs, i));
                }
                
                callbackFunction->ExecuteFunction(NULL, arguments);
            }
            
            context->Exit();
            
            callback_map_.erase(callbackId);
        } else if (message->GetName() == "executeCommand") {
            // This is called by the browser process to execute a command via JavaScript
            // 
            // The first argument is the command name. This is required.
            // The second argument is a message id. This is optional. If set, a response
            // message will be sent back to the browser process.
            
            CefRefPtr<CefListValue> messageArgs = message->GetArgumentList();
            CefString commandName = messageArgs->GetString(0);
            int messageId = messageArgs->GetSize() > 1 ? messageArgs->GetInt(1) : -1;
            bool handled = false;
            
            StContextScope ctx(browser->GetMainFrame()->GetV8Context());
            
            CefRefPtr<CefV8Value> global = ctx.GetContext()->GetGlobal();
            
            if (global->HasValue("brackets")) { 
                
                CefRefPtr<CefV8Value> brackets = global->GetValue("brackets");
                
                if (brackets->HasValue("shellAPI")) {
                    
                    CefRefPtr<CefV8Value> shellAPI = brackets->GetValue("shellAPI");
                    
                    if (shellAPI->HasValue("executeCommand")) {
                        
                        CefRefPtr<CefV8Value> executeCommand = shellAPI->GetValue("executeCommand");
                        
                        if (executeCommand->IsFunction()) {
                            
                            CefRefPtr<CefV8Value> retval;
                            CefV8ValueList args;
                            args.push_back(CefV8Value::CreateString(commandName));
                            
                            retval = executeCommand->ExecuteFunction(global, args);
                            
                            if (retval) {
                                handled = retval->GetBoolValue();
                            }
                        }
                    }
                }
            }
            
            // Return a message saying whether or not the command was handled
            if (messageId != -1) {
                CefRefPtr<CefProcessMessage> result = CefProcessMessage::Create("executeCommandCallback");
                result->GetArgumentList()->SetInt(0, messageId);
                result->GetArgumentList()->SetBool(1, handled);
                
                browser->SendProcessMessage(PID_BROWSER, result);
            }
        }
    }
    
    return handled;
}
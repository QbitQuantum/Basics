ECode CAccessibilityServiceClientWrapper::ExecuteMessage(
    /* [in] */ IMessage* message)
{
    Int32 what, arg1;
    message->GetWhat(&what);
    message->GetArg1(&arg1);

    switch (what) {
        case DO_ON_ACCESSIBILITY_EVENT : {
            AutoPtr<IInterface> obj;
            message->GetObj((IInterface**)&obj);
            IAccessibilityEvent* event = IAccessibilityEvent::Probe(obj);
            if (event != NULL) {
                AutoPtr<IAccessibilityInteractionClientHelper> helper;
                CAccessibilityInteractionClientHelper::AcquireSingleton((IAccessibilityInteractionClientHelper**)&helper);
                AutoPtr<IAccessibilityInteractionClient> client;
                helper->GetInstance((IAccessibilityInteractionClient**)&client);

                client->OnAccessibilityEvent(event);
                mCallback->OnAccessibilityEvent(event);
                event->Recycle();
            }
            return NOERROR;
        }

        case DO_ON_INTERRUPT :
            mCallback->OnInterrupt();
            return NOERROR;

        case DO_SET_SET_CONNECTION : {
            AutoPtr<IAccessibilityInteractionClientHelper> helper;
            CAccessibilityInteractionClientHelper::AcquireSingleton((IAccessibilityInteractionClientHelper**)&helper);
            AutoPtr<IAccessibilityInteractionClient> client;
            helper->GetInstance((IAccessibilityInteractionClient**)&client);

            const Int32 connectionId = arg1;
            AutoPtr<IInterface> obj;
            message->GetObj((IInterface**)&obj);
            IIAccessibilityServiceConnection* connection = IIAccessibilityServiceConnection::Probe(obj);

            if (connection != NULL) {
                client->AddConnection(connectionId, connection);
                mCallback->OnSetConnectionId(connectionId);
                mCallback->OnServiceConnected();
            }
            else {
                client->RemoveConnection(connectionId);
                mCallback->OnSetConnectionId(IAccessibilityInteractionClient::NO_ID);
            }
            return NOERROR;
        }

        case DO_ON_GESTURE : {
            Boolean result;
            mCallback->OnGesture(arg1, &result);
            return NOERROR;
        }

        default :
            // Logger::W(LOG_TAG, "Unknown message type %d", what);
            break;
    }
    return NOERROR;
}
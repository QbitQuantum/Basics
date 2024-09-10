TInt COpenMAXALTestModule::al_SetDataLocator( CStifItemParser& aItem )
    {
    TInt status(KErrNone);
    TInt type;

    status = aItem.GetNextInt(type);

    switch(type)
        {
        case XA_DATALOCATOR_URI:
            {
            TPtrC uri;
            if(m_URIName)
                {
                delete m_URIName;
                m_URIName = NULL;
                }
            //status = aItem.SetParsingType(CStifItemParser::EQuoteStyleParsing);
            status = aItem.GetNextString(uri);
            if(!status)
                {
                m_URIName = HBufC8::NewL(uri.Length()+1);
                TPtr8 desc = m_URIName->Des();
                desc.Copy(uri);
                m_Uri.locatorType = XA_DATALOCATOR_URI;
                m_Uri.URI = (XAchar*) desc.PtrZ();
                }
            else
                {
                status = KErrGeneral;
                }
            }
            break;
        case XA_DATALOCATOR_IODEVICE:
            {
            TInt devicetype;
            TUint deviceId;

            status = aItem.GetNextInt(devicetype);
            if(!status)
                {
                status = aItem.GetNextInt(deviceId);
                if(!status)
                    {
                    TInt srcsinktype(0);
                    status = aItem.GetNextInt(srcsinktype);
                    if(!status)
                        {
                        if(srcsinktype == 1)
                            {
                            m_SrcIODevice.deviceID = deviceId;
                            m_SrcIODevice.deviceType = devicetype;
                            m_SrcIODevice.locatorType = XA_DATALOCATOR_IODEVICE;
                            }
                        else
                            {
                            m_SinkIODevice.deviceID = deviceId;
                            m_SinkIODevice.deviceType = devicetype;
                            m_SinkIODevice.locatorType = XA_DATALOCATOR_IODEVICE;
                            }
                        }
                    else
                        {
                        status = KErrGeneral;
                        }
                    }
                else
                    {
                    status = KErrGeneral;
                    }
                }
            else
                {
                status = KErrGeneral;
                }
            }
            break;
        case XA_DATALOCATOR_OUTPUTMIX:
        case XA_DATALOCATOR_NATIVEDISPLAY:
        case XA_DATALOCATOR_ADDRESS:
            break;
        default:
            status = KErrGeneral;
            break;
        }
    return status;
    }
NetworkAddress * NetworkAddress_New(const char * uri, int uriLength)
{
    NetworkAddress * result = NULL;
    if (uri && uriLength > 0)
    {
        if (!result)
        {
            bool secure = false;
            int index = 0;
            int startIndex = 0;
            int port = 5683;
            char hostname[MAX_URI_LENGTH];
            int hostnameLength = 0;
            UriParseState state = UriParseState_Scheme;
            while (index < uriLength)
            {
                if (state == UriParseState_Scheme)
                {
                    if ((uri[index] == ':') && ((index + 2) <  uriLength) && (uri[index+1] == '/') &&  (uri[index+2] == '/'))
                    {
                        int length = index - startIndex;
                        if ((length == 4) && (strncmp(&uri[startIndex],"coap", length) == 0))
                        {

                        }
                        else if ((length == 5) && (strncmp(&uri[startIndex],"coaps", length) == 0))
                        {
                            port = 5684;
                            secure = true;
                        }
                        else
                        {
                            break;
                        }
                        state = UriParseState_Hostname;
                        index += 2;
                        startIndex = index + 1;
                    }
                    index++;
                }
                else if (state == UriParseState_Hostname)
                {
                    if ((uri[index] == '[') )
                    {
                        index++;
                        startIndex = index;
                        while (index < uriLength)
                        {
                            if (uri[index] == ']')
                            {
                                break;
                            }
                            hostname[hostnameLength] = uri[index];
                            hostnameLength++;
                            index++;
                        }
                    }
                    else if ((uri[index] == ':') || (uri[index] == '/') )
                    {
                        hostname[hostnameLength] = 0;
                        if  (uri[index] == '/')
                            break;
                        state = UriParseState_Port;
                        port = 0;
                        startIndex = index + 1;
                    }
                    else
                    {
                        hostname[hostnameLength] = uri[index];
                        hostnameLength++;
                    }
                    index++;
                }
                else if (state == UriParseState_Port)
                {
                    if (uri[index] == '/')
                    {
                        break;
                    }
                    else if (isdigit(uri[index]))
                    {
                        port = (port * 10) + (uri[index] - '0');
                    }
                    index++;
                }
            }
            if (state == UriParseState_Hostname)
            {
                hostname[hostnameLength] = 0;
            }
            if (hostnameLength > 0 && port > 0)
            {
                uip_ipaddr_t * resolvedAddress = getHostByName(hostname);

                if (resolvedAddress)
                {
                    NetworkAddress * networkAddress = getCachedAddress(resolvedAddress, port);

                    if(!networkAddress)
                    {
                        networkAddress = addCachedAddress(resolvedAddress, port, secure);
                    }

                    if (networkAddress)
                    {
                        result = networkAddress;
                    }
                }
            }
        }
        if(result)
        {
            result->useCount++;
        }
    }
    return result;
}
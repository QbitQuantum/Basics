/****
 * DumpEventInfo
 *
 * DESC:
 *     This function has two purposes depending on the mode. It will
 *     either (1) Print the contents of an event (if normal mode) or
 *     (2) return the latest record ID (if "last record" mode)
 *
 * ARGS:
 *     hRemote - Remote session context
 *     hResults - An open set of results
 *     outputFormat - 0 for JSON, otherwise XML
 *     mode - last record vs print results
 *     debug - set to 0 (none) 1 (basic) or 2 (verbose)
 *
 * REMARKS:
 */
DWORD64 DumpEventInfo(EVT_HANDLE hRemote, EVT_HANDLE hEvent, INT outputFormat, INT mode, INT debug)
{
    DWORD64 dwError = ERROR_SUCCESS;
    DWORD dwBufferSize = 0;
    DWORD dwBufferUsed = 0;
    DWORD dwPropertyCount = 0;
    LPWSTR pwsBuffer = NULL;
	rapidxml::xml_document<WCHAR> doc;

	if( debug >= DEBUG_L2 ) {
		wprintf(L"[DumpEventInfo]: Attempting to read event XML with no buffer\n" );
	}

    // Attempt to read the event as an XML string
	//
	// Note: We are expecting this call to fail, as we have NOT provided a buffer. Therefore
	// the purpose of this call is to fail, and have dwBufferUsed updated with required space	
    if (!EvtRender(NULL, hEvent, EvtRenderEventXml, dwBufferSize, pwsBuffer, &dwBufferUsed, &dwPropertyCount)) 
	{
		// Reading was NOT successful, as expected
		if( debug >= DEBUG_L2 ) {
			wprintf(L"[DumpEventInfo]: Required buffer space: %lu\n", dwBufferUsed );
		}

		// Get the error code
		dwError = GetLastError();

		if( debug >= DEBUG_L2 ) {
			wprintf(L"[DumpEventInfo]: Raw error code is: %lu\n", dwError );
		}

		// If call failed due to insufficient buffer (as we should expect)
        if (dwError == ERROR_INSUFFICIENT_BUFFER)
        {
			if( debug >= DEBUG_L2 ) {
				wprintf(L"[DumpEventInfo]: Last error code is insufficient buffer (as expecteted)\n" );
			}

			// Adjust the buffer size to the required amount as indicated by dwBufferUsed		
            dwBufferSize = dwBufferUsed;

			if( debug >= DEBUG_L2 ) {
				wprintf(L"[DumpEventInfo]: Attempting to reallocate buffer size: %lu\n", dwBufferSize );
			}

			// Re-allocate our buffer with the required size
            pwsBuffer = (LPWSTR)malloc(dwBufferSize);

			// If allocaton was successful
            if (pwsBuffer)
            {
				if( debug >= DEBUG_L2 ) {
					wprintf(L"[DumpEventInfo]: Allocation successful. Re-attempting to read event data\n" );
				}

				// Re-attempt to read event (as XML) now that we have appropriate buffer size
                if( EvtRender(NULL, hEvent, EvtRenderEventXml, dwBufferSize, pwsBuffer, &dwBufferUsed, &dwPropertyCount) ) 
				{
					if( debug >= DEBUG_L2 ) {
						wprintf(L"[DumpEventInfo]: Read successful. Last error code is: %lu\n", dwError );
					}

					// Reading was successful
					dwError = GetLastError();

					if( debug >= DEBUG_L2 ) {
						wprintf( L"[DumpEventInfo]: Raw XML: %s\n", pwsBuffer );
					}

					// Parse the XML string into our XML reader
					doc.parse<0>( pwsBuffer );

					if( debug >= DEBUG_L2 ) {
						wprintf( L"[DumpEventInfo]: XML parsing successful\n" );
					}

					// Retrieve the <Event> node
					rapidxml::xml_node<WCHAR> *nodeEvent = doc.first_node(L"Event");

					// Retrieve the <System> node
					rapidxml::xml_node<WCHAR> *nodeSystem = nodeEvent->first_node(L"System");
					// Children of the <System> node
					// You will recongize these as elements when viewing the event log in your viewer
					rapidxml::xml_node<WCHAR> *nodeEventID = nodeSystem->first_node(L"EventID");
					rapidxml::xml_node<WCHAR> *nodeChannel = nodeSystem->first_node(L"Channel");
					rapidxml::xml_node<WCHAR> *nodeEventRecordID = nodeSystem->first_node(L"EventRecordID");
					rapidxml::xml_node<WCHAR> *nodeProvider = nodeSystem->first_node(L"Provider");
					rapidxml::xml_node<WCHAR> *nodeComputer = nodeSystem->first_node(L"Computer");
					rapidxml::xml_node<WCHAR> *nodeTimeCreated = nodeSystem->first_node(L"TimeCreated");
					rapidxml::xml_node<WCHAR> *nodeTask = nodeSystem->first_node(L"Task");
					rapidxml::xml_node<WCHAR> *nodeLevel = nodeSystem->first_node(L"Level");

					if( debug >= DEBUG_L2 ) {
						wprintf( L"[DumpEventInfo]: Extracting XML elements successful\n" );
					}

					// Recall there are two modes. The default mode will parse the event log XML, and the "last record" mode
					// (called MODE_FETCH_LAST_RECORD) will fetch only the last record and exit afterwards. 
					if( mode == MODE_FETCH_LAST_RECORD ) {
						if( debug >= DEBUG_L2 ) {
							wprintf( L"[DumpEventInfo]: Record ID is '%s'\n", nodeEventRecordID->value() );
						}

						DWORD64 lastRecord = _wcstoui64( nodeEventRecordID->value(), NULL, 10 );

						if( debug >= DEBUG_L2 ) {
							wprintf( L"[DumpEventInfo]: Record ID converted to 64-bit number: %I64d\n", lastRecord );
						}

						return lastRecord;
					}

					// Extract the publisher name from the <Provider> node
					// We will need this to lookup the message string for this publisher
					LPWSTR pwszPublisherName = nodeProvider->first_attribute(L"Name")->value();

					if( debug >= DEBUG_L2 ) {
						wprintf( L"[DumpEventInfo] Publisher is: %s\n", pwszPublisherName );
					}

					// Setup an empty string to read the message string
					LPWSTR pwsMessage = NULL;

					// Get the handle to the provider's metadata that contains the message strings.
					EVT_HANDLE hProviderMetadata = EvtOpenPublisherMetadata(hRemote, pwszPublisherName, NULL, 0, 0);

					// If a provider handle was found
					if( hProviderMetadata != NULL ) 
					{
						if( debug >= DEBUG_L2 ) {
							wprintf( L"[DumpEventInfo] Publisher metadata found. Attempting to get message string\n");
						}

						// Get the message string associated with this event type
						pwsMessage = GetEventMessageDescription(hProviderMetadata, hEvent);

						// If a message was not found, default to an empty string
						if( pwsMessage == NULL ) {
							// Why are we setting to empty string?
							//pwsMessage = L"";

							if( debug >= DEBUG_L2 ) {
								wprintf( L"[DumpEventInfo] Message string not found. Assume empty\n");
							}
						}
					}
					else 
					{
						// Publisher/provider cannot be found. Do not display an error message. It occurs all too often when a 
						// publisher is not found, and skews the JSON results. when it prints itself to the main screen
						// printf("Error: EvtOpenPublisherMetadata for %s failed with %d\n", pwszPublisherName, GetLastError());						

						// Default the publisher to an empty string so we can continue
						pwszPublisherName = L"";

						if( debug >= DEBUG_L2 ) {
							wprintf( L"[DumpEventInfo] Publisher metadata not found. Assume empty\n");
						}
					}

					// We have all the results; print them to the screen
					if( outputFormat == OUTPUT_FORMAT_JSON ) 
					{
						wprintf(L"{\"record_id\":\"%s\",\"event_id\":\"%s\",\"logname\":\"%s\",\"source\":\"%s\",\"computer\":\"%s\",\"time_created\":\"%s\",\"task\":\"%s\",\"level\":\"%s\"", 
							nodeEventRecordID->value(), 
							nodeEventID->value(), 
							nodeChannel->value(), 
							nodeProvider->first_attribute(L"Name")->value(), 
							nodeComputer->value(), 
							nodeTimeCreated->first_attribute(L"SystemTime")->value(),
							nodeTask->value(),
							nodeLevel->value());
						
						// If a message string was found
						if( pwsMessage != NULL ) 
						{
							wprintf(L",\"message\":\"%s\"}", pwsMessage);

							if( debug >= DEBUG_L2 ) {
								wprintf( L"[DumpEventInfo] Attempting to free pwsMessage\n");
							}

							free(pwsMessage);

							if( debug >= DEBUG_L2 ) {
								wprintf( L"[DumpEventInfo] pwsMessage successfully freed\n");
							}
						} 
						else 
						{
							wprintf(L",\"message\":\"\"}");

							if( debug >= DEBUG_L2 ) {
								wprintf( L"[DumpEventInfo] No pwsMessage found to free\n");
							}
						}
					} 
					else 
					{
						// Note: A new line is not printed yet (see next steps)
						wprintf(L"%s||%s||%s||%s||%s||%s||%s||%s||", 
							nodeEventRecordID->value(), 
							nodeEventID->value(), 
							nodeChannel->value(), 
							nodeProvider->first_attribute(L"Name")->value(), 
							nodeComputer->value(), 
							nodeTimeCreated->first_attribute(L"SystemTime")->value(),
							nodeTask->value(),
							nodeLevel->value());

						// If a message string was found
						if( pwsMessage != NULL ) 
						{
							wprintf(L"%s\n", pwsMessage);
							free(pwsMessage);
						} 
						else 
						{
							wprintf(L"(no message provided)\n");
						}
					}
				} 
				else
				{
					// Reading was NOT successful

					// This time we were not expecting it to fail. Get the error code
					dwError = GetLastError();

					// Print error results to the screen
					fwprintf(stderr, L"[DumpEventInfo] Failed to render results with: %d\n", GetLastError());

					// Free up our allocation
					free(pwsBuffer);
				}				
            }
            else
            {
				// Allocation was unsuccessful
                fwprintf(stderr, L"[DumpEventInfo] malloc failed\n");
                dwError = ERROR_OUTOFMEMORY;
            }
        }
	}

	if( debug >= DEBUG_L2 ) {
		wprintf( L"[DumpEventInfo]: Data dump completed\n" );
	}

    return dwError;
}
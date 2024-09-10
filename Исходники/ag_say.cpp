int main(int argc, char **argv)
{
    ISpVoice *pVoice = NULL;
    WCHAR line_buffer[LINE_LENGTH];
    bool exitflag = FALSE;
    int counter = 0;

    if (FAILED(::CoInitialize(NULL)))
    {
        printf("ERROR: Couldn't initialise COM.\n");
        return FALSE;
    }

    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
    if( SUCCEEDED( hr ) )
    {
        // For some reason, if you don't do this, speech cuts out
        // (only on first announcement)...
        pVoice->Speak(L" ", SPF_IS_NOT_XML, NULL);

        // Main loop...
        while( ! exitflag )
        {
            for(counter = 0; counter < LINE_LENGTH; counter++ )
            {
                // Fill up the buffer...
                line_buffer[counter] = getwchar();

                // Check for exit condition...
                if( line_buffer[counter] == WEOF )
                {
                    line_buffer[counter] = 0;
                    exitflag = TRUE;
                    break;
                }

                // Break at end of line...
                if( line_buffer[counter] == L'\n' )
                {
                    line_buffer[counter] = 0;
                    break;
                }
            }

            counter = 0;

            // Should the synth's UI be displayed?
            if ( line_buffer == L"DisplayUI" )
            {
                int supported = 0;
                hr = pVoice->IsUISupported(SPDUI_EngineProperties, NULL, NULL, &supported);
                if( SUCCEEDED( hr ) && supported )
                {
                    hr = pVoice->DisplayUI(NULL, NULL, SPDUI_EngineProperties, NULL, NULL);
                    if( ! SUCCEEDED( hr ) )
                    {
                        pVoice->Speak(L"There was an error displaying the properties window.\n", SPF_IS_NOT_XML|SPF_ASYNC|SPF_PURGEBEFORESPEAK, NULL);
                    }
                }
                else
                {
                    pVoice->Speak(L"Your current voice doesn't support a properties window.\n", SPF_IS_NOT_XML|SPF_ASYNC|SPF_PURGEBEFORESPEAK, NULL);
                }
            }

            // Was the message high-priority?
            if( line_buffer[0] == L'!' )
            {
                line_buffer[0] = L' ';
                pVoice->Speak(line_buffer, SPF_IS_NOT_XML|SPF_ASYNC|SPF_PURGEBEFORESPEAK, NULL);
            }
            else
            {
                pVoice->Speak(line_buffer, SPF_IS_NOT_XML|SPF_ASYNC, NULL);
            }
        }

        // Allow the user to hear the rest of the speech buffer...
        pVoice->Speak(L" ", SPF_IS_NOT_XML, NULL);

        pVoice->Release();
        pVoice = NULL;
    }
    else
    {
        printf("ERROR: Couldn't initialise SAPI 5.1.\n");
    }

    ::CoUninitialize();
    return TRUE;
}
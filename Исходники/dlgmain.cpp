HRESULT CTTSApp::VoiceChange()
/////////////////////////////////////////////////////////////////
//
// This function is called during initialization and whenever the 
// selection for the voice combo box changes. 
// It gets the token pointer associated with the voice.
// If the new voice is different from the one that's currently 
// selected, it first stops any synthesis that is going on and
// sets the new voice on the global voice object. 
//
{
    HRESULT         hr = S_OK;
    GUID*           pguidAudioFormat = NULL;

    // Get the token associated with the selected voice
    ISpObjectToken* pToken = SpGetCurSelComboBoxToken( GetDlgItem( m_hWnd, IDC_COMBO_VOICES ) );
    
    //Determine if it is the current voice
    CComPtr<ISpObjectToken> pOldToken;
    hr = m_cpVoice->GetVoice( &pOldToken );

    if (SUCCEEDED(hr))
    {
        if (pOldToken != pToken)
        {        
            // Stop speaking. This is not necesary, for the next call to work,
            // but just to show that we are changing voices.
            hr = m_cpVoice->Speak( NULL, SPF_PURGEBEFORESPEAK, 0);
            // And set the new voice on the global voice object
            if (SUCCEEDED (hr) )
            {
                hr = m_cpVoice->SetVoice( pToken );
            }
        }
    }

    EnableSpeakButtons( SUCCEEDED( hr ) );

    return hr;
}
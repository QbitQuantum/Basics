bool OTNym_or_SymmetricKey::Seal_or_Encrypt(      OTEnvelope & outputEnvelope,
                                            const OTString     strInput,
                                            const OTString   * pstrDisplay/*=NULL*/)
{
    const char * szFunc = "OTNym_or_SymmetricKey::Seal_or_Encrypt";
    // --------------------------
    bool bSuccess                  = false;
    bool bHadToInstantiatePassword = false;
    // ---------------
	// Encrypt/Seal strInput into outputEnvelope
    //
    if (this->IsNym())
    {
        bSuccess = outputEnvelope.Seal(*(this->GetNym()), strInput);
    }
    // -------------------------------------------
    else if (this->IsKey())
    {
        OTPassword * pPassword = NULL;
        
        if (this->HasPassword()) // Password is already available. Let's use it.
            pPassword = this->GetPassword();
        else // no password? let's collect it from the user...
        {
            const OTString strDisplay((NULL == pstrDisplay) ? szFunc : pstrDisplay->Get());
            // NOTE: m_pstrDisplay overrides this below.
            // -------------------------------------------
            // returns a text OTPassword, or NULL.
            //
            pPassword = OTSymmetricKey::GetPassphraseFromUser((NULL == m_pstrDisplay) ? &strDisplay : m_pstrDisplay);//bool bAskTwice=false
            
            if (NULL == pPassword) // Unable to retrieve passphrase from user.
            {
                OTLog::vOutput(0, "%s: Failed trying to retrieve passphrase for key. "
                               "Returning false.\n", szFunc);
                return false;
            }
            else // OTNym_or_SymmetricKey stores this, if it creates it.
                 // (And cleans it up on destruction, IF it created it.)
                 //
                bHadToInstantiatePassword = true;
        }
        // -------------------------------------------
        //
        bSuccess = outputEnvelope.Encrypt(strInput, *(this->GetKey()), *pPassword);
        
        // We only set this, presuming we have to at all, if it was a success.
        if (bHadToInstantiatePassword)
        {
            if (bSuccess)
            {
                m_bCleanupPassword = true;
                m_pPassword        = pPassword; // Not bothering to cleanup whatever was here before, since we only end up here if m_pPassword was set to NULL (according to above logic...)
            }
            else // We instantiated the password, but the encrypt failed. (Need to cleanup the password then.)
            {
                delete pPassword;
                pPassword = NULL;
            }
        }
    }
    // else ? should never happen.
    // -----------------------------------
	return bSuccess;
}
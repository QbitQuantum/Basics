//----------------------------------------------------------------//
void MOAIHttpTaskCurl::AffirmHandle () {

	if ( this->mEasyHandle ) return;
	
	CURLcode result;
	
	this->mEasyHandle = curl_easy_init ();
	
	result = curl_easy_setopt ( this->mEasyHandle, CURLOPT_HEADERFUNCTION, _writeHeader );
	PrintError ( result );
	
	result = curl_easy_setopt ( this->mEasyHandle, CURLOPT_HEADERDATA, this );
	PrintError ( result );

	result = curl_easy_setopt ( this->mEasyHandle, CURLOPT_WRITEFUNCTION, _writeData );
	PrintError ( result );
	
	result = curl_easy_setopt ( this->mEasyHandle, CURLOPT_WRITEDATA, this );
	PrintError ( result );
	
	result = curl_easy_setopt ( this->mEasyHandle, CURLOPT_FAILONERROR, 1 );
	PrintError ( result );
	
	result = curl_easy_setopt ( this->mEasyHandle, CURLOPT_NOPROGRESS, 0 );
	PrintError ( result );
	
	result = curl_easy_setopt ( this->mEasyHandle, CURLOPT_PROGRESSDATA, this );
	PrintError ( result );
	
	result = curl_easy_setopt ( this->mEasyHandle, CURLOPT_PROGRESSFUNCTION, _progressFunction );
	PrintError ( result );
	
	result = curl_easy_setopt ( this->mEasyHandle, CURLOPT_SSL_VERIFYPEER, 0 );
	PrintError ( result );
	
	result = curl_easy_setopt ( this->mEasyHandle, CURLOPT_SSL_VERIFYHOST, 0 );
	PrintError ( result );

#ifdef USE_ARES
	result = curl_easy_setopt ( this->mEasyHandle, CURLOPT_NOSIGNAL, 1 );
	PrintError ( result );
#endif
}
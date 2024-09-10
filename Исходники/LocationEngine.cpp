void CLocationEngine::InsertIntoPayload(TInt aPosition, const TDesC8& aString, TPtr8& aLogStanza) {
	if(aLogStanza.Length() + aString.Length() > aLogStanza.MaxLength()) {
		iLogStanza = iLogStanza->ReAlloc(aLogStanza.MaxLength() + aString.Length() + 32);
		aLogStanza.Set(iLogStanza->Des());
	}

	aLogStanza.Insert(aPosition, aString);
}
FskErr KprZeroconfPlatformAdvertisementStart(KprZeroconfAdvertisement self)
{
	FskErr err = kFskErrNone;
	char* txt = NULL;
	UInt32 size = 0, offset = 0, length;
	KprZeroconfPlatformAdvertisement advertisement = self->platform;
	if (!advertisement->service) {
		DNSServiceErrorType error;
		DNSServiceRef serviceRef;
		FskAssociativeArrayIterator iterator = FskAssociativeArrayIteratorNew(self->txt);

		FskInstrumentedItemPrintfDebug(advertisement, "DNSServiceRegister %s %s %d\n", self->serviceName, self->serviceType, self->port);
		while (iterator) {
			UInt32 nameLength = FskStrLen(iterator->name);
			UInt32 valueLength = FskStrLen(iterator->value);
			length = nameLength + 1 + valueLength;
			if (length <= 255) {
				size += length + 1;
				err = txt ? FskMemPtrRealloc(size + 1, &txt) : FskMemPtrNew(size + 1, &txt);
				if (err)
					size -= length + 1;
				else {
					txt[offset++] = (char)length;
					FskStrCopy(txt + offset, iterator->name); offset += nameLength;
					txt[offset++] = '=';
					FskStrCopy(txt + offset, iterator->value); offset += valueLength;
					txt[offset] = 0;
				}
			}
			iterator = FskAssociativeArrayIteratorNext(iterator);
		}
		FskAssociativeArrayIteratorDispose(iterator);

		error = DNSServiceRegister(&serviceRef, 0, 0, self->serviceName, self->serviceType, "", NULL, // use default host name
					htons(self->port), txt ? FskStrLen(txt) : 0, txt, KprZeroconfPlatformAdvertisementProcess, self);
		if (error != kDNSServiceErr_NoError) {
			FskInstrumentedItemPrintfDebug(advertisement, "DNSServiceRegister error %d\n", error);
			bailIfError(kFskErrNetworkErr);
		}
		bailIfError(KprZeroconfPlatformServiceNew(&advertisement->service, NULL, serviceRef, NULL, 0));
	}
bail:
	FskMemPtrDispose(txt);
	return err;
}
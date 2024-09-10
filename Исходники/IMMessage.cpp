/*
 * Unformat the from address - removes blanks and converts to lower case
 *
 *  see IMAddressFormatter.unformat() - palm.com.messaging.data
 */
MojErr IMMessage::unformatFromAddress(const MojString formattedScreenName, MojString& unformattedName) {

	if(!formattedScreenName.empty()) {
		MojVector<MojString> stringTokens;
		MojErr err = formattedScreenName.split(' ', stringTokens);
		MojErrCheck(err);

		MojVector<MojString>::ConstIterator itr = stringTokens.begin();
		while (itr != stringTokens.end()) {
			err = unformattedName.append(*itr);
			MojErrCheck(err);
			itr++;
		}
		err = unformattedName.toLower();
		MojErrCheck(err);
	}
	return MojErrNone;
}
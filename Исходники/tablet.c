static void CommitFirstCandidate(FcitxTablet* tablet) {
	char s[5]; // five chars should be plenty to hold a utf-8 char
	char* candidates = tablet->engineInstance->GetCandidates(tablet->engineData);
	int l = mblen(candidates, 10);
	memcpy(s, candidates, l);
	s[l] = '\0';
	FcitxInstanceCommitString(tablet->fcitx, FcitxInstanceGetCurrentIC(tablet->fcitx), s);
}
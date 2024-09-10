void cBan::DisplayKick(ostream &os)
{
	os << "\t\t";

	if (mDateEnd) {
		cTime HowLong(mDateEnd - cTime().Sec(), 0);

		if (HowLong.Sec() < 0) {
			os << autosprintf(_("Expired %s"), cTime(mDateEnd, 0).AsDate().AsString().c_str());
		} else {
			os << HowLong.AsPeriod().AsString().c_str();
		}
	} else {
		os << _("Permanent");
	}

	os << "\t\t";

	if (!mLastHit)
		os << _("Never");
	else
		os << cTime(cTime().Sec() - mLastHit).AsPeriod().AsString();
}
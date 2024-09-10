int cServerDC::ValidateUser(cConnDC *conn, const string &nick, int &closeReason)
{
	// first validate the IP and host if any
	stringstream errmsg,os;
	// Default close reason
	closeReason = eCR_INVALID_USER;
	if (!conn) return 0;
	//time_t n;
	bool close=false;

	// phase 1: test nick validity
	// phase 2: test ip/host ban (registered users pass)
	// phase 3: test nickban
	// then we're done

	static cRegUserInfo *sRegInfo = new cRegUserInfo;
	if ((nick.size() < mC.max_nick * 2 ) && mR->FindRegInfo(*sRegInfo,nick) && !conn->mRegInfo ) {
		conn->mRegInfo = sRegInfo;
		sRegInfo = new cRegUserInfo;
	}

	// Validate nick
	tVAL_NICK vn = ValidateNick(nick, (conn->GetTheoricalClass() >= eUC_REGUSER ));
	if(vn != eVN_OK) {
		close=true;
		if(vn == eVN_BANNED) {
			errmsg << _("Do not reconnect too fast.") << " ";
			closeReason = eCR_RECONNECT;
		}
		else
			errmsg << _("Bad nickname") << ": ";
		if (conn->Log(2))
			conn->LogStream() << "Bad nick: '" << nick << "' (" << vn << ")" << endl;
	}
	switch(vn) {
		case eVN_OK:
		break;
		case eVN_CHARS:
			errmsg << _("Unallowed characters in your nick.");
			if(mC.nick_chars.size())
				 errmsg << autosprintf(_("use these: %s"), mC.nick_chars.c_str());
		break;
		case eVN_SHORT:
			errmsg << _("Your nick is too short.");
		break;
		case eVN_LONG:
			errmsg << _("Your nick is too long.");
		break;
		case eVN_USED: // never happens
			errmsg << _("Your nick is already in use.");
		break;
		case eVN_PREFIX:
			errmsg << autosprintf(_("Invalid nick prefix. Use: %s"), mC.nick_prefix.c_str());
		break;
		case eVN_NOT_REGED_OP:
			errmsg << _("Operator not registered.");
		break;
		case eVN_BANNED:
			errmsg << autosprintf(_("Wait %s before reconnecting."), cTime(mBanList->IsNickTempBanned(nick) - cTime().Sec()).AsPeriod().AsString().c_str());
		break;
		default:
			errmsg << _("Unknown error.");
		break;
	}

	if (close) {
		if (vn == eVN_USED) {
			static string omsg;
			omsg = "$ValidateDenide";
			conn->Send(omsg);
		}

		DCPublicHS(errmsg.str(), conn);
		if (conn->Log(3)) conn->LogStream() << "Bad nick: " << errmsg.str() << endl;
		return 0;
	}

	cBan Ban(this);
	bool banned = false;

	if (conn->GetTheoricalClass() < eUC_MASTER) { // master class is immune
		// here we cant check share ban because user hasnt sent $MyINFO yet
		if (conn->GetTheoricalClass() == eUC_NORMUSER)
			banned = mBanList->TestBan(Ban, conn, nick, eBF_NICK | eBF_NICKIP | eBF_RANGE | eBF_HOST2 | eBF_HOST1 | eBF_HOST3 | eBF_HOSTR1 | eBF_PREFIX);
		else // registered users avoid prefix ban check because we might actually ban a prefix for unregistered users, but let registered users to use it
			banned = mBanList->TestBan(Ban, conn, nick, eBF_NICK | eBF_NICKIP | eBF_RANGE | eBF_HOST2 | eBF_HOST1 | eBF_HOST3 | eBF_HOSTR1);
	}

	if (banned) {
		errmsg << _("You are banned from this hub.") << "\r\n";
		Ban.DisplayUser(errmsg);
		DCPublicHS(errmsg.str(), conn);
		if (conn->Log(1)) conn->LogStream() << "Unallowed user (" << Ban.mType << "), closing" << endl;
		return 0;
	}

	if (mC.nick_prefix_cc) {
		if (conn->mCC.size() && conn->mCC != "--") {
			string Prefix("[");
			Prefix += conn->mCC;
			Prefix += "]";

			if (StrCompare(nick, 0, 4, Prefix) != 0) {
				errmsg << autosprintf(_("Please add %s in front of your nick."), Prefix.c_str());
				close = conn->GetTheoricalClass() < eUC_REGUSER;
			}
		}
	}

	if (close) {
		DCPublicHS(errmsg.str(), conn);
		return 0;
	}

	return 1;
}
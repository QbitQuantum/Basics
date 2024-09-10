void CDPLoginSrvr::SendLoginProtect( const char* lpszAccount, const char* lpszPlayer, u_long idPlayer, BOOL bLogin, DPID dpId )
{
	BEFORESENDSOLE( ar, PACKETTYPE_LOGIN_PROTECT_CERT, dpId );
	ar.WriteString( lpszAccount );
	ar.WriteString( lpszPlayer );
	ar << idPlayer << bLogin;
	SEND( ar, this, DPID_ALLPLAYERS );
}
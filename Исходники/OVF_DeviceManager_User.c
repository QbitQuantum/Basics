SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRemoteUser(struct soap* hSoap, struct _tds__SetRemoteUser *tds__SetRemoteUser, struct _tds__SetRemoteUserResponse *tds__SetRemoteUserResponse)
{
  	NEW(lpRtUser,struct tt__RemoteUser);
    NEW(RtUser  ,REMOTEUSER);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	
	STRNCPY(RtUser->UserName,lpRtUser->Username,OVFCHARLENTH);
	STRNCPY(RtUser->UserPwd ,lpRtUser->Password,OVFCHARLENTH);
	RtUser->UserUseDerivedPwd=lpRtUser->UseDerivedPassword;
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetRemoteUser);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetRemoteUser( RtUser))return SOAP_FAULT;
    	
	return SOAP_OK;
}
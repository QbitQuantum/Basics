int UPPayNetRequest(const TDesC& aAddr,const char* result, char** response)
{
	int ret = 0; 
	CSyncHttpConnection* httpConnection = new CSyncHttpConnection();
	int len = strlen(result);
	TPtr8 ptr((TUint8 *)result,len,len);
	//CommonUtils::WriteLogL(_L("send!!!!!!!!!!!!!!!!!!!!!:\n"));
	//CommonUtils::WriteLogL(ptr,len);
	TBool error = EFalse;
	//httpConnection->GetRespone(_L("http://www.baidu.com"),error);//http://202.101.25.178:8080/Gateway/MobilePayment  //http://222.66.233.198:8080/Gateway/MobilePayment
	HBufC8* res = httpConnection->PostRespone(aAddr,ptr,error);////
	if(res)
	{
		len = res->Length()+1;
		*response = (char*)User::Alloc(len);
		if(*response)
		{
			memset(*response,0,len);
			Mem::Copy(*response,res->Ptr(),len-1);
			ret = 1;
			//CommonUtils::WriteLogL(_L("\nreceive!!!!!!!!!!!!!!!!!!!!!:\n"));
			//CommonUtils::WriteLogL(res->Des(),ret);
			//CommonUtils::WriteLogL(_L("\nend!!!!!!!!!!!!!!!!!!!!!\n"));
		}
	}
	delete httpConnection;
	return ret;
}
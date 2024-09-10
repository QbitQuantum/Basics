// ----------------------------------------------------
// CDbtestAppUi::HandleCommandL(TInt aCommand)
// ?implementation_description
// ----------------------------------------------------
//
void CDbtestAppUi::HandleCommandL(TInt aCommand)
{
	switch ( aCommand )
        {
        case EAknSoftkeyBack:
        case EEikCmdExit:
		{
			Exit();
			break;
		}
	case EdbtestCmdAppOBEX:
		//bt->transfer_logs();
		break;
        case EdbtestCmdAppTest:
		{
#if 0
			if (!is_open) {
				User::LeaveIfError(sockserv.Connect());
				User::LeaveIfError(sock.Open(sockserv, KAfInet, KSockStream, KUndefinedProtocol));
				TInetAddr a(INET_ADDR(128, 214, 48, 81) , 80);

				TRequestStatus s;
				sock.Connect(a, s);
				User::WaitForRequest(s);
				status_change(_L("opened"));
				is_open=true;
			} else {
				sock.CancelAll();
				sock.Close();
				sockserv.Close();
				status_change(_L("closed"));
				is_open=false;
			}
#else
#  if 0
			//transferer->log_gps();
			/*
			TInetAddr a(INET_ADDR(128, 214, 48, 81) , 21);
			ftp->Connect(a, _L8("tkt_cntx"), _L8("dKFJmqBi"));
			current_state=CONNECTING;
			*/
			/*
			run(this);
			*/
#  else
			//wap->Connect(1, _L("http://db.cs.helsinki.fi/~mraento/cgi-bin/put.pl"));
#  endif

#endif

		}
		break;
		
	case EdbtestCmdAppCommDb:
		{
			CCommDbDump* dump=CCommDbDump::NewL();
			CleanupStack::PushL(dump);
			dump->DumpDBtoFileL(_L("c:\\commdb.txt"));
			CleanupStack::PopAndDestroy();
		}
		break;
	case EdbtestCmdAppCert:
		{
			auto_ptr<CCertInstaller> i(CCertInstaller::NewL(AppContext()));
			i->InstallCertL(_L("c:\\hy.der"));
		}
	case EdbtestCmdAppDiscover:
		//discoverer->search();
		break;
	case EdbtestCmdAppCtmGSM:
		{
		TBuf<40> s;
		RDevRecharger c;
		TInt ret=0;
		TInt u=0;
		bool done=false;
		while (!done) {
			ret=c.Open(u);
			if (ret==KErrNone) {
				done=true;
			} else {
				++u;
				if (u==KNullUnit) done=true;
			}
		}
		if (ret!=KErrNone) {
			s.Format(_L("Open: %d"), ret);
		} else {
			TChargeInfoV1 i;
			i.iRawTemperature=i.iSmoothedTemperature=0;
			i.iChargeType=EChargeNone;
			TChargeInfoV1Buf b(i);
			c.ChargeInfo(b);
			s.Format(_L("%d r %d s %d t %d"), u, i.iRawTemperature, i.iSmoothedTemperature, i.iChargeType)	;
		}
		status_change(s);
		}
		break;

	case EdbtestCmdAppVibra:
		CFLDRingingTonePlayer* p;
		p=CFLDRingingTonePlayer::NewL(ETrue);
		p->SetVibra(ETrue);
		p->SetRingingType(0); 
		//((MFLDFileProcessor*)p)->ProcessFileL(_L("c:\\nokia\\sounds\\simple\\silent.rng"));
		((MFLDFileProcessor*)p)->ProcessFileL(_L("c:\\system\\apps\\context_log\\silent.rng"));
		break;
        default:
		break;      
        }
}
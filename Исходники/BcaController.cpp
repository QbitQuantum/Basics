void CBcaController::RunL()
/**
 *  AO async callback method. Called after request is completed. 
 *  
 */
	{
	OstTraceDef0(OST_TRACE_CATEGORY_DEBUG, TRACE_INTERNALS, CBCACONTROLLER_RUNL_1, "CBcaControl::RunL() called");
	switch (iState)
		{
		//in this state, Ioctl is called to set IAP ID, check the result of
		// Ioctl, then either set the BCA stack with another Ioctl call, 
		// open the BCA (if there's no BCA stack to set), or stop the NIF.
		case EIdling:
			{
			if(iStatus == KErrNone || iStatus == KErrNotSupported)
				{
				if(iStatus == KErrNotSupported)
					{
					OstTraceDef0(OST_TRACE_CATEGORY_DEBUG, TRACE_INTERNALS, CBCACONTROLLER_RUNL_2, "This BCA does not support IAPID set");
					}
				else
					{
					OstTraceDef0(OST_TRACE_CATEGORY_DEBUG, TRACE_INTERNALS, CBCACONTROLLER_RUNL_3, "This BCA supports IAPID set");
					}
				
				TPtrC bcaStack = iBCAProvisionConfig->GetBCAStack();
				if(bcaStack.Length())
					{
					TBuf8<KMaxName> remainingBcaStack8;
					remainingBcaStack8.Copy(bcaStack);
					iMBca->Control(iStatus, KBcaOptLevelGeneric,KBCASetBcaStack,remainingBcaStack8);
					}
				else
					{
					TRequestStatus* statusPtr=&iStatus;
					User::RequestComplete(statusPtr,KErrNone);
					}
				iState = EIAPSet;
				SetActive();	
				}
			else
				{
				OstTraceDef1(OST_TRACE_CATEGORY_DEBUG, TRACE_INTERNALS, CBCACONTROLLER_RUNL_4, "ERROR in BCA IAPID set = %d", iStatus.Int());
				Stop(iStatus.Int());
				}
			
			break;
			}			
		//in this case, we receive the result of Ioctl call to set Bca Stack.
		// Check the result of Ioctl, then Open and start the Bca or stop the NIF
		case EIAPSet:
			{
			if(iStatus == KErrNotSupported || iStatus == KErrNone)
				{
				if(iStatus == KErrNotSupported)
					{
					OstTraceDef0(OST_TRACE_CATEGORY_DEBUG, TRACE_INTERNALS, CBCACONTROLLER_RUNL_5, "This BCA does not support BCA stacking");
					}
				else
					{
					OstTraceDef0(OST_TRACE_CATEGORY_DEBUG, TRACE_INTERNALS, CBCACONTROLLER_RUNL_6, "This BCA supports BCA stacking");
					}
				iBcaParams = new(ELeave) MBca2::TBcaParams(const_cast<CBCAProvision*>(iBCAProvisionConfig)->GetCommsPond(), iBCAProvisionConfig->GetPortName());
			
				TInt aErr = iMBca->Open(*iUpperControl,*iUpperDataReceiver,*iBcaParams);
				if ( aErr != KErrNone)
					{					
					OstTraceDef1(OST_TRACE_CATEGORY_DEBUG, TRACE_INTERNALS, CBCACONTROLLER_RUNL_7, "ERROR in BCA Open = %d", aErr);
					Stop(iStatus.Int());
					iState = EIdling;
					}
				else
					{
					iMBca->Start();					
					}
				}
			else
				{
				OstTraceDef1(OST_TRACE_CATEGORY_DEBUG, TRACE_INTERNALS, CBCACONTROLLER_RUNL_8, "ERROR in BCA stack set = %d", iStatus.Int());
				Stop(iStatus.Int());
				}
			break;
			}
		// Wrong state.
		default:
			{
			OstTraceDef0(OST_TRACE_CATEGORY_DEBUG, TRACE_INTERNALS, CBCACONTROLLER_RUNL_9, "ERROR CBcaControl::RunL(): Unknown state");
			OstTraceDefExt2(OST_TRACE_CATEGORY_DEBUG, TRACE_INTERNALS, CBCACONTROLLER_RUNL_10, "PANIC: %S %d", KNifName, KBcaUnkownState);
			User::Panic(KNifName, KBcaUnkownState);
			break;
			}
		}

	}
OSStatus
CSecondPage::StartResolve( Service * service )
{
	CPrinterSetupWizardSheet	*	psheet;
	OSStatus						err = kNoErr;

	psheet = reinterpret_cast<CPrinterSetupWizardSheet*>(GetParent());
	require_quiet( psheet, exit );

	check( service->serviceRef == NULL );

	//
	// clean out any queues that were collected during a previous
	// resolve
	//

	service->EmptyQueues();

	//
	// now start the new resolve
	//

	err = DNSServiceResolve( &service->serviceRef, 0, 0, service->printer->name.c_str(), service->type.c_str(), service->domain.c_str(), (DNSServiceResolveReply) OnResolve, service );
	require_noerr( err, exit );

	err = StartOperation( service->serviceRef );
	require_noerr( err, exit );

	//
	// If we're not currently resolving, then disable the next button
	// and set the cursor to hourglass
	//

	if ( !service->printer->resolving )
	{
		psheet->SetWizardButtons( PSWIZB_BACK );

		psheet->m_active = psheet->m_wait;
		SetCursor(psheet->m_active);
	}

	service->printer->resolving++;

exit:

	return err;
}
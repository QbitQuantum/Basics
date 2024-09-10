void VJSDedicatedWorkerClass::_terminate (XBOX::VJSParms_callStaticFunction &ioParms, VJSWebWorkerObject *inDedicatedWorker)
{
	xbox_assert(inDedicatedWorker != NULL);

	VJSWorker	*outsideWorker	= VJSWorker::RetainWorker(ioParms.GetContext());
	VJSWorker	*insideWorker	= inDedicatedWorker->fOnMessagePort->GetOther(outsideWorker);
	
//**

	// ACI0081079: 
	//
	// Defensive programming, check pointer is not NULL. Pending definitive fix (and architecture overall in WAK5).
	// insideWorker should never be NULL !

	if (insideWorker != NULL)

		insideWorker->Terminate();


//**

	XBOX::ReleaseRefCountable<VJSWorker>(&outsideWorker);
}
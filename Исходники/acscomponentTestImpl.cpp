void ACSComponentTestClassImpl::shutdown ()
{
    ACS_SHORT_LOG((LM_INFO, "acscomponentTestImpl Shutdown")); 
    orb->shutdown(1);
 }
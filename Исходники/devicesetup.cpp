BOOL CDeviceSetup::GetSibling(PSP_DEVINFO_DATA pDevInfoData)
{
	assert(pDevInfoData!=NULL);
	if(pDevInfoData==NULL)
		return 0;

	DEVINST siblingDevInstance;
	if(CM_Get_Sibling(&siblingDevInstance,m_devInfoData.DevInst,0) != CR_SUCCESS)
		return 0;
	
	
	DevInstToDevInfoData(siblingDevInstance,pDevInfoData);

	return 1;


}
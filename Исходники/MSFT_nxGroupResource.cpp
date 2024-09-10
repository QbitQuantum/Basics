void MI_CALL MSFT_nxGroupResource_Invoke_InventoryTargetResource(
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxGroupResource* instanceName,
    _In_opt_ const MSFT_nxGroupResource_InventoryTargetResource* in)
{
    SCX_BOOKEND_EX ("Inventory", " name=\"nxGroup\"");
    MI_Result result = MI_RESULT_FAILED;
    if (self)
    {
        MI_Instance* retInstance;
	MI_NewDynamicInstance (
	    context, className,
	    0, &retInstance);

        result = self->inventory (in->InputResource.value->__instance, context,
                            retInstance);
        if (MI_RESULT_OK == result)
        {
            SCX_BOOKEND_PRINT ("packing succeeded!");
            MSFT_nxGroupResource_InventoryTargetResource out;
            MSFT_nxGroupResource_InventoryTargetResource_Construct (&out, context);
            MSFT_nxGroupResource_InventoryTargetResource_Set_MIReturn (&out, 0);


 {
		const MI_Uint32 c_initBufferLength = 1000000;
		MI_Application application;
		MI_Serializer serializer;
		MI_Uint8 *clientBuffer;
		MI_Uint32 clientBufferLength = c_initBufferLength;
		MI_Uint32 clientBufferNeeded = 0;
		const char * reportTemplateBase = DSC_ETC_PATH "/InventoryReports/nxGroup_XXXXXX";

		FILE *fp = NULL;
		
		clientBuffer = (MI_Uint8*)malloc(clientBufferLength + 1);
		MI_Application_Initialize(0,NULL,NULL, &application);
		result = XmlSerializer_Create(&application, 0, "MI_XML", &serializer);
		if (result != MI_RESULT_OK)
		{
		    MI_Application_Close(&application);
		    MI_Context_PostResult (context, result);
		    return;
		}
		
		result = XmlSerializer_SerializeInstance( &serializer, 0, retInstance, clientBuffer, clientBufferLength, &clientBufferNeeded);
		if (result != MI_RESULT_OK)
		{
		    free(clientBuffer);
		    if (clientBufferNeeded > 0)
		    {
			// Try again with a buffer given to us by the clientBufferNeeded field
			clientBufferLength = clientBufferNeeded;
			clientBuffer = (MI_Uint8*)malloc(clientBufferLength + 1);
			result = XmlSerializer_SerializeInstance( &serializer, 0, retInstance, clientBuffer, clientBufferLength, &clientBufferNeeded);
		    }
		    else
		    {
			XmlSerializer_Close(&serializer);
			MI_Application_Close(&application);
			MI_Context_PostResult (context, result);
			return;
		    }
		}
		
		XmlSerializer_Close(&serializer);
		MI_Application_Close(&application);
		if (result == MI_RESULT_OK)
		{
		    clientBuffer[clientBufferNeeded] = '\0';
		    printf((char*)clientBuffer);
		}

		
		{
		    char * reportTemplate = (char*)malloc(strlen(reportTemplateBase));
		    strcpy(reportTemplate, reportTemplateBase);
		    int fd = mkstemp(reportTemplate);
		    if (fd == -1)
		    {
			std::cerr << std::endl << "Error running mkstemp, errno = " << errno << std::endl;
		    }
		    fp = fdopen(fd, "w");
		    if( fp != NULL )
		    {
			fwrite(clientBuffer, 1, clientBufferNeeded, fp);
			fclose(fp);
		    }
		    else
		    {
			std::cerr << std::endl << "Error opening file descriptor for reportTemplate, errno = " << errno << std::endl;
		    }
		    free(reportTemplate);
		}
		
		free(clientBuffer);
	    }

            result = MSFT_nxGroupResource_InventoryTargetResource_Post (&out, context);
            if (MI_RESULT_OK != result)
            {
                SCX_BOOKEND_PRINT ("post Failed");
            }
            MSFT_nxGroupResource_InventoryTargetResource_Destruct (&out);
        }
        else
        {
            SCX_BOOKEND_PRINT ("inventory FAILED");
        }
        MI_Instance_Delete (retInstance);
    }
    MI_Context_PostResult (context, result);
}
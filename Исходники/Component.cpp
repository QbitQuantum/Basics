bool Component::Deinitialize(string caller)
{
    ofLogVerbose(__func__) << componentName << " by caller: " << caller;
    OMX_ERRORTYPE error = OMX_ErrorNone;

    
    
	if(handle)
	{
		
        flushAll();
		

        error = freeOutputBuffers();
        OMX_TRACE(error);
		freeInputBuffers();
        OMX_TRACE(error);
        
        if((componentName != "OMX.broadcom.egl_render") && (componentName != "OMX.broadcom.video_decode"))
        {
            if(getState() == OMX_StateExecuting)
            {
                setState(OMX_StatePause);
            }
            if(getState() != OMX_StateIdle)
            {
                setState(OMX_StateIdle);
            }
            if(getState() != OMX_StateLoaded)
            {
                setState(OMX_StateLoaded);
            }
        }
		
        if(componentName != "OMX.broadcom.video_decode")
        {
            error = OMX_FreeHandle(handle);
            OMX_TRACE(error); 
        }
		


		handle = NULL;
	}else
    {
        ofLogError(__func__) << "NO HANDLE! caller: " << caller;
    }

	inputPort    = 0;
	outputPort   = 0;
	//componentName = "";

    if(CustomFillBufferDoneHandler)
    {
        CustomFillBufferDoneHandler = NULL;
    }
	if(CustomEmptyBufferDoneHandler)
    {
       CustomEmptyBufferDoneHandler = NULL; 
    }
	

    ofLogVerbose(__func__) << componentName << " END";

	return true;
}
// -----------------------------------------------------------------------------
// UpnpAVCPEngine::RemoveSlashes
// -----------------------------------------------------------------------------
//   
void RemoveSlashes(TDes8& aPath) 
	{
	if (aPath.Length() > 0 && aPath[0] == '/' ) 
		{        
		aPath.Delete(0,1);
		}

	// remove ending '/' 
	TInt length = aPath.Length();                
	if (length > 0 && aPath[length-1] == '/' ) 
		{
		aPath.Delete(length-1,1);   
		}	   
	}
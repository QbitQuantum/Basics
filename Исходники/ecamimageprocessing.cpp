/** Get the sequence of all active transforms, ordered in order of execution.
 
@param aTransformSequence
	   an empty array to be populated with sequence of transform UIDs, 
	   where transform entries with smaller index are executed earlier. 
	
@leave KErrNoMemory Out of memory.  
*/
EXPORT_C void CCamera::CCameraImageProcessing::GetActiveTransformSequenceL(RArray<TUid>& aTransformSequence) const
	{
	iImpl->GetActiveTransformSequenceL(aTransformSequence);
	
	/* if CCamera::New2L() or CCamera::NewDuplicate2L() is not used to create CCamera object, it is assumed that 
    application is not prepared to receive extra added uid values (new settings added). So, any extra uid value passed 
    from the implementation will be filtered at this point.
    To receive extra added uid values, application should rather use CCamera::New2L() or CCamera::NewDuplicate2L() 
    to create camera object. In this case, application is assumed to be prepared to receive unrecognised uid values */
	if(iOwner.CameraVersion() == KCameraDefaultVersion)
		{
		for(TInt index =0; index < aTransformSequence.Count(); index++)
			{
			/** KBaselinedImageProcessing is the baseline. Any image processing attribute with greater uid value means that
			it has been added in later versions */
			if(aTransformSequence[index].iUid > KBaselinedImageProcessing)
				{
				aTransformSequence.Remove(index);
				index--;
				}
			}
		}
	}
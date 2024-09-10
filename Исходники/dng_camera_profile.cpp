bool dng_camera_profile::IsValid (uint32 channels) const
	{
	
	// For Monochrome images, we ignore the camera profile.
		
	if (channels == 1)
		{
		
		return true;
		
		}
		
	// ColorMatrix1 is required for all color images.
		
	if (fColorMatrix1.Cols () != 3 ||
		fColorMatrix1.Rows () != channels)
		{
		
		#if qDNGValidate
	
		ReportError ("ColorMatrix1 is wrong size");
					 
		#endif
					 
		return false;
		
		}
		
	// ColorMatrix2 is optional, but it must be valid if present.
	
	if (fColorMatrix2.Cols () != 0 ||
		fColorMatrix2.Rows () != 0)
		{
		
		if (fColorMatrix2.Cols () != 3 ||
			fColorMatrix2.Rows () != channels)
			{
			
			#if qDNGValidate
		
			ReportError ("ColorMatrix2 is wrong size");
						 
			#endif
					 
			return false;
			
			}
		
		}
		
	// ForwardMatrix1 is optional, but it must be valid if present.
	
	if (fForwardMatrix1.Cols () != 0 ||
		fForwardMatrix1.Rows () != 0)
		{
		
		if (fForwardMatrix1.Rows () != 3 ||
			fForwardMatrix1.Cols () != channels)
			{
			
			#if qDNGValidate
		
			ReportError ("ForwardMatrix1 is wrong size");
						 
			#endif
						 
			return false;
			
			}

		// Make sure ForwardMatrix1 does a valid mapping.
		
		if (!ValidForwardMatrix (fForwardMatrix1))
			{
			
			#if qDNGValidate
		
			ReportError ("ForwardMatrix1 does not map equal camera values to XYZ D50");
						 
			#endif
						 
			return false;
		
			}
				
		}

	// ForwardMatrix2 is optional, but it must be valid if present.
	
	if (fForwardMatrix2.Cols () != 0 ||
		fForwardMatrix2.Rows () != 0)
		{
		
		if (fForwardMatrix2.Rows () != 3 ||
			fForwardMatrix2.Cols () != channels)
			{
			
			#if qDNGValidate
		
			ReportError ("ForwardMatrix2 is wrong size");
						 
			#endif
						 
			return false;
			
			}

		// Make sure ForwardMatrix2 does a valid mapping.
		
		if (!ValidForwardMatrix (fForwardMatrix2))
			{
			
			#if qDNGValidate
		
			ReportError ("ForwardMatrix2 does not map equal camera values to XYZ D50");
						 
			#endif
						 
			return false;
		
			}
				
		}

	// ReductionMatrix1 is optional, but it must be valid if present.
	
	if (fReductionMatrix1.Cols () != 0 ||
		fReductionMatrix1.Rows () != 0)
		{
		
		if (fReductionMatrix1.Cols () != channels ||
			fReductionMatrix1.Rows () != 3)
			{
			
			#if qDNGValidate
		
			ReportError ("ReductionMatrix1 is wrong size");
						 
			#endif
					 
			return false;
			
			}
		
		}
	
	// ReductionMatrix2 is optional, but it must be valid if present.
	
	if (fReductionMatrix2.Cols () != 0 ||
		fReductionMatrix2.Rows () != 0)
		{
		
		if (fReductionMatrix2.Cols () != channels ||
			fReductionMatrix2.Rows () != 3)
			{
			
			#if qDNGValidate
		
			ReportError ("ReductionMatrix2 is wrong size");
						 
			#endif
					 
			return false;
			
			}
		
		}
		
	// Make sure ColorMatrix1 is invertable.
	
	try
		{
		
		if (fReductionMatrix1.NotEmpty ())
			{
			
			(void) Invert (fColorMatrix1,
						   fReductionMatrix1);
			
			}
			
		else
			{
		
			(void) Invert (fColorMatrix1);
			
			}
		
		}
		
	catch (...)
		{
			
		#if qDNGValidate
	
		ReportError ("ColorMatrix1 is not invertable");
					 
		#endif
					 
		return false;
	
		}
		
	// Make sure ColorMatrix2 is invertable.
	
	if (fColorMatrix2.NotEmpty ())
		{
						
		try
			{
			
			if (fReductionMatrix2.NotEmpty ())
				{
				
				(void) Invert (fColorMatrix2,
							   fReductionMatrix2);
				
				}
				
			else
				{
			
				(void) Invert (fColorMatrix2);
				
				}

			}
			
		catch (...)
			{
				
			#if qDNGValidate
	
			ReportError ("ColorMatrix2 is not invertable");
						 
			#endif
						 
			return false;
		
			}
			
		}

	return true;
	
	}
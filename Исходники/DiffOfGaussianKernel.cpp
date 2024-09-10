	bool DiffOfGaussianKernel<T, U>::Initialize_()
	{
		//if (m_dimension<5) return false;

		// create two gaussian deriv kernels

		PGCore::GaussianKernel<T, U> kernelOuter(m_sigmaOuter, m_dimension);
		PGCore::GaussianKernel<T, U> kernelInner(m_sigmaInner, m_dimension);
	
		

		kernelOuter-= kernelInner;
		
		memcpy(m_buffer, kernelOuter.GetBuffer(), m_dimension*sizeof(float));
		
		for(int i=0;i<(m_dimension);i++)
		{
			m_buffer[i]*=10;//m_dimension;		
		}
		

		/*
		float sum=0;
		for(int i=0;i<(m_dimension);i++)
		{
			m_buffer[i]*=50;//m_dimension;
			sum += m_buffer[i];			
		}
		
		if (sum<0)
		{
			float offset=abs(sum)/m_dimension;
			for (int i=0; i<(m_dimension); i++)
			{
				m_buffer[i] = offset;
			}			
		}		
		*/

#ifdef _DEBUG
		LOG0("{ The filter coefficients difference of gaussian are:");
		for(int i=0;i<(m_dimension);i++)
		{
			LOG2("Kernel[%d] = %f", i, (double)m_buffer[i]);
		}
		LOG0("} The filter coefficients.");
#endif

		//Reset()

		// experimental
		//  0	-1	-2	 -1	 0
		// -1	-2	-4	 -2	 1
		// -2	-4	 0	  4	 2
		// -1	 2	 4	  2	 1
		//  0	 1	 2	  1	 0
/*
		if (!m_orientY)
		{

			// fill up the buffer here
			SetValue(1, 0, (T)(-1.0f)); SetValue(3, 0, (T)(-1.0f));
			SetValue(1, 1, (T)(-2.0f)); SetValue(3, 1, (T)(-2.0f));
			SetValue(1, 3, (T)(2.0f));  SetValue(3, 3, (T)(2.0f));
			SetValue(1, 4, (T)(1.0f));  SetValue(3, 4, (T)(1.0f));

			SetValue(2, 0, (T)(-2.0f)); 
			SetValue(2, 1, (T)(-4.0f)); 
			SetValue(2, 3, (T)(4.0f));  
			SetValue(2, 4, (T)(2.0f));  

		} else
		{
			// fill up the buffer here
			SetValue(0, 1, (T)(-1.0f)); SetValue(0, 3, (T)(-1.0f));
			SetValue(1, 1, (T)(-2.0f)); SetValue(1, 3, (T)(-2.0f));
			SetValue(3, 1, (T)(2.0f));  SetValue(3, 3, (T)(2.0f));
			SetValue(4, 1, (T)(1.0f));  SetValue(4, 3, (T)(1.0f));

			SetValue(0, 2, (T)(-2.0f)); 
			SetValue(1, 2, (T)(-4.0f)); 
			SetValue(3, 2, (T)(4.0f));  
			SetValue(4, 2, (T)(2.0f));  

		}*/
		return true;
	}
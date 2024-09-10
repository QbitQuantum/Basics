 bool TMSIDriver::getSampleMatrixValue(MatrixXf& sampleMatrix)
{
    //Check if the driver DLL was loaded
    if(!m_bDllLoaded)
        return false;

    //Check if device was initialised and connected correctly
    if(!m_bInitDeviceSuccess)
    {
        cout << "Plugin TMSI - ERROR - getSampleMatrixValue() - Cannot start to get samples from device because device was not initialised correctly" << endl;
        return false;
    }

    sampleMatrix.setZero(); // Clear matrix - set all elements to zero
    uint iSamplesWrittenToMatrix = 0;
    int channelMax = 0;
    int sampleMax = 0;
    int sampleIterator = 0;

    //get samples from device until the complete matrix is filled, i.e. the samples per block size is met
    while(iSamplesWrittenToMatrix < m_uiSamplesPerBlock)
    {
        //Get sample block from device
        LONG ulSizeSamples = m_oFpGetSamples(m_HandleMaster, (PULONG)m_lSignalBuffer, m_lSignalBufferSize);
        LONG ulNumSamplesReceived = ulSizeSamples/(m_uiNumberOfAvailableChannels*4);

        //Only do the next steps if there was at least one sample received, otherwise skip and wait until at least one sample was received
        if(ulNumSamplesReceived > 0)
        {
            int actualSamplesWritten = 0; //Holds the number of samples which are actually written to the matrix in this while procedure

            //Write the received samples to an extra buffer, so that they are not getting lost if too many samples were received. These are then written to the next matrix (block)
            for(int i=0; i<ulNumSamplesReceived; i++)
            {
                for(uint j=i*m_uiNumberOfAvailableChannels; j<(i*m_uiNumberOfAvailableChannels)+m_uiNumberOfChannels; j++)
                    m_vSampleBlockBuffer.push_back((double)m_lSignalBuffer[j]);
            }

            //If the number of available channels is smaller than the number defined by the user -> set the channelMax to the smaller number
            if(m_uiNumberOfAvailableChannels < m_uiNumberOfChannels)
                channelMax = m_uiNumberOfAvailableChannels;
            else
                channelMax = m_uiNumberOfChannels;

            //If the number of the samples which were already written to the matrix plus the last received number of samples is larger then the defined block size
            //-> only fill until the matrix is completeley filled with samples. The other (unused) samples are still stored in the vector buffer m_vSampleBlockBuffer and will be used in the next matrix which is to be sent to the circular buffer
            if(iSamplesWrittenToMatrix + ulNumSamplesReceived > m_uiSamplesPerBlock)
                sampleMax = m_uiSamplesPerBlock - iSamplesWrittenToMatrix + sampleIterator;
            else
                sampleMax = ulNumSamplesReceived + sampleIterator;

            //Read the needed number of samples from the vector buffer to store them in the matrix
            for(; sampleIterator < sampleMax; sampleIterator++)
            {
                for(int channelIterator = 0; channelIterator < channelMax; channelIterator++)
                {
                    sampleMatrix(channelIterator, sampleIterator) = ((m_vSampleBlockBuffer.first() * (m_bUseUnitGain ? m_vUnitGain[channelIterator] : 1)) + (m_bUseUnitOffset ? m_vUnitOffSet[channelIterator] : 0)) * (m_bUseChExponent ? pow(10., (double)m_vExponentChannel[channelIterator]) : 1);
                    m_vSampleBlockBuffer.pop_front();
                }

                actualSamplesWritten ++;
            }

            iSamplesWrittenToMatrix = iSamplesWrittenToMatrix + actualSamplesWritten;
        }

        if(m_outputFileStream.is_open() && m_bWriteDriverDebugToFile)
        {
            m_outputFileStream << "samples in buffer: " << m_vSampleBlockBuffer.size()/m_uiNumberOfChannels << endl;
            m_outputFileStream << "ulSizeSamples: " << ulSizeSamples << endl;
            m_outputFileStream << "ulNumSamplesReceived: " << ulNumSamplesReceived << endl;
            m_outputFileStream << "sampleMax: " << sampleMax << endl;
            m_outputFileStream << "sampleIterator: " << sampleIterator << endl;
            m_outputFileStream << "iSamplesWrittenToMatrix: " << iSamplesWrittenToMatrix << endl << endl;
        }
    }

    if(/*m_outputFileStream.is_open() &&*/ m_bWriteDriverDebugToFile)
    {
        //Get device buffer info
        ULONG ulOverflow;
        ULONG ulPercentFull;
        m_oFpGetBufferInfo(m_HandleMaster, &ulOverflow, &ulPercentFull);

        m_outputFileStream <<  "Unit offset: " << endl;
        for(int w = 0; w<<m_vUnitOffSet.size(); w++)
            cout << float(m_vUnitOffSet[w]) << "  ";
        m_outputFileStream << endl << endl;

        m_outputFileStream <<  "Unit gain: " << endl;
        for(int w = 0; w<<m_vUnitGain.size(); w++)
            m_outputFileStream << float(m_vUnitGain[w]) << "  ";
        m_outputFileStream << endl << endl;

        m_outputFileStream << "----------<See output file for sample matrix>----------" <<endl<<endl;
        m_outputFileStream << "----------<Internal driver buffer is "<<ulPercentFull<<" full>----------"<<endl;
        m_outputFileStream << "----------<Internal driver overflow is "<<ulOverflow<< ">----------"<<endl;
    }

    return true;
}
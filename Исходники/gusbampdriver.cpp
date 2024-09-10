bool GUSBAmpDriver::getSampleMatrixValue(MatrixXf& sampleMatrix)
{
    sampleMatrix.setZero(); // Clear matrix - set all elements to zero

    for(int queueIndex=0; queueIndex<m_QUEUE_SIZE; queueIndex++)
    {
        //receive data from each device
        for (int deviceIndex = 0; deviceIndex < m_numDevices; deviceIndex++)
        {
            HANDLE hDevice = m_callSequenceHandles[deviceIndex];

            //wait for notification from the system telling that new data is available
            if (WaitForSingleObject(m_overlapped[deviceIndex][queueIndex].hEvent, 1000) == WAIT_TIMEOUT)
            {
                //throw string("Error on data transfer: timeout occurred.");
                cout << "Error on data transfer: timeout occurred." << "\n";
                return 0;
            }

            //get number of received bytes...
            GetOverlappedResult(hDevice, &m_overlapped[deviceIndex][queueIndex], &m_numBytesReceived, false);

            //...and check if we lost something (number of received bytes must be equal to the previously allocated buffer size)
            if (m_numBytesReceived != m_bufferSizeBytes)
            {
                //throw string("Error on data transfer: samples lost.");
                cout << "Error on data transfer: samples lost." << "\n";
                return 0;
            }
        }

        //store received data from each device in the correct order (that is scan-wise, where one scan includes all channels of all devices) ignoring the header
        //Data is aligned as follows: element at position destBuffer(scanIndex * (m_chNumberOfChannels + m_bTrigger) + channelIndex) * sizeof(float) + HEADER_SIZE is sample of channel channelIndex (zero-based) of the scan with zero-based scanIndex.
        //channelIndex ranges from 0..numDevices*numChannelsPerDevices where numDevices equals the number of recorded devices and numChannelsPerDevice the number of channels from each of those devices.
        //It is assumed that all devices provide the same number of channels.
        for (int scanIndex = 0; scanIndex < m_iNumberOfScans; scanIndex++)
        {
            for (int deviceIndex = 0; deviceIndex < m_numDevices; deviceIndex++)
            {
                for(int channelIndex = 0; channelIndex<m_chNumberOfChannels; channelIndex++)
                {
                    BYTE ByteValue[sizeof(float)];
                    float   FloatValue;

                    for(int i=0;i<sizeof(float);i++)
                    {
                        ByteValue[i] = m_buffers[deviceIndex][queueIndex][(scanIndex * (m_chNumberOfChannels + m_bTrigger) + channelIndex) * sizeof(float) + HEADER_SIZE + i];
                    }
                    memcpy(&FloatValue, &ByteValue, sizeof(float));

                    //store float-value to Matrix
                    sampleMatrix(channelIndex + deviceIndex*int(m_chNumberOfChannels), scanIndex + queueIndex * m_iNumberOfScans) = FloatValue;
                }
            }
        }

        //add new GetData call to the queue replacing the currently received one
        for (int deviceIndex = 0; deviceIndex < m_numDevices; deviceIndex++)
            if (!GT_GetData(m_callSequenceHandles[deviceIndex], m_buffers[deviceIndex][queueIndex], m_bufferSizeBytes, &m_overlapped[deviceIndex][queueIndex]))
            {
                cout << "\tError on GT_GetData.\n";
                return 0;
            }
    }
    return true;
}
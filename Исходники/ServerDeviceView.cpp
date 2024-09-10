bool ServerDeviceView::poll()
{
    bool bSuccessfullyUpdated= true;
    
    IDeviceInterface* device = getDevice();

    // Only poll data from open, bluetooth controllers
    if (device != nullptr && device->getIsReadyToPoll())
    {
        switch (device->poll())
        {
        case IDeviceInterface::_PollResultSuccessNoData:
            {
                long max_failure= device->getMaxPollFailureCount();
                
                ++m_pollNoDataCount;

                if (m_pollNoDataCount > max_failure)
                {
                    SERVER_LOG_INFO("ServerDeviceView::poll") <<
                    "Device id " << getDeviceID() << " closing due to no data (" << max_failure << " failed poll attempts)";
                    device->close();
                    
                    bSuccessfullyUpdated= false;
                }
            }
            break;
                
        case IDeviceInterface::_PollResultSuccessNewData:
            {
                m_pollNoDataCount= 0;
                m_lastNewDataTimestamp= std::chrono::high_resolution_clock::now();

                // If we got new sensor data, then we have new state to publish
                markStateAsUnpublished();

                bSuccessfullyUpdated= true;
            }
            break;
                
        case IDeviceInterface::_PollResultFailure:
            {
                SERVER_LOG_INFO("ServerDeviceView::poll") <<
                "Device id " << getDeviceID() << " closing due to failed read";
                device->close();
                
                bSuccessfullyUpdated= false;
            }
            break;
        }
    }
    
    return bSuccessfullyUpdated;
}
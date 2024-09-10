static BluetoothPairDeviceState::eStatus
AsyncBluetoothPairDeviceRequest__setupBluetoothRadio(
    BluetoothPairDeviceState *state)
{
    assert(state->isWorkerThread());
    BluetoothPairDeviceState::eStatus nextSubStatus= 
        state->getSubStatus_WorkerThread<BluetoothPairDeviceState::eStatus>();

    /* NOTE: Order matters for the following two operations: The radio must
        *       allow incoming connections prior to being made discoverable.
        */
    if (!BluetoothIsConnectable(state->hRadio)) 
    {
        SERVER_MT_LOG_INFO("AsyncBluetoothPairDeviceRequest") 
            << "Making radio accept incoming connections";

        if (BluetoothEnableIncomingConnections(state->hRadio, TRUE) == FALSE) 
        {
            SERVER_MT_LOG_ERROR("AsyncBluetoothPairDeviceRequest") 
                << "Failed to enable incoming connections on radio " << state->host_address_string;
        }
    }

    if (!BluetoothIsDiscoverable(state->hRadio))                 
    {
        SERVER_MT_LOG_INFO("AsyncBluetoothPairDeviceRequest") 
            << "Making radio discoverable";

        if (BluetoothEnableDiscovery(state->hRadio, TRUE) == FALSE) 
        {
            SERVER_MT_LOG_ERROR("AsyncBluetoothPairDeviceRequest") 
                << "Failed to enable radio " << state->host_address_string << " discoverable";
        }
    }

    if (BluetoothIsConnectable(state->hRadio) != FALSE && BluetoothIsDiscoverable(state->hRadio) != FALSE)
    {
        nextSubStatus= BluetoothPairDeviceState::deviceScan;
    }
    else
    {
        nextSubStatus= BluetoothPairDeviceState::failed;
    }

    return nextSubStatus;
}
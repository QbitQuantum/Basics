static int
set_up_bluetooth_radio(const HANDLE hRadio)
{
    /* NOTE: Order matters for the following two operations: The radio must
     *       allow incoming connections prior to being made discoverable.
     */

    if (!BluetoothIsConnectable(hRadio)) {
        WINPAIR_DEBUG("Making radio accept incoming connections");
        if (BluetoothEnableIncomingConnections(hRadio, TRUE) == FALSE) {
            WINPAIR_DEBUG("Failed to enable incoming connections");
            return 1;
        }
    }

    if (!BluetoothIsDiscoverable(hRadio)) {
        WINPAIR_DEBUG("Making radio discoverable");
        if (BluetoothEnableDiscovery(hRadio, TRUE) == FALSE) {
            WINPAIR_DEBUG("Failed to make radio discoverable");
            return 1;
        }
    }

    if ((BluetoothIsConnectable(hRadio) != FALSE) && (BluetoothIsDiscoverable(hRadio) != FALSE)) {
        return 0;
    } else {
        return 1;
    }
}
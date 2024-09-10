bool QBluetoothServiceInfoPrivate::unregisterService()
{
    if (!registered)
        return false;
    if (serverChannel() == -1)
        return false;
    if ( __fakeServerPorts.key(serverChannel()) != 0) {
#ifdef QT_QNX_BT_BLUETOOTH
        QByteArray b_uuid = attributes.value(QBluetoothServiceInfo::ServiceId).
                value<QBluetoothUuid>().toByteArray();
        b_uuid = b_uuid.mid(1, b_uuid.length() - 2);
        if (bt_spp_close_server(b_uuid.data()) == -1)
            return false;
#else
        if (!ppsSendControlMessage("deregister_server", 0x1101, attributes.value(QBluetoothServiceInfo::ServiceId).value<QBluetoothUuid>(), QString(),
                                   attributes.value(QBluetoothServiceInfo::ServiceName).toString(),
                                   __fakeServerPorts.key(serverChannel()), BT_SPP_SERVER_SUBTYPE)) {
            return false;
        }
#endif
        else {
            __fakeServerPorts.remove(__fakeServerPorts.key(serverChannel()));
            registered = false;
            return true;
        }
    }
    else {
        return false;
    }
}
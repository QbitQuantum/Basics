 void NObjBroadcastReceiver::setMac(QString mac)
 {
     m_mac = CCompareMacInLower ? mac.toLower() : mac.toUpper();
 }
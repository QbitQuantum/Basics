void CEC_TV::OnReceive(int source, int dest, unsigned char* buffer, int count){
    //#ifdef DEBUG_CODES
        debugReceivedMsg(source, dest, buffer, count);
    //#endif //#DEBUG_CODES

    if (count /*&& (dest == _logicalAddress || dest == CECDEVICE_BROADCAST)*/){
        switch(buffer[0]){
            case CEC_OPCODE_IMAGE_VIEW_ON:
            case CEC_OPCODE_TEXT_VIEW_ON:
                powerOn();
                break;
            case CEC_OPCODE_STANDBY:
                powerOff();
                break;
            case CEC_OPCODE_GET_CEC_VERSION:
                TransmitMsg(source, 2, CEC_OPCODE_CEC_VERSION, 0x04);//hdmi 1.3a
            case CEC_OPCODE_CEC_VERSION:
                devices[source].cec_ver = (cec_version)buffer[1];
                break;
            case CEC_OPCODE_GIVE_PHYSICAL_ADDRESS:
                TransmitMsg(source, 4, CEC_OPCODE_REPORT_PHYSICAL_ADDRESS, 0, 0, CDT_TV);
                break;
            case CEC_OPCODE_GIVE_DEVICE_POWER_STATUS:
                TransmitMsg(source, 2, CEC_OPCODE_REPORT_POWER_STATUS, _powerStatus);
                break;
            case CEC_OPCODE_ACTIVE_SOURCE:
                /*if (_powerStatus == CEC_POWER_STATUS_ON)
                {
                    _activeSrcBroadcast = 0;
                    DbgPrint("changing to input %d\r\n", buffer[1]>>4 & 0xf);
                    //changeKoganInput(&irsend, buffer[1]>>4 & 0xf);
                    //irrecv.enableIRIn(); // Re-enable receiver
                    changeInputI2c(buffer[1]>>4 & 0xf);

                }*/
                active_src1 = buffer[1];
                active_src2 = buffer[2];
                DbgPrint("Got active src of %02X.%02X\n", active_src1, active_src2);
                DbgPrint("Asking for OSD: %d\n", TransmitMsg(source, 1,CEC_OPCODE_GIVE_OSD_NAME));
                DbgPrint("Asking for audio mode: %d\n", RequestAudio(byte_combine_2(active_src1, active_src2)));
                TransmitMsg(source, 2, CEC_OPCODE_MENU_REQUEST, CEC_MENU_REQUEST_TYPE_QUERY);
                break;
            case CEC_OPCODE_ROUTING_INFORMATION:
                active_src1 = buffer[1];
                active_src2 = buffer[2];
                RequestAudio(byte_combine_2(active_src1, active_src2));
                break;
            case CEC_OPCODE_ROUTING_CHANGE:
                active_src1 = buffer[3];
                active_src2 = buffer[4];
                RequestAudio(byte_combine_2(active_src1, active_src2));
                break;
            case CEC_OPCODE_INACTIVE_SOURCE:
                /*if (_powerStatus == CEC_POWER_STATUS_ON)
                    broadcastForActiveSource(true);//this probably shows up with nothing as other sources assume they're not active, but we check to be sure.
                    DbgPrint("TODO 139, cectv\r\n");*/
                break;
            case CEC_OPCODE_MENU_STATUS:
                if (buffer[1] == CEC_MENU_STATE_ACTIVATED)
                    _sendUCTo = source;
                else
                    _sendUCTo = 0;
                break;
            case CEC_OPCODE_REPORT_POWER_STATUS:
                #ifdef DEBUG_CODES
                    DbgPrint("device at logical %d is ", source);
                    switch (buffer[1]){
                        case CEC_POWER_STATUS_ON:
                            Serial.print("On");
                            break;
                        case CEC_POWER_STATUS_STANDBY:
                            Serial.print("on Standby");
                            break;
                        case CEC_POWER_STATUS_IN_TRANSITION_STANDBY_TO_ON:
                            Serial.print("Turning On");
                            break;
                        case CEC_POWER_STATUS_IN_TRANSITION_ON_TO_STANDBY:
                            Serial.print("Turning Off");
                            break;
                        default:
                            DbgPrint("UNKNOWN STATUS (%d)", buffer[1]);
                            break;
                    }
                    Serial.print("\r\n");
                #endif
                devices[source].power_status = (cec_power_status)buffer[1];
                break;
            case CEC_OPCODE_REPORT_PHYSICAL_ADDRESS:
                DbgPrint("Device at logical %X is at %02X%02X device type %02X\r\n", source, buffer[1],buffer[2], buffer[3]);
                devices[source].phy_addr = byte_combine_2(buffer[1], buffer[2]);
                break;
            case CEC_OPCODE_SET_OSD_NAME:
                {
                    short osdLen = count -1;
                    if (osdLen){
                        char* osdName = new char[osdLen];
                        memcpy(osdName, buffer+1, osdLen);
                        osdName[osdLen] = 0;
                        #ifdef DEBUG_CODES
                        DbgPrint("Device at logical %X is known as \"%s\"\r\n", source, osdName);
                        #endif
                        if (devices[source].osd_name)
                            delete devices[source].osd_name;
                        devices[source].osd_name = osdName;
                    }
                    break;
                }
            case CEC_OPCODE_SET_SYSTEM_AUDIO_MODE://this tells us that the receiver is on/off
                subSwitch.send(buffer[1] ? SWITCH_CODE_0_ON : SWITCH_CODE_0_OFF, 24);
                DbgPrint("AUdio mode set: %x\r\n", buffer[1]);
                break;
            case CEC_OPCODE_DEVICE_VENDOR_ID:
                {
                    cec_vendor_id vendorid = (cec_vendor_id) byte_combine_3(buffer[1], buffer[2], buffer[3]);
                    DbgPrint("Device at logical %X is a %s (%06lX)\n", source, vendor_tostring(vendorid), vendorid);
                    devices[source].vendor_id = vendorid;
                    break;
                }
            //no response messages:
            case  CEC_OPCODE_FEATURE_ABORT:
            case  CEC_OPCODE_SYSTEM_AUDIO_MODE_STATUS://receiver giving volume status
                break;
            default:
                if (dest != CECDEVICE_BROADCAST){//dont wanna do for bcast
                    Serial.print("ABORT!\r\n");
                    TransmitMsg(source, 2,  CEC_OPCODE_FEATURE_ABORT, CEC_ABORT_REASON_UNRECOGNIZED_OPCODE);
                }
                break;
        }
    }
}
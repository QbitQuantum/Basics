void ofxModbusTcpClient::updateRegisters(int _id, int _startAddress, int _qty) {
    if (enabled) {
        if (_id<=numberOfSlaves && _id>0 && _qty<=125 && _qty>0) {
            uint8_t localByteArray[12];
            
            WORD tx = getTransactionID();
            WORD length = 6;
            WORD start = _startAddress-1;
            WORD qty = _qty;
            
            localByteArray[0] = HIGHBYTE(tx); //Transaction High
            localByteArray[1] = LOWBYTE(tx); //Transaction Low
            localByteArray[2] = 0x00; //Protocal Identifier High
            localByteArray[3] = 0x00; //Protocol Identifier Low
            localByteArray[4] = HIGHBYTE(length); //Length High
            localByteArray[5] = LOWBYTE(length); //Length Low
            localByteArray[6] = _id; //Unit Idenfifier
            localByteArray[7] = 0x03; //Function Code
            localByteArray[8] = HIGHBYTE(start); //Start Address High
            localByteArray[9] = LOWBYTE(start); //Start Address Low
            localByteArray[10] = HIGHBYTE(qty); //Qty High
            localByteArray[11] = LOWBYTE(qty); //Qty Low
            
            lastStartingReg = start;
            
            stringstream dm;
            dm<<"Reading Registers of "<<_id<<" Start:"<<_startAddress<<" Qty:"<<_qty;
            
            vector<uint8_t> lba;
            int sizeOfArray = sizeof(localByteArray) / sizeof(localByteArray[0]);
            for (int i=0; i<sizeOfArray; i++){
                lba.push_back(localByteArray[i]);
            }
            
            mbCommand c;
            c.msg = lba;
            c.length = length;
            c.timeAdded = ofGetElapsedTimeMillis();
            c.debugString = dm.str();
            commandToSend.push_back(c);
        } else {
            ofLogError("ofxModbusTCP IP:"+ip)<<"Read Registers Parameters Are Out Of Range";
        }
    }
}
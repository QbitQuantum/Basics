// Reading SMS's is a bit involved so we don't use helpers that may cause delays or debug
// printouts!
bool Adafruit_FONA::readSMS(uint8_t i, char *smsbuff, uint16_t maxlen, uint16_t *readlen) {
    // text mode
    if (! sendCheckReply(F("AT+CMGF=1"), F("OK"))) return false;
    
    // show all text mode parameters
    if (! sendCheckReply(F("AT+CSDH=1"), F("OK"))) return false;
    
    // parse out the SMS len
    uint16_t thesmslen = 0;
    
    //getReply(F("AT+CMGR="), i, 1000);  //  do not print debug!
    mySerial->print(F("AT+CMGR="));
    mySerial->println(i);
    readline(1000); // timeout
    
    // parse it out...
    parseReply(F("+CMGR:"), &thesmslen, ',', 11);
    
    readRaw(thesmslen);
    
    flushInput();
    
    uint16_t thelen = min(maxlen, strlen(replybuffer));
    strncpy(smsbuff, replybuffer, thelen);
    smsbuff[thelen] = 0; // end the string
    
    #ifdef ADAFRUIT_FONA_DEBUG
    Serial.println(replybuffer);
    #endif
    *readlen = thelen;
    return true;
}
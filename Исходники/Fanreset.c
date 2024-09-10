//-------------------------------------------------------------------------
//  read a byte from the embedded controller (EC) via port io 
//-------------------------------------------------------------------------
int ReadByteFromEC(int offset, byte *pdata)
{
	int ok;

	// wait for IBF and OBF to clear
	ok = waitportstatus(EC_STAT_IBF|EC_STAT_OBF, 0);
	if (!ok) return false;
	    
    // tell 'em we want to "READ"
    ok = writeport(EC_CTRLPORT, EC_CTRLPORT_READ);
    if (!ok) return false;
        
    // wait for IBF to clear (command byte removed from EC's input queue)
    ok = waitportstatus(EC_STAT_IBF, 0);
    if (!ok) return false;
        
    // tell 'em where we want to read from
    ok = writeport(EC_DATAPORT, offset);
    if (!ok) return false;
    
    // wait for IBF to clear (address byte removed from EC's input queue)
    // Note: Techically we should waitportstatus(IBF|OBF,OBF) here. (a byte 
    //  being in the EC's output buffer being ready to read). For some reason
    //  this never seems to happen
    ok = waitportstatus(EC_STAT_IBF, 0);
    if (!ok) return false;
    
    // read result (EC byte at offset)
    byte data;
    ok = readport(EC_DATAPORT, &data);
    if (ok) *pdata= data;

	return ok;
}
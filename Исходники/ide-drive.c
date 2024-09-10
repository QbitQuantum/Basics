int DriveStatus(BYTE_WIDE drive, WORD_WIDE* buf){

    int i;
    unsigned erroria=0;
    IDESoftReset();


    erroria=setHead(drive); //LBA access!
    delayShort();
    if (erroria&ERR){
        return READ_ERROR; //error reading
    }

    //delayCIA();
    i=20000;
    TF_COMMAND=ATA_IDENTIFY_DRIVE;
    delayShort();

    erroria=TF_ALTERNATE_STATUS;
    delayShort();
    while (erroria&BSY!=0&&i>0 )
    {
        erroria = TF_ALTERNATE_STATUS;
        delayShort();
        i--;
    };

    erroria = TF_STATUS; //an atapi drive reports 0 here!

    if (erroria&ERR){
        return READ_ERROR; //error reading
    }

    if (erroria&DWF){
        return WRITE_ERROR; //error writing
    }

    if (erroria==0 ){ //atapi drive
        TF_COMMAND=ATA_IDENTIFY_PACKET_DEVICE;
        i=20000;
        erroria=TF_ALTERNATE_STATUS;
	    delayShort();
        while (erroria&BSY!=0&&i>0 )
        {
            erroria = TF_ALTERNATE_STATUS;
            delayShort();
            i--;
        };

        if(i>0){
            return DriveType(buf);
        }
        else{
            return TIME_OUT;
        }
    }

    if (i<=0){ //time out
        return TIME_OUT;
    }
    else{
        return DriveType(buf);

    }

}
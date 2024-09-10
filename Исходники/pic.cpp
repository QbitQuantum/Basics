void PIC::decodeCmd(int pc)
{
//    {

        qDebug() << "CMDLIST" <<m_CmdList[pc];
        //qDebug() << pc << "PC";
        k_long=m_CmdList[pc] & 0x7FF;
        //qDebug() << k_long << "klong";
        k=m_CmdList[pc] & 0xFF;
        qDebug() << k << "k";
        f=m_CmdList[pc] & 0x7F;
        //qDebug() << f <<"f";
        d=m_CmdList[pc] & 0x80;
        d=(d>>7); //Test
        l=d;
        b=m_CmdList[pc] & 0x380;
        b = b / 128;
        //qDebug() << b << "b";
        qDebug() << PreScalerWert << "PreScalerWert";

        PIC::getPreScaler();
        PIC::SetBank();
        PIC::ChkIndirect();



        CheckIndirect();

     int ByteCmd=m_CmdList[pc] & 0x3F00;
     //qDebug() << ByteCmd << "byteCMD";
     int BitCmd=m_CmdList[pc] & 0x3C00;
     //qDebug() << BitCmd << "BitCMD";
     int ShrtCmd=m_CmdList[pc] & 0x3800;
     //qDebug() << ShrtCmd << "ShrtCMD";


     if(ByteCmd == 0x0700 )
        ADDWF();
     else if(ByteCmd == 0x0500)
        ANDWF();
     else if((m_CmdList[pc] & 0x03F80)  == 0x0180)
        CLRF();
     else if(ByteCmd == 0x0100)
        CLRW();
     else if(ByteCmd == 0x0900)
        COMF();
     else if(ByteCmd == 0x0300)
        DECF();
     else if(ByteCmd == 0x0B00)
        DECFSZ();
     else if(ByteCmd == 0x0A00)
        INCF();
     else if(ByteCmd == 0x0F00)
        INCFSZ();
     else if(ByteCmd == 0x0400)
        IORWF();
     else if(ByteCmd == 0x0800)
        MOVF();
     else if((m_CmdList[pc] & 0x3F80) == 0x0080)
        MOVWF();
     else if((m_CmdList[pc] & 0x3F9F) == 0x0000)
        NOP();
     else if(ByteCmd == 0x0D00)
        RLF();
     else if(ByteCmd == 0x0C00)
        RRF();
     else if(ByteCmd == 0x0200)
        SUBWF();
     else if(ByteCmd == 0x0E00)
        SWAPF();
     else if(ByteCmd == 0x0600)
        XORWF();
     else if(BitCmd == 0x1000)
        BCF();
     else if(BitCmd == 0x1400)
        BSF();
     else if(BitCmd == 0x1800)
        BTFSC();
     else if(BitCmd == 0x1C00)
        BTFSS();
     //ADDLW kann durch don't care Bit 3E bzw. 3F sein
     else if((m_CmdList[pc] & 0x3E00 ) == 0x3E00)
        ADDLW();
     else if((m_CmdList[pc] & 0x3F00 ) == 0x3F00)
        ADDLW();
     else if(ByteCmd == 0x3900)
        ANDLW();
     else if(ShrtCmd == 0x2000)
        CALL();
     else if((m_CmdList[pc]& 0XFFFF) == 0x0064)
        CLRWDT();
     else if(ShrtCmd == 0x2800)
        GOTO();
     else if((ByteCmd) == 0x3A00)
        XORLW();
     else if((m_CmdList[pc] & 0x3E00 ) == 0x3C00)
        SUBLW();
     else if((m_CmdList[pc] & 0xFFFF ) == 0x0063)
        SLEEP();
    else if((m_CmdList[pc] & 0xFFFF ) == 0x0008)
        RETURN();
    else if((BitCmd) == 0x3400)
        RETURNLW();
    else if((m_CmdList[pc] & 0xFFFF ) == 0x0009)
        RETURNFIE();
    else if((ByteCmd) == 0x3000)
        MOVLW();
    else if((ByteCmd) == 0x3100)
        MOVLW();
    else if((ByteCmd) == 0x3200)
        MOVLW();
    else if((ByteCmd) == 0x3300)
        MOVLW();
    else if((ShrtCmd) == 0x3800)
        IORLW();

    //zählt nach jeder Befehlsabarbeitung einen Programmzyklus hoch, bizyklische Befehle zählen zusätzlich während des Befehls rauf
     PIC::ExtClock();
     PIC::IncrementCycles();
     PIC::setTmr0();
     PIC::LaufZeit();
     //PreScalerCounter++;
     PIC::SyncSpecialReg();
     PIC::RBPeakAnalyzer();
     PIC::InterruptAnalyzer();


     //Diagnoseausgaben
     qDebug() << "---------------------------------";
     //qDebug() << regModel->reg[bank][PORTB] << "PortB";
     qDebug() << regModel->reg[bank][INDIRECT] << "INDIRECT";
     qDebug() << regModel->reg[bank][FSR] << "FSR";
     //qDebug() << regModel->reg[bank][0x15] << "15h";
     qDebug() << cycles << "Programmzyklen";
     qDebug() << "---------------------------------";

}
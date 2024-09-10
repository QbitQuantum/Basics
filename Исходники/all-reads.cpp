int main(int argc, char** argv){
   
    Port* port = new Port("/dev/ttyUSB0");
    if(port->OpenPort() == false){
        fprintf(stderr, "\n Fail to open port\n");
        fprintf(stderr, " CM-730 is used by another program or do not have root privileges.\n\n");
        return 0;
    }

    //dxl power on stuff
    //(WriteByte(CM730::ID_CM, CM730::P_DXL_POWER, 1, 0)

    unsigned char dxltxpacket[] = {0xFF, 0xFF, 0xC8, 0x04, 0x03, 0x18, 0x01, 0};
    dxltxpacket[7] = CalculateChecksum(dxltxpacket);
    port->WritePort(dxltxpacket, 8);

    printf("Finshed dxl power up. Press enter\n");
    getchar();

    unsigned char rxpacket[MAXNUM_RXPARAM + 10] = {0, };
    //unsigned char txpacket[MAXNUM_TXPARAM + 10] = {0, };
    //txpacket = {0xFF, 0xFF, id, 4, INST_READ, start address, 2, checksum};

    unsigned char txpacketread[] = {0xFF, 0xFF, 0x14, 0x04, 0x02, 0x24, 0x02, 0};
    int length = txpacketread[LENGTH] + 4;
    
    txpacketread[length-1] = CalculateChecksum(txpacketread);


    // make bulkread packet
    int number = 0;

    unsigned char BulkReadTxPacket[MAXNUM_TXPARAM + 10] = {0, };

    BulkReadTxPacket[0] = 0xFF;
    BulkReadTxPacket[1] = 0xFF;
    BulkReadTxPacket[ID] = 0xFE;
    BulkReadTxPacket[INSTRUCTION] = 0x92;
    BulkReadTxPacket[PARAMETER] = 0x0;
    
    if(Ping(0xC8, 0, port)){
        BulkReadTxPacket[PARAMETER+3*number+1] = 30; //length
        BulkReadTxPacket[PARAMETER+3*number+2] = 0xC8; // ID_CM
        BulkReadTxPacket[PARAMETER+3*number+3] = 24; //P_DXL_POWER
        number++;
    }

    if(Ping(70, 0, port)){
        BulkReadTxPacket[PARAMETER+3*number+1] = 10;    // length
        BulkReadTxPacket[PARAMETER+3*number+2] = 0x70;  // ID_L_FSR
        BulkReadTxPacket[PARAMETER+3*number+3] = 0x1A;  // start address P_FSR1_L
        number++;
    }

    if(Ping(0x6F, 0, port)){
        BulkReadTxPacket[PARAMETER+3*number+1] = 10;     // length
        BulkReadTxPacket[PARAMETER+3*number+2] = 0x6F;   // id ID_R_FSR
        BulkReadTxPacket[PARAMETER+3*number+3] = 0x1A;   // start address P_FSR1_L
        number++;
    }
    
    for(int id = 1; id < 20; id++){ //NUMBER OF JOINTS = 20
       
       BulkReadTxPacket[PARAMETER+3*number+1] = 23;  // length
       BulkReadTxPacket[PARAMETER+3*number+2] = id; // id
       BulkReadTxPacket[PARAMETER+3*number+3] = 26;  // start at CCW_COMPLIANCE_MARGIN
       number++;
        
    }

    BulkReadTxPacket[LENGTH]          = (number * 3) + 3;  

    length = BulkReadTxPacket[LENGTH] + 4;

    BulkReadTxPacket[length - 1] = CalculateChecksum(BulkReadTxPacket);


    int result = read(port, BulkReadTxPacket, rxpacket);

    printf("result: %d\n", result);

    int word = MakeWord((int)rxpacket[PARAMETER], (int)rxpacket[PARAMETER + 1]);
    printf("Motor position: %d\n\n", word);


    printf("Press the ENTER key to close port!\n");
    getchar();

    port->ClosePort();
      
}
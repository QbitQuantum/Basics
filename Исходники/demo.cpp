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
    usleep(2000);

    printf("Finshed dxl power up. Press enter\n");
    getchar();

    Init_to_Pose(port);
    getchar();   
  
    unsigned char packet[100] = {0, };
    usleep(2000);
    unsigned char dip_params[3] = {DGAIN, IGAIN, PGAIN};
    MakePacket(packet, 0x05, 3, 0x03, 0x1A, dip_params);
    port->ClearPort();
    port->WritePort(packet, 10);
    usleep(2000);

    int gainread = 0;
    gainread = ReadWord(port, 0x05, 0x1B);
    int iread = GetLowByte(gainread);
    int pread = GetHighByte(gainread);
    printf("i gain: %d\n", iread);
    printf("p gain: %d\n", pread);

if(EYES){
    int color = MakeColor(230, 0, 230);
    
    // LED packet
    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = 0xC8;
    packet[3] = 0x05;
    packet[4] = 0x03;
    packet[5] = 0x1A;
    packet[6] = GetLowByte(color);
    packet[7] = GetHighByte(color);
    packet[8] = CalculateChecksum(packet); 

    port->ClearPort();
    port->WritePort(packet, 9);
    usleep(2000);
   
    packet[5] = 0x1C;
    packet[8] = CalculateChecksum(packet);
    port->ClearPort();
    port->WritePort(packet, 9);
    usleep(2000);

    getchar();

    // 0x01C for eye LEDs, 0x1A for head LED
    unsigned char txpacket[] = {0xFF, 0xFF, 0xC8, 0x05, 0x03, 0x1C, 0xE0, 0x03, 0};
    txpacket[8] = CalculateChecksum(txpacket);
    printf("%d \n", txpacket[8]);

    int value = port->WritePort(txpacket, 9);


    printf("press enter\n");
    getchar();

    double r[total] = {0, };
    double g[total] = {0, };
    double b[total] = {0, };

    int count;

    for(count = 0; count < total; count++){
        r[count] = 255*sin(6.28*count/(total/2));
        g[count] = 255*sin(6.28*count/(total/11));
        b[count] = 255*sin(6.28*count/(total/21));
    }

    count = 0;
    int newcolor;

    while(count < total){
        port->ClearPort();
        newcolor = MakeColor(r[count], g[count], b[count]);
        txpacket[6] = GetLowByte(newcolor);
        txpacket[7] = GetHighByte(newcolor);
        txpacket[8] = 0;
        txpacket[8] = CalculateChecksum(txpacket);
        port->WritePort(txpacket, 9);
        usleep(10000);
        count++;
    } 
}

    //do we want a time out???
    //port->SetPacketTimeout(length) 

if(READ){

    unsigned char jointID = 0x1;
    int word;

  for(jointID = 1; jointID < 21; jointID++){
    word = ReadWord(port, jointID, 0x24);
    printf("Motor %d: %X - %X \n", jointID, GetHighByte(word), GetLowByte(word));
}
    if(word == -9999999){
        printf("bad read, terminating program.\n");
        port->ClosePort();
        return 0;
    }
 //   printf("Read angle as: %d, press enter to write new angle", word);


    // add some amount to the angle that was read in
    // split into low and high bytes
    //   word += 100;
    //   int value_low = GetLowByte(word);
    //   int value_high = GetHighByte(word);

    // now write position

    // txpacket_write = {0xFF, 0xFF, joint_id, 5, INST_WRITE, start address, value low, value high, checksum};
    // 			 {header, header, id, length = 5, INST_WRITE = 3, ...}
    // want start_address to be MX28::P_GOAL_POSITION_L
  
  //  unsigned char txpacket_write[] = {0xFF, 0xFF, 0x05, 0x05, 0x03, 0x1E, GetLowByte(word), GetHighByte(word), 0};
  //  int txlength = txpacket_write[LENGTH] + 4;
    
  //  txpacket_write[8] = CalculateChecksum(txpacket_write);
   
 //   port->ClearPort();
 //   port->WritePort(txpacket_write, 9);
 //   usleep(2000);

}

if(WRITE){
    int angle = 0;
    while(1){

        packet[2] = 0x05;
        packet[3] = 0x05;
        packet[5] = 0x1E;
        packet[6] = 0xD0;
        packet[7] = 0x07;
        packet[8] = CalculateChecksum(packet);
        port->ClearPort();
        port->WritePort(packet, 9);
        usleep(2000);

        sleep(2);

        angle = ReadWord(port, 0x5, 0x24);
        printf("Angle is: %d", angle);
        if(getchar() == 'a')
	    break;

        packet[7] = 0x09;
        packet[8] = CalculateChecksum(packet);
        port->ClearPort();
        port->WritePort(packet, 9);
        usleep(2000);

	sleep(2);

        angle = ReadWord(port, 0x05, 0x24);
        printf("Angle is: %d", angle);
        if(getchar() == 'a')
	    break;
    }

}

if(REGWRITE){

    unsigned char regpack[] = {0xFF, 0xFF, 0x05, 0x04, 0x04, 0x19, 0x01, 0x00};
    regpack[7] = CalculateChecksum(regpack);

    unsigned char action[] = {0xFF, 0xFF, 0x05, 0x02, 0x05, 0};
    action[5] = CalculateChecksum(action);

    port->ClearPort();
    port->WritePort(regpack, 8);
    usleep(2000);
   
    getchar();

    port->ClearPort();
    port->WritePort(action, 6);
    usleep(2000);
}

    printf("Press the ENTER key to close port!\n");
    getchar();

    port->ClosePort();

}
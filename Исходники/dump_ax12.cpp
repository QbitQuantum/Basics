void dump(Usb2Dynamixel controller, byte_t id_to_dump) {

    if(verboseFlag) std::cout << "Dump AX-12 #" << (int) id_to_dump << std::endl;
    else fprintf(stdout, "AX-12 #%02d | ", (int) id_to_dump);

    for(byte_t address_to_read = 0x00 ; (int) address_to_read < 0x32 ; address_to_read++) {
        byte_t param1 = address_to_read;
        byte_t param2 = 0x01;
        controller.send(ax12::ReadData(id_to_dump, param1, param2));

        Status status;
        controller.recv(0.5f, status);

        if(verboseFlag) fprintf(stdout, "%#04x %#04x\n", (int) address_to_read, (int) status.get_params()[0]);
        else fprintf(stdout, "%02x ", (int) status.get_params()[0]);
        
        usleep(1000); // Suspend execution for n microseconds
    }

}
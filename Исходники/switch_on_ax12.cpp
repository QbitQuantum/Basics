void switch_on(Usb2Dynamixel controller, byte_t id_to_switch_on) {

    Status status;

    controller.send(ax12::WriteData(id_to_switch_on, 0x18, 0x01));
    controller.recv(0.5f, status); usleep(1000);
    std::cout << "AX-12 #" << (int) id_to_switch_on << " : torque enabled" << std::endl;

}
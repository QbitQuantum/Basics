void send_serial_hex_USB( uint8_t value) {
    send_serial_USB('0');
    send_serial_USB('x');
    send_serial_USB(toASCII(value >> 4));
    send_serial_USB(toASCII(value & 0x0f));
}
static uint8_t mx_data_poll(uint8_t val) {
    // 200us * 5 => 1ms
    uint8_t max_try = 200;
    uint8_t data = 0;
    TRISA = 0xFF;

    while ((max_try--)>0) {
        CSL; 
        __nop();
        data = PORTA;
        CSH;

        if ((val & 0x80) == (data & 0x80)) {
            TRISA = 0x00;
            return 0;
        }
        __nop();
        __nop();
        __nop();
        __nop();
        __nop();
        __nop();
        __nop();
        __nop();
    }

    //error ...
    return 0xFF;
}
int8_t RotaryEncoder::readEncoder() {
    int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
    static uint8_t prev_state = 0;

    prev_state <<= 2;
    prev_state |= (readPort() & 0x03);

    uint8_t index = prev_state & 0x0f;
    return enc_states[index];
}
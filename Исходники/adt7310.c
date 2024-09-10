int16_t adt7310_read_raw(adt7310_t *dev)
{
    int status;
    int16_t raw;

    /* Read the temperature value register */
    status = adt7310_read_reg(dev, ADT7310_REG_VALUE, ADT7310_REG_SIZE_VALUE, (uint8_t*)&raw);
    if (status < 0) {
        /* communication error */
        return INT16_MIN;
    }
    /* The temperature value is sent big endian (network byte order) */
    raw = (int16_t)NTOHS((uint16_t)raw);
    return raw;
}
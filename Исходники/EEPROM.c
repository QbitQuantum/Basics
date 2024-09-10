uint8_t eeprom_write_byte(uint8_t *index, uint8_t val) {
  if (((uint32_t)index) >= sizeof(flash_backing))
    return 1;

  if (flash_state == STATE_EMPTY)
    memcpy(flash_backing, (const void *)&flash_area, sizeof(flash_backing));

  flash_backing[(uint32_t)index] = val;
  flash_state = STATE_DIRTY;

  setTimer(&my_timer, MS2ST(30), eeprom_flush, NULL);

  return 0;
}
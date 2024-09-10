int
ipmi_device_type_modifer_message (uint8_t device_type,
                                  uint8_t device_modifier,
                                  char *buf,
                                  unsigned int buflen)
{
  if (!IPMI_DEVICE_TYPE_VALID (device_type)
      || !buf
      || !buflen)
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  switch (device_type)
    {
    case IPMI_DEVICE_TYPE_DS1624_TEMPERATURE_SENSOR_EEPROM_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_ds1624_temperature_sensor_eeprom_or_equivalent_max_index,
                            ipmi_device_type_modifier_ds1624_temperature_sensor_eeprom_or_equivalent));
    case IPMI_DEVICE_TYPE_DS1621_TEMPERATURE_SENSOR_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_ds1621_temperature_sensor_eeprom_or_equivalent_max_index,
                            ipmi_device_type_modifier_ds1621_temperature_sensor_eeprom_or_equivalent));
    case IPMI_DEVICE_TYPE_LM75_TEMPERATURE_SENSOR_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_lm75_temperature_sensor_eeprom_or_equivalent_max_index,
                            ipmi_device_type_modifier_lm75_temperature_sensor_eeprom_or_equivalent));
    case IPMI_DEVICE_TYPE_HECETA_ASIC_OR_SIMILAR:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_heceta_asic_or_similar_max_index,
                            ipmi_device_type_modifier_heceta_asic_or_similar));
    case IPMI_DEVICE_TYPE_EEPROM_24C01_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_eeprom_24c01_or_equivalent_max_index,
                            ipmi_device_type_modifier_eeprom_24c01_or_equivalent));
    case IPMI_DEVICE_TYPE_EEPROM_24C02_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_eeprom_24c02_or_equivalent_max_index,
                            ipmi_device_type_modifier_eeprom_24c02_or_equivalent));
    case IPMI_DEVICE_TYPE_EEPROM_24C04_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_eeprom_24c04_or_equivalent_max_index,
                            ipmi_device_type_modifier_eeprom_24c04_or_equivalent));
    case IPMI_DEVICE_TYPE_EEPROM_24C08_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_eeprom_24c08_or_equivalent_max_index,
                            ipmi_device_type_modifier_eeprom_24c08_or_equivalent));
    case IPMI_DEVICE_TYPE_EEPROM_24C16_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_eeprom_24c16_or_equivalent_max_index,
                            ipmi_device_type_modifier_eeprom_24c16_or_equivalent));
    case IPMI_DEVICE_TYPE_EEPROM_24C17_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_eeprom_24c17_or_equivalent_max_index,
                            ipmi_device_type_modifier_eeprom_24c17_or_equivalent));
    case IPMI_DEVICE_TYPE_EEPROM_24C32_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_eeprom_24c32_or_equivalent_max_index,
                            ipmi_device_type_modifier_eeprom_24c32_or_equivalent));
    case IPMI_DEVICE_TYPE_EEPROM_24C64_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_eeprom_24c64_or_equivalent_max_index,
                            ipmi_device_type_modifier_eeprom_24c64_or_equivalent));
    case IPMI_DEVICE_TYPE_FRU_INVENTORY_DEVICE_BEHIND_MANAGEMENT_CONTROLLER:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_fru_inventory_device_behind_management_controller_max_index,
                            ipmi_device_type_modifier_fru_inventory_device_behind_management_controller));
    case IPMI_DEVICE_TYPE_PCF_8570_256_BYTE_RAM_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_pcf_8570_256_byte_ram_or_equivalent_max_index,
                            ipmi_device_type_modifier_pcf_8570_256_byte_ram_or_equivalent));
    case IPMI_DEVICE_TYPE_PCF_8573_CLOCK_CALENDAR_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_pcf_8573_clock_calendar_or_equivalent_max_index,
                            ipmi_device_type_modifier_pcf_8573_clock_calendar_or_equivalent));
    case IPMI_DEVICE_TYPE_PCF_8574A_IO_PORT_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_pcf_8574a_io_port_or_equivalent_max_index,
                            ipmi_device_type_modifier_pcf_8574a_io_port_or_equivalent));
    case IPMI_DEVICE_TYPE_PCF_8583_CLOCK_CALENDAR_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_pcf_8583_clock_calendar_or_equivalent_max_index,
                            ipmi_device_type_modifier_pcf_8583_clock_calendar_or_equivalent));
    case IPMI_DEVICE_TYPE_PCF_8593_CLOCK_CALENDAR_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_pcf_8593_clock_calendar_or_equivalent_max_index,
                            ipmi_device_type_modifier_pcf_8593_clock_calendar_or_equivalent));
    case IPMI_DEVICE_TYPE_CLOCK_CALENDAR_TYPE_NOT_SPECIFIED:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_clock_calendar_type_not_specified_max_index,
                            ipmi_device_type_modifier_clock_calendar_type_not_specified));
    case IPMI_DEVICE_TYPE_PCF_8591_AD_DA_CONVERTER_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_pcf_8591_ad_da_converter_or_equivalent_max_index,
                            ipmi_device_type_modifier_pcf_8591_ad_da_converter_or_equivalent));
    case IPMI_DEVICE_TYPE_IO_PORT_SPECIFIC_DEVICE_NOT_SPECIFIED:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_io_port_specific_device_not_specified_max_index,
                            ipmi_device_type_modifier_io_port_specific_device_not_specified));
    case IPMI_DEVICE_TYPE_AD_CONVERTER_SPECIFIC_DEVICE_NOT_SPECIFIED:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_ad_converter_specific_device_not_specified_max_index,
                            ipmi_device_type_modifier_ad_converter_specific_device_not_specified));
    case IPMI_DEVICE_TYPE_DA_CONVERTER_SPECIFIC_DEVICE_NOT_SPECIFIED:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_da_converter_specific_device_not_specified_max_index,
                            ipmi_device_type_modifier_da_converter_specific_device_not_specified));
    case IPMI_DEVICE_TYPE_AD_DA_CONVERTER_SPECIFIC_DEVICE_NOT_SPECIFIED:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_ad_da_converter_specific_device_not_specified_max_index,
                            ipmi_device_type_modifier_ad_da_converter_specific_device_not_specified));
    case IPMI_DEVICE_TYPE_LCD_CONTROLLER_DRIVER_SPECIFIC_DEVICE_NOT_SPECIFIED:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_lcd_controller_driver_specific_device_not_specified_max_index,
                            ipmi_device_type_modifier_lcd_controller_driver_specific_device_not_specified));
    case IPMI_DEVICE_TYPE_CORE_LOGIC_DEVICE_SPECIFIC_DEVICE_NOT_SPECIFIED:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_core_logic_device_specific_device_not_specified_max_index,
                            ipmi_device_type_modifier_core_logic_device_specific_device_not_specified));
    case IPMI_DEVICE_TYPE_LMC6874_INTELLIGENT_BATTERY_CONTROLLER_OR_EQUIVALENT:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_lmc6874_intelligent_battery_controller_or_equivalent_max_index,
                            ipmi_device_type_modifier_lmc6874_intelligent_battery_controller_or_equivalent));
    case IPMI_DEVICE_TYPE_INTELLIGENT_BATTERY_CONTROLLER_SPECIFIC_DEVICE_NOT_SPECIFIED:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_intelligent_battery_controller_specific_device_not_specified_max_index,
                            ipmi_device_type_modifier_intelligent_battery_controller_specific_device_not_specified));
    case IPMI_DEVICE_TYPE_COMBO_MANAGEMENT_ASIC_SPECIFIC_DEVICE_NOT_SPECIFIED:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_combo_management_asic_specific_device_not_specified_max_index,
                            ipmi_device_type_modifier_combo_management_asic_specific_device_not_specified));
    case IPMI_DEVICE_TYPE_MAXIM_1617_TEMPERATURE_SENSOR:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_maxim_1617_temperature_sensor_max_index,
                            ipmi_device_type_modifier_maxim_1617_temperature_sensor));
    case IPMI_DEVICE_TYPE_OTHER_UNSPECIFIED_DEVICE:
      return (_get_message (device_modifier,
                            buf,
                            buflen,
                            ipmi_device_type_modifier_other_unspecified_device_max_index,
                            ipmi_device_type_modifier_other_unspecified_device));
    }

  SET_ERRNO (EINVAL);
  return (-1);
}
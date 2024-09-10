zigbus::ZigbusSubType zigbus::convertStrToSubType(const QString &str) {
    if(str.toUpper() == "DHT11") return zigbus::stype_DHT11;
    else if(str.toUpper() == "LM35DZ") return zigbus::stype_LM35DZ;
    else return zigbus::stype_UNDEF;
}
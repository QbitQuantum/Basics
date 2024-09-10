void CustomConfig::setLongProperty(const char* propertyName, long propertyValue) {
    StringBuffer s;
    s.sprintf("%ld", propertyValue);
    extraProps.put(propertyName, s.c_str());
}
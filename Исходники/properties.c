long double
getProperty_LongDouble(const char *key, const long double defaultVal)
{
    char *val = (char *) HashMap_get(_sdf_globalPropertiesMap, key);
    return ((val) ? strtold(val, NULL) : defaultVal);
}
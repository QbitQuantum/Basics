int32_t
PropertyNames::getPropertyValueEnum(int32_t property, const char *name) const {
    return u_getPropertyValueEnum((UProperty)property, name);
}
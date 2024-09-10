String CIMObjectPath::_toStringCanonical() const
{
    CIMObjectPath ref;
    *ref._rep = *this->_rep;

    // Normalize hostname by changing to lower case
    ref._rep->_host.toLower(); // ICU_TODO:

    // Normalize namespace by changing to lower case
    if (!ref._rep->_nameSpace.isNull())
    {
        String nameSpaceLower = ref._rep->_nameSpace.getString();
        nameSpaceLower.toLower(); // ICU_TODO:
        ref._rep->_nameSpace = nameSpaceLower;
    }

    // Normalize class name by changing to lower case
    if (!ref._rep->_className.isNull())
    {
        String classNameLower = ref._rep->_className.getString();
        classNameLower.toLower(); // ICU_TODO:
        ref._rep->_className = classNameLower;
    }

    for (Uint32 i = 0, n = ref._rep->_keyBindings.size(); i < n; i++)
    {
        // Normalize key binding name by changing to lower case
        if (!ref._rep->_keyBindings[i]._rep->_name.isNull())
        {
            String keyBindingNameLower =
                ref._rep->_keyBindings[i]._rep->_name.getString();
            keyBindingNameLower.toLower(); // ICU_TODO:
            ref._rep->_keyBindings[i]._rep->_name = keyBindingNameLower;
        }

        // Normalize the key value
        switch (ref._rep->_keyBindings[i]._rep->_type)
        {
        case CIMKeyBinding::REFERENCE:
            try
            {
                // Convert reference to CIMObjectPath and recurse
                ref._rep->_keyBindings[i]._rep->_value =
                    CIMObjectPath(ref._rep->_keyBindings[i]._rep->_value).
                        _toStringCanonical();
            }
            catch (Exception&)
            {
                // Leave value unchanged if the CIMObjectPath parsing fails
            }
            break;
        case CIMKeyBinding::BOOLEAN:
            // Normalize the boolean string by changing to lower case
            ref._rep->_keyBindings[i]._rep->_value.toLower(); // ICU_TODO:
            break;
        case CIMKeyBinding::NUMERIC:
            // Normalize the numeric string by converting to integer and back
            Uint64 uValue;
            Sint64 sValue;
            // First try converting to unsigned integer
            if (StringConversion::stringToUnsignedInteger(
                    ref._rep->_keyBindings[i]._rep->_value.getCString(),
                        uValue))
            {
                char buffer[32];  // Should need 21 chars max
                sprintf(buffer, "%" PEGASUS_64BIT_CONVERSION_WIDTH "u", uValue);
                ref._rep->_keyBindings[i]._rep->_value = String(buffer);
            }
            // Next try converting to signed integer
            else if (StringConversion::stringToSignedInteger(
                         ref._rep->_keyBindings[i]._rep->_value.getCString(),
                             sValue))
            {
                char buffer[32];  // Should need 21 chars max
                sprintf(buffer, "%" PEGASUS_64BIT_CONVERSION_WIDTH "d", sValue);
                ref._rep->_keyBindings[i]._rep->_value = String(buffer);
            }
            // Leave value unchanged if it cannot be converted to an integer
            break;
        default:  // CIMKeyBinding::STRING
            // No normalization required for STRING
            break;
        }
    }

    // Note: key bindings are sorted when set in the CIMObjectPath

    return ref.toString();
}
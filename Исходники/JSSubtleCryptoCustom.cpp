static bool cryptoKeyUsagesFromJSValue(ExecState* exec, JSValue value, CryptoKeyUsage& result)
{
    if (!isJSArray(value)) {
        throwTypeError(exec);
        return false;
    }

    result = 0;

    JSArray* array = asArray(value);
    for (size_t i = 0; i < array->length(); ++i) {
        JSValue element = array->getIndex(exec, i);
        String usageString = element.toString(exec)->value(exec);
        if (exec->hadException())
            return false;
        if (usageString == "encrypt")
            result |= CryptoKeyUsageEncrypt;
        else if (usageString == "decrypt")
            result |= CryptoKeyUsageDecrypt;
        else if (usageString == "sign")
            result |= CryptoKeyUsageSign;
        else if (usageString == "verify")
            result |= CryptoKeyUsageVerify;
        else if (usageString == "deriveKey")
            result |= CryptoKeyUsageDeriveKey;
        else if (usageString == "deriveBits")
            result |= CryptoKeyUsageDeriveBits;
        else if (usageString == "wrapKey")
            result |= CryptoKeyUsageWrapKey;
        else if (usageString == "unwrapKey")
            result |= CryptoKeyUsageUnwrapKey;
    }
    return true;
}
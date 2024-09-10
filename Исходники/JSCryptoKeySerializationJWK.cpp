void JSCryptoKeySerializationJWK::reconcileUsages(CryptoKeyUsage& suggestedUsages) const
{
    CryptoKeyUsage jwkUsages = 0;

    JSArray* keyOps;
    if (getJSArrayFromJSON(m_exec, m_json.get(), "key_ops", keyOps)) {
        for (size_t i = 0; i < keyOps->length(); ++i) {
            JSValue jsValue = keyOps->getIndex(m_exec, i);
            String operation;
            if (!jsValue.getString(m_exec, operation)) {
                if (!m_exec->hadException())
                    throwTypeError(m_exec, "JWK key_ops attribute could not be processed");
                return;
            }
            if (!tryJWKKeyOpsValue(m_exec, jwkUsages, operation, ASCIILiteral("sign"), CryptoKeyUsageSign))
                return;
            if (!tryJWKKeyOpsValue(m_exec, jwkUsages, operation, ASCIILiteral("verify"), CryptoKeyUsageVerify))
                return;
            if (!tryJWKKeyOpsValue(m_exec, jwkUsages, operation, ASCIILiteral("encrypt"), CryptoKeyUsageEncrypt))
                return;
            if (!tryJWKKeyOpsValue(m_exec, jwkUsages, operation, ASCIILiteral("decrypt"), CryptoKeyUsageDecrypt))
                return;
            if (!tryJWKKeyOpsValue(m_exec, jwkUsages, operation, ASCIILiteral("wrapKey"), CryptoKeyUsageWrapKey))
                return;
            if (!tryJWKKeyOpsValue(m_exec, jwkUsages, operation, ASCIILiteral("unwrapKey"), CryptoKeyUsageUnwrapKey))
                return;
            if (!tryJWKKeyOpsValue(m_exec, jwkUsages, operation, ASCIILiteral("deriveKey"), CryptoKeyUsageDeriveKey))
                return;
            if (!tryJWKKeyOpsValue(m_exec, jwkUsages, operation, ASCIILiteral("deriveBits"), CryptoKeyUsageDeriveBits))
                return;
        }
    } else {
        if (m_exec->hadException())
            return;

        String jwkUseString;
        if (!getStringFromJSON(m_exec, m_json.get(), "use", jwkUseString)) {
            // We have neither key_ops nor use.
            return;
        }

        if (jwkUseString == "enc")
            jwkUsages |= (CryptoKeyUsageEncrypt | CryptoKeyUsageDecrypt | CryptoKeyUsageWrapKey | CryptoKeyUsageUnwrapKey);
        else if (jwkUseString == "sig")
            jwkUsages |= (CryptoKeyUsageSign | CryptoKeyUsageVerify);
        else {
            throwTypeError(m_exec, "Unsupported JWK key use value \"" + jwkUseString + "\"");
            return;
        }
    }

    suggestedUsages = suggestedUsages & jwkUsages;
}
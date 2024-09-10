bool PaymentRequestValidator::validateCurrencyCode(const String& currencyCode) const
{
    if (!currencyCode) {
        m_window.printErrorMessage("Missing currency code.");
        return false;
    }

    UErrorCode errorCode = U_ZERO_ERROR;
    auto currencyCodes = std::unique_ptr<UEnumeration, void (*)(UEnumeration*)>(ucurr_openISOCurrencies(UCURR_ALL, &errorCode), uenum_close);

    int32_t length;
    while (auto *currencyCodePtr = uenum_next(currencyCodes.get(), &length, &errorCode)) {
        if (currencyCodePtr == currencyCode)
            return true;
    }

    auto message = makeString("\"" + currencyCode, "\" is not a valid currency code.");
    m_window.printErrorMessage(message);

    return false;
}
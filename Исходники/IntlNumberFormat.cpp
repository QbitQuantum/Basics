void IntlNumberFormat::initializeNumberFormat(ExecState& state, JSValue locales, JSValue optionsValue)
{
    VM& vm = state.vm();
    auto scope = DECLARE_THROW_SCOPE(vm);

    // 11.1.2 InitializeNumberFormat (numberFormat, locales, options) (ECMA-402)
    // https://tc39.github.io/ecma402/#sec-initializenumberformat

    auto requestedLocales = canonicalizeLocaleList(state, locales);
    RETURN_IF_EXCEPTION(scope, void());

    JSObject* options;
    if (optionsValue.isUndefined())
        options = constructEmptyObject(&state, state.lexicalGlobalObject()->nullPrototypeObjectStructure());
    else {
        options = optionsValue.toObject(&state);
        RETURN_IF_EXCEPTION(scope, void());
    }

    HashMap<String, String> opt;

    String matcher = intlStringOption(state, options, vm.propertyNames->localeMatcher, { "lookup", "best fit" }, "localeMatcher must be either \"lookup\" or \"best fit\"", "best fit");
    RETURN_IF_EXCEPTION(scope, void());
    opt.add("localeMatcher"_s, matcher);

    auto& availableLocales = state.jsCallee()->globalObject(vm)->intlNumberFormatAvailableLocales();
    auto result = resolveLocale(state, availableLocales, requestedLocales, opt, relevantNumberExtensionKeys, WTF_ARRAY_LENGTH(relevantNumberExtensionKeys), IntlNFInternal::localeData);

    m_locale = result.get("locale"_s);
    if (m_locale.isEmpty()) {
        throwTypeError(&state, scope, "failed to initialize NumberFormat due to invalid locale"_s);
        return;
    }

    m_numberingSystem = result.get("nu"_s);

    String styleString = intlStringOption(state, options, Identifier::fromString(&vm, "style"), { "decimal", "percent", "currency" }, "style must be either \"decimal\", \"percent\", or \"currency\"", "decimal");
    RETURN_IF_EXCEPTION(scope, void());
    if (styleString == "decimal")
        m_style = Style::Decimal;
    else if (styleString == "percent")
        m_style = Style::Percent;
    else if (styleString == "currency")
        m_style = Style::Currency;
    else
        ASSERT_NOT_REACHED();

    String currency = intlStringOption(state, options, Identifier::fromString(&vm, "currency"), { }, nullptr, nullptr);
    RETURN_IF_EXCEPTION(scope, void());
    if (!currency.isNull()) {
        if (currency.length() != 3 || !currency.isAllSpecialCharacters<isASCIIAlpha>()) {
            throwException(&state, scope, createRangeError(&state, "currency is not a well-formed currency code"_s));
            return;
        }
    }

    unsigned currencyDigits = 0;
    if (m_style == Style::Currency) {
        if (currency.isNull()) {
            throwTypeError(&state, scope, "currency must be a string"_s);
            return;
        }

        currency = currency.convertToASCIIUppercase();
        m_currency = currency;
        currencyDigits = computeCurrencyDigits(currency);
    }

    String currencyDisplayString = intlStringOption(state, options, Identifier::fromString(&vm, "currencyDisplay"), { "code", "symbol", "name" }, "currencyDisplay must be either \"code\", \"symbol\", or \"name\"", "symbol");
    RETURN_IF_EXCEPTION(scope, void());
    if (m_style == Style::Currency) {
        if (currencyDisplayString == "code")
            m_currencyDisplay = CurrencyDisplay::Code;
        else if (currencyDisplayString == "symbol")
            m_currencyDisplay = CurrencyDisplay::Symbol;
        else if (currencyDisplayString == "name")
            m_currencyDisplay = CurrencyDisplay::Name;
        else
            ASSERT_NOT_REACHED();
    }

    unsigned minimumIntegerDigits = intlNumberOption(state, options, Identifier::fromString(&vm, "minimumIntegerDigits"), 1, 21, 1);
    RETURN_IF_EXCEPTION(scope, void());
    m_minimumIntegerDigits = minimumIntegerDigits;

    unsigned minimumFractionDigitsDefault = (m_style == Style::Currency) ? currencyDigits : 0;

    unsigned minimumFractionDigits = intlNumberOption(state, options, Identifier::fromString(&vm, "minimumFractionDigits"), 0, 20, minimumFractionDigitsDefault);
    RETURN_IF_EXCEPTION(scope, void());
    m_minimumFractionDigits = minimumFractionDigits;

    unsigned maximumFractionDigitsDefault;
    if (m_style == Style::Currency)
        maximumFractionDigitsDefault = std::max(minimumFractionDigits, currencyDigits);
    else if (m_style == Style::Percent)
        maximumFractionDigitsDefault = minimumFractionDigits;
    else
        maximumFractionDigitsDefault = std::max(minimumFractionDigits, 3u);

    unsigned maximumFractionDigits = intlNumberOption(state, options, Identifier::fromString(&vm, "maximumFractionDigits"), minimumFractionDigits, 20, maximumFractionDigitsDefault);
    RETURN_IF_EXCEPTION(scope, void());
    m_maximumFractionDigits = maximumFractionDigits;

    JSValue minimumSignificantDigitsValue = options->get(&state, Identifier::fromString(&vm, "minimumSignificantDigits"));
    RETURN_IF_EXCEPTION(scope, void());

    JSValue maximumSignificantDigitsValue = options->get(&state, Identifier::fromString(&vm, "maximumSignificantDigits"));
    RETURN_IF_EXCEPTION(scope, void());

    if (!minimumSignificantDigitsValue.isUndefined() || !maximumSignificantDigitsValue.isUndefined()) {
        unsigned minimumSignificantDigits = intlDefaultNumberOption(state, minimumSignificantDigitsValue, Identifier::fromString(&vm, "minimumSignificantDigits"), 1, 21, 1);
        RETURN_IF_EXCEPTION(scope, void());
        unsigned maximumSignificantDigits = intlDefaultNumberOption(state, maximumSignificantDigitsValue, Identifier::fromString(&vm, "maximumSignificantDigits"), minimumSignificantDigits, 21, 21);
        RETURN_IF_EXCEPTION(scope, void());
        m_minimumSignificantDigits = minimumSignificantDigits;
        m_maximumSignificantDigits = maximumSignificantDigits;
    }

    bool usesFallback;
    bool useGrouping = intlBooleanOption(state, options, Identifier::fromString(&vm, "useGrouping"), usesFallback);
    if (usesFallback)
        useGrouping = true;
    RETURN_IF_EXCEPTION(scope, void());
    m_useGrouping = useGrouping;

    UNumberFormatStyle style = UNUM_DEFAULT;
    switch (m_style) {
    case Style::Decimal:
        style = UNUM_DECIMAL;
        break;
    case Style::Percent:
        style = UNUM_PERCENT;
        break;
    case Style::Currency:
        switch (m_currencyDisplay) {
        case CurrencyDisplay::Code:
            style = UNUM_CURRENCY_ISO;
            break;
        case CurrencyDisplay::Symbol:
            style = UNUM_CURRENCY;
            break;
        case CurrencyDisplay::Name:
            style = UNUM_CURRENCY_PLURAL;
            break;
        default:
            ASSERT_NOT_REACHED();
        }
        break;
    default:
        ASSERT_NOT_REACHED();
    }

    UErrorCode status = U_ZERO_ERROR;
    m_numberFormat = std::unique_ptr<UNumberFormat, UNumberFormatDeleter>(unum_open(style, nullptr, 0, m_locale.utf8().data(), nullptr, &status));
    if (U_FAILURE(status)) {
        throwTypeError(&state, scope, "failed to initialize NumberFormat"_s);
        return;
    }

    if (m_style == Style::Currency) {
        unum_setTextAttribute(m_numberFormat.get(), UNUM_CURRENCY_CODE, StringView(m_currency).upconvertedCharacters(), m_currency.length(), &status);
        if (U_FAILURE(status)) {
            throwTypeError(&state, scope, "failed to initialize NumberFormat"_s);
            return;
        }
    }
    if (!m_minimumSignificantDigits) {
        unum_setAttribute(m_numberFormat.get(), UNUM_MIN_INTEGER_DIGITS, m_minimumIntegerDigits);
        unum_setAttribute(m_numberFormat.get(), UNUM_MIN_FRACTION_DIGITS, m_minimumFractionDigits);
        unum_setAttribute(m_numberFormat.get(), UNUM_MAX_FRACTION_DIGITS, m_maximumFractionDigits);
    } else {
        unum_setAttribute(m_numberFormat.get(), UNUM_SIGNIFICANT_DIGITS_USED, true);
        unum_setAttribute(m_numberFormat.get(), UNUM_MIN_SIGNIFICANT_DIGITS, m_minimumSignificantDigits);
        unum_setAttribute(m_numberFormat.get(), UNUM_MAX_SIGNIFICANT_DIGITS, m_maximumSignificantDigits);
    }
    unum_setAttribute(m_numberFormat.get(), UNUM_GROUPING_USED, m_useGrouping);
    unum_setAttribute(m_numberFormat.get(), UNUM_ROUNDING_MODE, UNUM_ROUND_HALFUP);

    m_initializedNumberFormat = true;
}
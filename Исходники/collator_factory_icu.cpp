StatusWith<std::unique_ptr<CollatorInterface>> CollatorFactoryICU::makeFromBSON(
    const BSONObj& spec) {
    // Parse the locale ID out of the spec.
    auto parsedLocaleID = parseLocaleID(spec);
    if (!parsedLocaleID.isOK()) {
        return parsedLocaleID.getStatus();
    }

    // If spec = {locale: "simple"}, return a null pointer. A null CollatorInterface indicates
    // simple binary compare.
    if (parsedLocaleID.getValue() == CollationSpec::kSimpleBinaryComparison) {
        if (spec.nFields() > 1) {
            return {ErrorCodes::FailedToParse,
                    str::stream() << "If locale=default, no other fields should be present in: "
                                  << spec};
        }
        return {nullptr};
    }

    // Check that the locale ID is recognizable by ICU.
    if (!isValidLocale(parsedLocaleID.getValue())) {
        return {ErrorCodes::BadValue,
                str::stream() << "Field '" << CollationSpec::kLocaleField
                              << "' is not a valid ICU locale in: " << spec};
    }

    // Construct an icu::Locale.
    auto locale = icu::Locale::createFromName(parsedLocaleID.getValue().c_str());

    // Construct an icu::Collator.
    UErrorCode status = U_ZERO_ERROR;
    std::unique_ptr<icu::Collator> icuCollator(icu::Collator::createInstance(locale, status));
    if (U_FAILURE(status)) {
        icu::ErrorCode icuError;
        icuError.set(status);
        return {ErrorCodes::OperationFailed,
                str::stream() << "Failed to create collator: " << icuError.errorName()
                              << ". Collation spec: " << spec};
    }

    // Construct a CollationSpec using the options provided in spec or the defaults in icuCollator.
    // Use locale.getName() for the localeID, since it is canonicalized and includes options.
    auto parsedSpec = parseToCollationSpec(spec, locale.getName(), icuCollator.get());
    if (!parsedSpec.isOK()) {
        return parsedSpec.getStatus();
    }

    auto mongoCollator = stdx::make_unique<CollatorInterfaceICU>(std::move(parsedSpec.getValue()),
                                                                 std::move(icuCollator));
    return {std::move(mongoCollator)};
}
JSObject* IntlPluralRules::resolvedOptions(ExecState& exec)
{
    VM& vm = exec.vm();
    auto scope = DECLARE_THROW_SCOPE(vm);

    // 13.4.4 Intl.PluralRules.prototype.resolvedOptions ()
    // https://tc39.github.io/ecma402/#sec-intl.pluralrules.prototype.resolvedoptions
    if (UNLIKELY(!m_initializedPluralRules)) {
        throwTypeError(&exec, scope, "Intl.PluralRules.prototype.resolvedOptions called on value that's not an object initialized as a PluralRules"_s);
        return nullptr;
    }

    JSObject* options = constructEmptyObject(&exec);
    options->putDirect(vm, vm.propertyNames->locale, jsNontrivialString(&exec, m_locale));
    options->putDirect(vm, Identifier::fromString(&vm, "type"), jsNontrivialString(&exec, m_type == UPLURAL_TYPE_ORDINAL ? "ordinal"_s : "cardinal"_s));
    options->putDirect(vm, Identifier::fromString(&vm, "minimumIntegerDigits"), jsNumber(m_minimumIntegerDigits));
    options->putDirect(vm, Identifier::fromString(&vm, "minimumFractionDigits"), jsNumber(m_minimumFractionDigits));
    options->putDirect(vm, Identifier::fromString(&vm, "maximumFractionDigits"), jsNumber(m_maximumFractionDigits));
    if (m_minimumSignificantDigits) {
        options->putDirect(vm, Identifier::fromString(&vm, "minimumSignificantDigits"), jsNumber(m_minimumSignificantDigits.value()));
        options->putDirect(vm, Identifier::fromString(&vm, "maximumSignificantDigits"), jsNumber(m_maximumSignificantDigits.value()));
    }

#if HAVE(ICU_PLURALRULES_KEYWORDS)
    JSGlobalObject* globalObject = exec.jsCallee()->globalObject(vm);
    JSArray* categories = JSArray::tryCreate(vm, globalObject->arrayStructureForIndexingTypeDuringAllocation(ArrayWithContiguous), 0);
    if (UNLIKELY(!categories)) {
        throwOutOfMemoryError(&exec, scope);
        return nullptr;
    }

    UErrorCode status = U_ZERO_ERROR;
    auto keywords = std::unique_ptr<UEnumeration, UEnumerationDeleter>(uplrules_getKeywords(m_pluralRules.get(), &status));
    ASSERT(U_SUCCESS(status));
    int32_t resultLength;

    // Category names are always ASCII, so use char[].
    unsigned index = 0;
    while (const char* result = uenum_next(keywords.get(), &resultLength, &status)) {
        ASSERT(U_SUCCESS(status));
        categories->putDirectIndex(&exec, index++, jsNontrivialString(&exec, String(result, resultLength)));
        RETURN_IF_EXCEPTION(scope, { });
    }
    options->putDirect(vm, Identifier::fromString(&vm, "pluralCategories"), categories);
#endif

    RELEASE_AND_RETURN(scope, options);
}
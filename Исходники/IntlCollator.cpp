void IntlCollator::createCollator(ExecState& state)
{
    VM& vm = state.vm();
    auto scope = DECLARE_CATCH_SCOPE(vm);
    ASSERT(!m_collator);

    if (!m_initializedCollator) {
        initializeCollator(state, jsUndefined(), jsUndefined());
        ASSERT_UNUSED(scope, !scope.exception());
    }

    UErrorCode status = U_ZERO_ERROR;
    auto collator = std::unique_ptr<UCollator, UCollatorDeleter>(ucol_open(m_locale.utf8().data(), &status));
    if (U_FAILURE(status))
        return;

    UColAttributeValue strength = UCOL_PRIMARY;
    UColAttributeValue caseLevel = UCOL_OFF;
    switch (m_sensitivity) {
    case Sensitivity::Base:
        break;
    case Sensitivity::Accent:
        strength = UCOL_SECONDARY;
        break;
    case Sensitivity::Case:
        caseLevel = UCOL_ON;
        break;
    case Sensitivity::Variant:
        strength = UCOL_TERTIARY;
        break;
    default:
        ASSERT_NOT_REACHED();
    }
    ucol_setAttribute(collator.get(), UCOL_STRENGTH, strength, &status);
    ucol_setAttribute(collator.get(), UCOL_CASE_LEVEL, caseLevel, &status);

    ucol_setAttribute(collator.get(), UCOL_NUMERIC_COLLATION, m_numeric ? UCOL_ON : UCOL_OFF, &status);

    // FIXME: Setting UCOL_ALTERNATE_HANDLING to UCOL_SHIFTED causes punctuation and whitespace to be
    // ignored. There is currently no way to ignore only punctuation.
    ucol_setAttribute(collator.get(), UCOL_ALTERNATE_HANDLING, m_ignorePunctuation ? UCOL_SHIFTED : UCOL_DEFAULT, &status);

    // "The method is required to return 0 when comparing Strings that are considered canonically
    // equivalent by the Unicode standard."
    ucol_setAttribute(collator.get(), UCOL_NORMALIZATION_MODE, UCOL_ON, &status);
    if (U_FAILURE(status))
        return;

    m_collator = WTFMove(collator);
}
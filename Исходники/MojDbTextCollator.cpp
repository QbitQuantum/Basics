MojErr MojDbTextCollator::init(const MojChar* locale, MojDbCollationStrength level)
{
    LOG_TRACE("Entering function %s", __FUNCTION__);
	MojAssert(locale);
	MojAssert(!m_ucol);

	UCollationStrength strength = UCOL_PRIMARY;
	switch (level) {
	case MojDbCollationPrimary:
		strength = UCOL_PRIMARY;
		break;
	case MojDbCollationSecondary:
		strength = UCOL_SECONDARY;
		break;
	case MojDbCollationTertiary:
		strength = UCOL_TERTIARY;
		break;
    case MojDbCollationQuaternary:
        strength = UCOL_QUATERNARY;
        break;
	case MojDbCollationIdentical:
		strength = UCOL_IDENTICAL;
		break;
	default:
		MojAssertNotReached();
	}

	UErrorCode status = U_ZERO_ERROR;
	m_ucol = ucol_open(locale, &status);
	MojUnicodeErrCheck(status);
	MojAssert(m_ucol);
	ucol_setAttribute(m_ucol, UCOL_NORMALIZATION_MODE, UCOL_ON, &status);
    if (level == MojDbCollationIdentical) {
        // Combination of IDENTICAL and NUMERIC option cover full-width comparison and ["001","01","1"] ordering.
        // NUMERIC option converts number charcter to numeric "a021" -> ["a",21]
        ucol_setAttribute(m_ucol, UCOL_NUMERIC_COLLATION, UCOL_ON, &status);
    }
	MojUnicodeErrCheck(status);
	ucol_setStrength(m_ucol, strength);

	return MojErrNone;
}
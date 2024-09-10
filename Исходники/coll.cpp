UCollator* 
Collator::createUCollator(const char *loc,
                          UErrorCode *status)
{
    UCollator *result = 0;
    if (status && U_SUCCESS(*status) && hasService()) {
        Locale desiredLocale(loc);
        Collator *col = (Collator*)gService->get(desiredLocale, *status);
        if (col && col->getDynamicClassID() == RuleBasedCollator::getStaticClassID()) {
            RuleBasedCollator *rbc = (RuleBasedCollator *)col;
            if (!rbc->dataIsOwned) {
                result = ucol_safeClone(rbc->ucollator, NULL, NULL, status);
            } else {
                result = rbc->ucollator;
                rbc->ucollator = NULL; // to prevent free on delete
            }
        }
        delete col;
    }
    return result;
}
NFSubstitution::NFSubstitution(int32_t _pos,
                               const NFRuleSet* _ruleSet,
                               const RuleBasedNumberFormat* formatter,
                               const UnicodeString& description,
                               UErrorCode& status)
                               : pos(_pos), ruleSet(NULL), numberFormat(NULL)
{
    // the description should begin and end with the same character.
    // If it doesn't that's a syntax error.  Otherwise,
    // makeSubstitution() was the only thing that needed to know
    // about these characters, so strip them off
    UnicodeString workingDescription(description);
    if (description.length() >= 2
        && description.charAt(0) == description.charAt(description.length() - 1))
    {
        workingDescription.remove(description.length() - 1, 1);
        workingDescription.remove(0, 1);
    }
    else if (description.length() != 0) {
        // throw new IllegalArgumentException("Illegal substitution syntax");
        status = U_PARSE_ERROR;
        return;
    }

    // if the description was just two paired token characters
    // (i.e., "<<" or ">>"), it uses the rule set it belongs to to
    // format its result
    if (workingDescription.length() == 0) {
        this->ruleSet = _ruleSet;
    }
    // if the description contains a rule set name, that's the rule
    // set we use to format the result: get a reference to the
    // names rule set
    else if (workingDescription.charAt(0) == gPercent) {
        this->ruleSet = formatter->findRuleSet(workingDescription, status);
    }
    // if the description begins with 0 or #, treat it as a
    // DecimalFormat pattern, and initialize a DecimalFormat with
    // that pattern (then set it to use the DecimalFormatSymbols
    // belonging to our formatter)
    else if (workingDescription.charAt(0) == gPound || workingDescription.charAt(0) ==gZero) {
        DecimalFormatSymbols* sym = formatter->getDecimalFormatSymbols();
        if (!sym) {
            status = U_MISSING_RESOURCE_ERROR;
            return;
        }
        this->numberFormat = new DecimalFormat(workingDescription, *sym, status);
        /* test for NULL */
        if (this->numberFormat == 0) {
            status = U_MEMORY_ALLOCATION_ERROR;
            return;
        }
        if (U_FAILURE(status)) {
            delete (DecimalFormat*)this->numberFormat;
            this->numberFormat = NULL;
            return;
        }
        // this->numberFormat->setDecimalFormatSymbols(formatter->getDecimalFormatSymbols());
    }
    // if the description is ">>>", this substitution bypasses the
    // usual rule-search process and always uses the rule that precedes
    // it in its own rule set's rule list (this is used for place-value
    // notations: formats where you want to see a particular part of
    // a number even when it's 0)
    else if (workingDescription.charAt(0) == gGreaterThan) {
        // this causes problems when >>> is used in a frationalPartSubstitution
        // this->ruleSet = NULL;
        this->ruleSet = _ruleSet;
        this->numberFormat = NULL;
    }
    // and of the description is none of these things, it's a syntax error
    else {
        // throw new IllegalArgumentException("Illegal substitution syntax");
        status = U_PARSE_ERROR;
    }
}
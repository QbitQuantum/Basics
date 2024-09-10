UBool
NFRuleSet::parse(const UnicodeString& text, ParsePosition& pos, double upperBound, Formattable& result) const
{
    // try matching each rule in the rule set against the text being
    // parsed.  Whichever one matches the most characters is the one
    // that determines the value we return.

    result.setLong(0);

    // dump out if there's no text to parse
    if (text.length() == 0) {
        return 0;
    }

    ParsePosition highWaterMark;
    ParsePosition workingPos = pos;

#ifdef RBNF_DEBUG
    fprintf(stderr, "<nfrs> %x '", this);
    dumpUS(stderr, name);
    fprintf(stderr, "' text '");
    dumpUS(stderr, text);
    fprintf(stderr, "'\n");
    fprintf(stderr, "  parse negative: %d\n", this, negativeNumberRule != 0);
#endif
    // Try each of the negative rules, fraction rules, infinity rules and NaN rules
    for (int i = 0; i < NON_NUMERICAL_RULE_LENGTH; i++) {
        if (nonNumericalRules[i]) {
            Formattable tempResult;
            UBool success = nonNumericalRules[i]->doParse(text, workingPos, 0, upperBound, tempResult);
            if (success && (workingPos.getIndex() > highWaterMark.getIndex())) {
                result = tempResult;
                highWaterMark = workingPos;
            }
            workingPos = pos;
        }
    }
#ifdef RBNF_DEBUG
    fprintf(stderr, "<nfrs> continue other with text '");
    dumpUS(stderr, text);
    fprintf(stderr, "' hwm: %d\n", highWaterMark.getIndex());
#endif

    // finally, go through the regular rules one at a time.  We start
    // at the end of the list because we want to try matching the most
    // sigificant rule first (this helps ensure that we parse
    // "five thousand three hundred six" as
    // "(five thousand) (three hundred) (six)" rather than
    // "((five thousand three) hundred) (six)").  Skip rules whose
    // base values are higher than the upper bound (again, this helps
    // limit ambiguity by making sure the rules that match a rule's
    // are less significant than the rule containing the substitutions)/
    {
        int64_t ub = util64_fromDouble(upperBound);
#ifdef RBNF_DEBUG
        {
            char ubstr[64];
            util64_toa(ub, ubstr, 64);
            char ubstrhex[64];
            util64_toa(ub, ubstrhex, 64, 16);
            fprintf(stderr, "ub: %g, i64: %s (%s)\n", upperBound, ubstr, ubstrhex);
        }
#endif
        for (int32_t i = rules.size(); --i >= 0 && highWaterMark.getIndex() < text.length();) {
            if ((!fIsFractionRuleSet) && (rules[i]->getBaseValue() >= ub)) {
                continue;
            }
            Formattable tempResult;
            UBool success = rules[i]->doParse(text, workingPos, fIsFractionRuleSet, upperBound, tempResult);
            if (success && workingPos.getIndex() > highWaterMark.getIndex()) {
                result = tempResult;
                highWaterMark = workingPos;
            }
            workingPos = pos;
        }
    }
#ifdef RBNF_DEBUG
    fprintf(stderr, "<nfrs> exit\n");
#endif
    // finally, update the parse postion we were passed to point to the
    // first character we didn't use, and return the result that
    // corresponds to that string of characters
    pos = highWaterMark;

    return 1;
}
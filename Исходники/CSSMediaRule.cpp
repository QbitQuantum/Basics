unsigned CSSMediaRule::insertRule(const String& rule, unsigned index, ExceptionCode& ec)
{
    if (index > m_lstCSSRules->length()) {
        // INDEX_SIZE_ERR: Raised if the specified index is not a valid insertion point.
        ec = INDEX_SIZE_ERR;
        return 0;
    }

    CSSParser p(useStrictParsing());
    RefPtr<CSSRule> newRule = p.parseRule(parentStyleSheet(), rule);
    if (!newRule) {
        // SYNTAX_ERR: Raised if the specified rule has a syntax error and is unparsable.
        ec = SYNTAX_ERR;
        return 0;
    }

    if (newRule->isImportRule()) {
        // FIXME: an HIERARCHY_REQUEST_ERR should also be thrown for a @charset or a nested
        // @media rule.  They are currently not getting parsed, resulting in a SYNTAX_ERR
        // to get raised above.

        // HIERARCHY_REQUEST_ERR: Raised if the rule cannot be inserted at the specified
        // index, e.g., if an @import rule is inserted after a standard rule set or other
        // at-rule.
        ec = HIERARCHY_REQUEST_ERR;
        return 0;
    }

    newRule->setParent(this);
    unsigned returnedIndex = m_lstCSSRules->insertRule(newRule.get(), index);

    // stylesheet() can only return 0 for computed style declarations.
    stylesheet()->styleSheetChanged();

    return returnedIndex;
}
void TextSearcherICU::setCaseSensitivity(bool caseSensitive) {
  const UCollationStrength strength =
      caseSensitive ? UCOL_TERTIARY : UCOL_PRIMARY;

  UCollator* const collator = usearch_getCollator(m_searcher);
  if (ucol_getStrength(collator) == strength)
    return;

  ucol_setStrength(collator, strength);
  usearch_reset(m_searcher);
}
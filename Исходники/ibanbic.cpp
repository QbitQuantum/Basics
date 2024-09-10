QString ibanBic::ibanToElectronic(const QString& iban)
{
  QString canonicalIban;
  const int length = iban.length();
  for (int i = 0; i < length; ++i) {
    const QChar letter = iban.at(i);
    if (letter.isLetterOrNumber())
      canonicalIban.append(letter.toUpper());
  }

  return canonicalIban;
}
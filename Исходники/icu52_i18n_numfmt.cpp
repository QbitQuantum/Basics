UnicodeString&
NumberFormat::format(const Formattable& obj,
                        UnicodeString& appendTo,
                        FieldPositionIterator* posIter,
                        UErrorCode& status) const
{
    if (U_FAILURE(status)) return appendTo;

    ArgExtractor arg(*this, obj, status);
    const Formattable *n = arg.number();
    const UChar *iso = arg.iso();

    if(arg.wasCurrency() && u_strcmp(iso, getCurrency())) {
      // trying to format a different currency.
      // Right now, we clone.
      LocalPointer<NumberFormat> cloneFmt((NumberFormat*)this->clone());
      cloneFmt->setCurrency(iso, status);
      // next line should NOT recurse, because n is numeric whereas obj was a wrapper around currency amount.
      return cloneFmt->format(*n, appendTo, posIter, status);
    }

    if (n->isNumeric() && n->getDigitList() != NULL) {
        // Decimal Number
        format(*n->getDigitList(), appendTo, posIter, status);
    } else {
        switch (n->getType()) {
        case Formattable::kDouble:
            format(n->getDouble(), appendTo, posIter, status);
            break;
        case Formattable::kLong:
            format(n->getLong(), appendTo, posIter, status);
            break;
        case Formattable::kInt64:
            format(n->getInt64(), appendTo, posIter, status);
            break;
        default:
            status = U_INVALID_FORMAT_ERROR;
            break;
        }
    }

    return appendTo;
}
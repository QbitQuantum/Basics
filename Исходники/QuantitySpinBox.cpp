void QuantitySpinBox::fixup(QString &input) const
{
    input.remove(locale().groupSeparator());
}
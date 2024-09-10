void testTypingValue(
    SpinBoxType* sbox, QPushButton *okButton, const QString &value)
{
    sbox->selectAll();
    for (int i = 0; i < value.size(); ++i) {
        const QChar valChar = value[i];
	_keyClick(static_cast<QWidget *>(sbox), valChar.toAscii()); // ### always guaranteed to work?
        if (sbox->hasAcceptableInput())
            QVERIFY(okButton->isEnabled());
        else
            QVERIFY(!okButton->isEnabled());
    }
}
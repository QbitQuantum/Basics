void EditPrimerDialog::sl_onPrimerChanged(const QString &primerSequence) {
    int curPos = primerEdit->cursorPosition();
    primerEdit->setText(primerSequence.toUpper());
    primerEdit->setCursorPosition(curPos);
}
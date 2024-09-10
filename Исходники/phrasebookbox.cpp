void PhraseBookBox::enableDisable()
{
    QModelIndex index = currentPhraseIndex();

    sourceLed->blockSignals(true);
    targetLed->blockSignals(true);
    definitionLed->blockSignals(true);

    bool indexValid = index.isValid();

    if (indexValid) {
        Phrase *p = phrMdl->phrase(index);
        sourceLed->setText(p->source().simplified());
        targetLed->setText(p->target().simplified());
        definitionLed->setText(p->definition());
    }
    else {
        sourceLed->setText(QString());
        targetLed->setText(QString());
        definitionLed->setText(QString());
    }

    sourceLed->setEnabled(indexValid);
    targetLed->setEnabled(indexValid);
    definitionLed->setEnabled(indexValid);
    removeBut->setEnabled(indexValid);

    sourceLed->blockSignals(false);
    targetLed->blockSignals(false);
    definitionLed->blockSignals(false);

    QWidget *f = QApplication::focusWidget();
    if (f != sourceLed && f != targetLed && f != definitionLed) {
        QLineEdit *led = (sourceLed->text() == NewPhrase ? sourceLed : targetLed);
        led->setFocus();
        led->selectAll();
    } else {
        static_cast<QLineEdit*>(f)->selectAll();
    }
}
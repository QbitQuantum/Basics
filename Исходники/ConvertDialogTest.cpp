void ConvertDialogTest::convert_addText_no()
{
    EffectsScrollArea *effectsScrollArea = convertDialog->effectsScrollArea;
    QGroupBox *textGroupBox = effectsScrollArea->textGroupBox;
    textGroupBox->setChecked(false);

    convertDialog->convert();

    SharedInformation *sharedInfo = convertDialog->sharedInfo;
    EffectsConfiguration conf = sharedInfo->effectsConfiguration();
    QCOMPARE(conf.getTextString(), QString());
    QCOMPARE(conf.getTextFont(), QFont());
    QCOMPARE(conf.getTextColor(), QColor());
    QCOMPARE(conf.getTextPosModifier(), UndefinedPosModifier);
    QCOMPARE(conf.getTextPos(), QPoint());
    QCOMPARE(conf.getTextUnitPair(), PosUnitPair(UndefinedUnit, UndefinedUnit));
    QCOMPARE(conf.getTextFrame(), false);
    QCOMPARE(conf.getTextRotation(), 0);
}
void CCardSearchParameters::fetchFromUi(const Ui::CardSearchWidget &ui)
{
    mName = ui.nameBox->currentText().trimmed();
    mLwCsName = mName.toLower();
    mSkill = ui.skillBox->currentText().split("+", QString::SkipEmptyParts);
    mLwCsSkill.clear();
    for (QStringList::const_iterator i = mSkill.begin(); i != mSkill.end(); ++i)
    {
        mLwCsSkill.push_back(i->toLower().trimmed());
    }

    mRarityMask = 0;
    mRarityMask |= ui.legendaryButton->isChecked() ? 0x1 : 0;
    mRarityMask |= ui.rareButton->isChecked() ? 0x2 : 0;
    mRarityMask |= ui.uncommonButton->isChecked() ? 0x4 : 0;
    mRarityMask |= ui.commonButton->isChecked() ? 0x8 : 0;

    mTypeMask = 0;
    mTypeMask |= ui.assaultButton->isChecked() ? 0x1 : 0;
    mTypeMask |= ui.structureButton->isChecked() ? 0x2 : 0;
    mTypeMask |= ui.commanderButton->isChecked() ? 0x4 : 0;
    mTypeMask |= ui.actionButton->isChecked() ? 0x8 : 0;

    mFactionMask = 0;
    mFactionMask |= ui.bloodthirstyButton->isChecked() ? 0x1 : 0;
    mFactionMask |= ui.imperialButton->isChecked() ? 0x2 : 0;
    mFactionMask |= ui.raiderButton->isChecked() ? 0x4 : 0;
    mFactionMask |= ui.righteousButton->isChecked() ? 0x8 : 0;
    mFactionMask |= ui.xenoButton->isChecked() ? 0x10 : 0;

    mTimerMask = 0;
    mTimerMask |= ui.timer0Button->isChecked() ? 0x1 : 0;
    mTimerMask |= ui.timer1Button->isChecked() ? 0x2 : 0;
    mTimerMask |= ui.timer2Button->isChecked() ? 0x4 : 0;
    mTimerMask |= ui.timer3Button->isChecked() ? 0x8 : 0;
    mTimerMask |= ui.timer4Button->isChecked() ? 0x10 : 0;

    switch(ui.attackStackedWidget->currentIndex())
    {
    case 1: mAttackCompare = ECompareEqual; break;
    case 2: mAttackCompare = ECompareEqualOrLesser; break;
    default: mAttackCompare = ECompareEqualOrLarger; break;
    }
    switch(ui.hpStackedWidget->currentIndex())
    {
    case 1: mHpCompare = ECompareEqual; break;
    case 2: mHpCompare = ECompareEqualOrLesser; break;
    default: mHpCompare = ECompareEqualOrLarger; break;
    }

    mAttackValue = ui.attackSlider->value();
    mHpValue = ui.hpSlider->value();

    mCheckUpgradeLevel = true;
    switch(ui.upgradeStackedWidget->currentIndex())
    {
    case 1: mUpgradeLevel = 0; break;
    case 2: mUpgradeLevel = 1; break;
    case 3: mUpgradeLevel = 2; break;
    default: mUpgradeLevel = 0xff; mCheckUpgradeLevel = false; break;
    }
    mIsUnique = ui.uniqueButton->isChecked();
}
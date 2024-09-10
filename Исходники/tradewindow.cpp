void TradeWindow::reset()
{
    mMyInventory->clear();
    mPartnerInventory->clear();
    mOkOther = false;
    mOkMe = false;
    setMoney(0);
    mMoneyField->setEnabled(true);
    mMoneyField->setText("");
    mMoneyLabel->setForegroundColorAll(getThemeColor(
        static_cast<int>(Theme::LABEL)), getThemeColor(
        static_cast<int>(Theme::LABEL_OUTLINE)));
    mAddButton->setEnabled(true);
    mMoneyChangeButton->setEnabled(true);
    mGotMoney = 0;
    mGotMaxMoney = 0;
    setStatus(PREPARING);
}
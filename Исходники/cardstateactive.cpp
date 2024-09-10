CardStateActive::~CardStateActive()
{
    getParent()->setStyleSheet(CardStateActive::RESET);
}
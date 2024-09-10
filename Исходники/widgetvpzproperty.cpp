void
WidgetVpzPropertyObservables::refresh()
{

    bool oldBlock = QComboBox::blockSignals(true);
    QComboBox::clear();
    QString dyn = mVpz->modelDynFromDoc(mModQuery);
    QDomNodeList obss = mVpz->obssListFromObss(mVpz->obsFromDoc());
    QComboBox::addItem("<none>");
    int selectIndex = 0;
    for (int i = 0; i < obss.length(); i++) {
        QDomNode obs = obss.at(i);
        QString obsName = DomFunctions::attributeValue(obs, "name");
        QComboBox::addItem(obsName);
        if (mVpz->modelObsFromDoc(mModQuery) == obsName) {
            selectIndex = i + 1;
        }
    }
    QComboBox::setCurrentIndex(selectIndex);
    QComboBox::blockSignals(oldBlock);
}
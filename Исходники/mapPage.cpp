QList<double> MapPage::evalGetHistoryDists() const {
    QVariant result = this->mainFrame()->evaluateJavaScript("curRoute.getHistoryDists();");
    QVariantList vpath = result.toList();

    QList<double> historyDists;
    for (int i=0; i<vpath.length(); i++) {
        historyDists.push_back(vpath[i].toDouble());
    }
    return historyDists;
}
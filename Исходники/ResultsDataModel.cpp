int ResultsDataModel::childCount(const QVariantList &indexPath) {
    int retVal = 0;
    if (indexPath.length() == 0) {
        retVal = _internalDB.length();
    } else {
        //No map in list has children; each just represents a song or album
        retVal = 0;
    }
    return retVal;
}
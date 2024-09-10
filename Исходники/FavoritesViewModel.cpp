/**
 * This slot is connected to the dataChanged signal of the FavoritesService and is executed
 * when the data in the service is changed. When the data is changed, we delete
 * all the data in the DataModel and insert the new data.
 *
 * @param favorites The data to be inserted in the datamodel.
 */
void FavoritesViewModel::favoritesDataChanged(const QVariantList &favorites) {
    // clear the data.
    this->dataModel->clear();

    // repopulate the datamodel
    for(int i=0; i<favorites.length(); i++) {
        this->dataModel->insert(favorites[i].toMap());
    }

    emit dataModelChanged(dataModel);
}
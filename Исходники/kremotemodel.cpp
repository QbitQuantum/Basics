void KRemoteModel::gotData(QVariantList data) {
	if(st_ == Fetching) {
		emit beginInsertRows(QModelIndex(), 0, data.length() - 1);
		this->data_ = data;
		emit endInsertRows();

		setState(Complete);
	}
}
QVariant FileItemModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}
	if (role != Qt::DisplayRole) {
		return QVariant();
	}

	StaticFile* file = static_cast<StaticFile*>(index.internalPointer());

	switch (index.column()) {
	case 0:
		return QVariant(file->toString().get());
		break;
	case 1:
		File realFile = file->getFile();

		if (realFile.isDirectory()) {
			return tr("Directory");
		} else {
			EntityOpenRequest req;
			req.setAttribute("type", "file");
			req.setAttribute("file", QString(realFile.getPath().toString().get()));
			EntityHandler* handler = EntityManager::getInstance()->getEntityHandler(req);

			if (handler) {
				return handler->getFileFormatName(realFile);
			} else {
				return tr("Unrecognized File");
			}
		}
	}

	return QVariant();
}
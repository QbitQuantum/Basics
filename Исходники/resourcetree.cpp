void ResourceTree::insertItemsFromArchive(Archive &archive, const ResourceTreeItem &item,
                                          const QModelIndex &parentIndex) {
	QList<ResourceTreeItem *> items;

	if (item.getFileType() == Aurora::kFileTypeBIF) {
		const QString localArchivePath = item.getParent()->getName() + "/" + item.getName();
		auto resList = static_cast<Aurora::KEYFile *>(archive.data)->getResourceListForDataFile(localArchivePath.toStdString().c_str());
		for (auto res : resList) {
			items.push_back(new ResourceTreeItem(archive.data, localArchivePath, *res));
		}
	} else {
		auto &resources = archive.data->getResources();
		for (auto r = resources.begin(); r != resources.end(); ++r) {
			items.push_back(new ResourceTreeItem(archive.data, item.getPath(), *r));
		}
	}
	archive.addedMembers = true;

	insertItems(0, items, parentIndex);
}
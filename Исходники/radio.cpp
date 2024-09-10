void
Radio_Impl::setGroup(const QString& group)
{
	QString groupName;
	QWidget *window = this->window();
	
	fGroup = group;
	if (window)
		groupName = QString("[%1]/%2").arg(window->objectName()).arg(group);
	else
		groupName = QString("[]/%1").arg(group);
	
	if (fButtonGroup) {
		fButtonGroup->removeButton(this);
		if (fButtonGroup->buttons().size() == 0) {
			sButtonGroups.remove(fButtonGroup->objectName());
			delete fButtonGroup;
		}
	}
	
	fButtonGroup = sButtonGroups[groupName];
	if (!fButtonGroup) {
		fButtonGroup = new QButtonGroup();
		fButtonGroup->setObjectName(groupName);
		sButtonGroups[groupName] = fButtonGroup;
	}
	fButtonGroup->addButton(this);
}
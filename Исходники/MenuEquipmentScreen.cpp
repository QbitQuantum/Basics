void MenuEquipmentScreen::equippedItemSelected() {
	// Reset updated stats and equipment list
	_updatedStatsItem->setText(QString());
	for (int i = 0; i < _updatedStatsItems.size(); i++)
		delete _updatedStatsItems.at(i);
	_updatedStatsItems.clear();

	_equipmentList.clear();
	_equipmentStringList.clear();
	_currentSelectedEquipmentString = 0;
	_currentEquipmentListItem = 0;
	_equipmentListItem->setText(QString());
	for (int i = 0; i < _activeEquipmentListItems.size(); i++)
		delete _activeEquipmentListItems.at(i);
	_activeEquipmentListItems.clear();

	// Build the equipmentlist
	QVector<QPair<EquipmentPiece*, int>> equipment = _inventory->getEquipment();
	for (int i = 0; i < equipment.size();) {
		if (!equipmentFilter(equipment.at(i).first))
			equipment.remove(i);
		else {
			_equipmentList.append(equipment.at(i).first);
			i++;
		}
	}

	// Set the equipment list
	QFont font ("Times", 12, QFont::Bold);
	QBrush brush(Qt::white);
	QPointF position(_equipmentListItem->pos().x(), _equipmentListItem->pos().y() + 20);

	_currentSelectedEquipmentString = 0;
	_equipmentStringList.append(QString("Clear equipment slot"));
	for (int i = 0; i < _equipmentList.size(); i++)
		_equipmentStringList.append(_equipmentList.at(i)->getName());

	_equipmentListItem->setText("Select equipment:");
	for (int i = 0; i < qMin<int>(_equipmentStringList.size(), 8); i++) {
		QGraphicsSimpleTextItem *item = new QGraphicsSimpleTextItem(_equipmentListPanel);

		item->setBrush(brush);
		item->setFont(font);
		item->setText(_equipmentStringList.at(i));
		item->setPos(position);

		position.setY(position.y() + 20);
		_activeEquipmentListItems.append(item);
	}

	setCurrentEquipmentItem(_activeEquipmentListItems.first(), 0);
	_state = MenuEquipmentScreen::EQUIPMENT_SELECTION;
}
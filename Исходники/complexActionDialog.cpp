void ComplexActionDialog::addComplexActionToRuleWidget(QTreeWidgetItem *parent, ComplexUserAction *complexUserAction, QTreeWidgetItem *topLevelParent)
{
	QTreeWidgetItem *ruleItem = nullptr;
	if (parent == nullptr) {
		ruleItem = new QTreeWidgetItem(ui->ruleTreeWidget);
	} else {
		ruleItem = new QTreeWidgetItem(parent);
	}
	if (ruleItem) {
		QTreeWidgetItem *topLevelParentItem = new QTreeWidgetItem();
		if (topLevelParent == nullptr) {
			topLevelParentItem = ruleItem;
		}
		else {
			topLevelParentItem = topLevelParent;
		}
		int column = 0;
		ruleItem->setText(column, complexUserAction->userActionName());
		for (UserAction *userAction: complexUserAction->userActions()) {
			ComplexUserAction *complexAction = dynamic_cast<ComplexUserAction *>(userAction);
			if (complexAction) {
				addComplexActionToRuleWidget(ruleItem, complexAction, topLevelParentItem);
			}
			else {
				BaseUserAction *baseAction = dynamic_cast<BaseUserAction *>(userAction);
				if (baseAction) {
					addBaseActionToRuleWidget(ruleItem, baseAction->userActionName(),
											  baseAction->customActionProperties()
											  , baseAction->repeatCount()
											  , baseAction->isKeyAction()
											  , *(baseAction->duration())
											  , topLevelParentItem);
				}
				else if (reserveRuleItems.contains(userAction->userActionName())) {
					int blue = 100;
					if (userAction->userActionName() == QString::fromUtf8("или")) {
						blue = 255;
					}
					QTreeWidgetItem *redTapeInstructionItem = new QTreeWidgetItem(ruleItem);
					redTapeInstructionItem->setText(column, userAction->userActionName());
					redTapeInstructionItem->setTextColor(column, QColor(100, 100, blue));
				}
			}
		}
		mWidgetItemCustomPropertyList.append(new WidgetItemCustomProperty(topLevelParentItem
																		  , ruleItem
																		  , QMap<QString, QString>()
																		  , complexUserAction->repeatCount()
																		  , complexUserAction->isKeyAction()
																		  , *(complexUserAction->duration())));
		mDisabledProperties.insert(ruleItem, QMap<QString, QString>());
	}
}
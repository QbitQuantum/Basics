void param_search_widget::updateSelectedParameter()
{
    // Grab list of selected items in the displayParameterModel
    QList<QTreeWidgetItem *> selectedItems =
        displayParameterModel->selectedItems();

    // We will use only the first element
    if (selectedItems.size() > 0)
    {
        parameterNode* currentNode = static_cast<parameterNode*>
                                     (selectedItems.at(0));

        currentSearchParam_ = flattenPath(currentNode);

        // Only want to display last 2
        QString truncPath;

        if (parameterList_.contains(currentSearchParam_))
        {
            geoStatParam param = parameterList_[currentSearchParam_];
            ui->lineEditParam->setText(currentSearchParam_);

            QString dataTypeStr;

            switch(param.type)
            {
            case -1:
                dataTypeStr = QString("String");
                break;
            case 0:
                dataTypeStr = QString("Float");
                break;
            case 1:
                dataTypeStr = QString("Integer");
                break;
            case 2:
                dataTypeStr = QString("Double");
                break;
            case 3:
                dataTypeStr = QString("Unknown");
                break;
            default:
                dataTypeStr = QString("String");

            }

            ui->lineEditType->setText(dataTypeStr);

            QString castable = (param.type > 0) ?
                               (QString("True")) : (QString("False"));

            ui->lineEditCastable->setText(castable);
            ui->lineEditValue->setText(param.str);

            if (param.type > 0)
            {
                ui->lineEditSearchValue->setDisabled(false);
                ui->lineEditSearchValue->setText(param.str);
            }
            else
                ui->lineEditSearchValue->setDisabled(true);
        }
        else
        {
            ui->lineEditParam->setText(currentSearchParam_);
            ui->lineEditType->setText(QString("Category"));
            ui->lineEditCastable->setText("False");
            ui->lineEditValue->setText("N/A");
            ui->lineEditSearchValue->setDisabled(true);

        }
    }
}
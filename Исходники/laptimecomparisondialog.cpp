void LapTimeComparisonDialog::updateCharts()
{
    DriverData *driverData[4] = {0, 0, 0, 0};
    QString driver;
    for (int i = 0; i < 4; ++i)
    {
        int idx = eventData.getDriverId(getNumber(i));
        if (idx > 0)
        {
            driver = eventData.getDriversData()[idx-1].getDriverName();
            driverData[i] = &eventData.getDriversData()[idx-1];
//            carIdx = (eventData.getDriversData()[idx-1].getNumber() > 13 ?
//                             eventData.getDriversData()[idx-1].getNumber() - 2 :
//                             eventData.getDriversData()[idx-1].getNumber() - 1) / 2;

            QTableWidgetItem *item = ui->chartsTableWidget->item(0, i);
            item->setText(driver);
            item->setTextColor(ColorsManager::getInstance().getCarColor(driverData[i]->getNumber()));

//            if (carIdx >= 0)
            {
                QLabel *lab = qobject_cast<QLabel*>(ui->chartsTableWidget->cellWidget(1, i));
                if (!lab)
                {
                    lab = new QLabel();
                    lab->setAlignment(Qt::AlignCenter);
                    lab->setPixmap(ImagesFactory::getInstance().getCarThumbnailsFactory().getCarThumbnail(driverData[i]->getNumber(), thumbnailsSize));//eventData.carImages[carIdx].scaledToWidth(120, Qt::SmoothTransformation));
                    ui->chartsTableWidget->setCellWidget(1, i, lab);
                }
                else
                    lab->setPixmap(ImagesFactory::getInstance().getCarThumbnailsFactory().getCarThumbnail(driverData[i]->getNumber(), thumbnailsSize));//eventData.carImages[carIdx].scaledToWidth(120, Qt::SmoothTransformation));
            }
        }
        else
        {
            QTableWidgetItem *item = ui->chartsTableWidget->item(0, i);
            item->setText("");

            QLabel *lab = qobject_cast<QLabel*>(ui->chartsTableWidget->cellWidget(1, i));
            if (lab)
                lab->clear();
        }
    }
    lapCompChart->setData(driverData);
    lapCompChart->repaint();
}
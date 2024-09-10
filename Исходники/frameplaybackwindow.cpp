void FramePlaybackWindow::saveFilters()
{
    QString filename;
    QFileDialog dialog(this);

    QStringList filters;
    filters.append(QString(tr("Filter list (*.ftl)")));

    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilters(filters);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    if (dialog.exec() == QDialog::Accepted)
    {
        filename = dialog.selectedFiles()[0];
        if (!filename.contains('.')) filename += ".ftl";
        if (dialog.selectedNameFilter() == filters[0])
        {
            QFile *outFile = new QFile(filename);

            if (!outFile->open(QIODevice::WriteOnly | QIODevice::Text))
                return;

            for (int c = 0; c < ui->listID->count(); c++)
            {
                outFile->write(QString::number(ui->listID->item(c)->text().toInt(NULL, 16), 16).toUtf8());
                outFile->putChar(',');
                if (ui->listID->item(c)->checkState() == Qt::Checked) outFile->putChar('T');
                else outFile->putChar('F');
                outFile->write("\n");
            }

            outFile->close();
        }
    }

}
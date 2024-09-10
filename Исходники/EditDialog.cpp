// Update the information labels in the bottom left corner of the dialog
// and switches the editor mode, if required, according to the detected data type.
void EditDialog::updateCellInfoAndMode(const QByteArray& data)
{
    QByteArray cellData = data;

    switchEditorMode(ui->buttonAutoSwitchMode->isChecked());

    // Image data needs special treatment
    if (dataType == Image || dataType == SVG) {
        QBuffer imageBuffer(&cellData);
        QImageReader imageReader(&imageBuffer);

        // Display the image format
        QString imageFormat = imageReader.format();

        ui->labelType->setText(tr("Type of data currently in cell: %1 Image").arg(imageFormat.toUpper()));

        // Display the image dimensions and size
        QSize imageDimensions = imageReader.size();
        int imageSize = cellData.size();

        QString labelSizeText = tr("%1x%2 pixel(s)").arg(imageDimensions.width()).arg(imageDimensions.height()) + ", " + humanReadableSize(imageSize);

        ui->labelSize->setText(labelSizeText);

        return;
    }

    // Use a switch statement for the other data types to keep things neat :)
    switch (dataType) {
    case Null:
        // NULL data type
        ui->labelType->setText(tr("Type of data currently in cell: NULL"));
        ui->labelSize->setText(tr("%n byte(s)", "", 0));
        ui->editorText->setStyleSheet("QTextEdit{ font-style: italic; }");
        ui->editorText->setPlaceholderText(Settings::getValue("databrowser", "null_text").toString());
        break;

    case Text: {
        // Text only
        // Determine the length of the cell text in characters (possibly different to number of bytes).
        int textLength = QString(cellData).length();
        ui->labelType->setText(tr("Type of data currently in cell: Text / Numeric"));
        ui->labelSize->setText(tr("%n char(s)", "", textLength));
        break;
    }
    case JSON: {
        // Valid JSON
        // Determine the length of the cell text in characters (possibly different to number of bytes).
        int jsonLength = QString(cellData).length();
        ui->labelType->setText(tr("Type of data currently in cell: Valid JSON"));
        ui->labelSize->setText(tr("%n char(s)", "", jsonLength));
        break;
    }
    default:

        // Determine the length of the cell data
        int dataLength = cellData.length();
        // If none of the above data types, consider it general binary data
        ui->labelType->setText(tr("Type of data currently in cell: Binary"));
        ui->labelSize->setText(tr("%n byte(s)", "", dataLength));
        break;
    }
}
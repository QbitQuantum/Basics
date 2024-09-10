void CSVImportDialog::createCSVImportView(QString filenamein)
{
    QFile file(filenamein);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // read file
        ui->csvTextEdit->setText(file.readAll());
    }

    this->setWindowTitle("CSV Import - " + filenamein);

    QTextCursor cursor = ui->csvTextEdit->textCursor();
    QTextCharFormat format;

    cursor.select(QTextCursor::Document);
    format.setForeground( QBrush( QColor( "black" ) ) );
    format.setFontStrikeOut(false);
    cursor.setCharFormat( format );

    for(int i=0; i<ui->lineskipSpinBox->value(); i++){
        format.setForeground( QBrush( QColor( "red" ) ) );
        format.setFontStrikeOut(true);
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, i);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.setCharFormat( format );
    }

}
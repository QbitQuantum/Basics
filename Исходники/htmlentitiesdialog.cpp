void HtmlEntitiesDialog::editClicked() {
    if (editMode) {
        if (textEdit->document()->isModified()) {
            QString value = textEdit->toPlainText();
            QString fileName = global.fileManager.getHomeDirPath("") + QString("entities.txt");
            QDir dir;
            dir.remove(fileName);
            QFile file(fileName);
            file.open(QFile::WriteOnly);
            if (file.isOpen()) {
                QTextStream out(&file);
                out << value;
            }
            file.close();
        }
        clearEntitiesButtons();
        loadCustomEntities();
        initEntitiesButtons();

    } else {
        if (textEdit == NULL) {
            textEdit = new QTextEdit(tr("Comma separated list of HTML entities.\nSee http://www.w3schools.com/charsets/ for list."));
        }
        textEdit->setText(getEntities(true));
    }
    editMode = !editMode;
    scrollArea->takeWidget();
    scrollArea->setWidget(editMode ? textEdit : entitiesWidget);
    scrollArea->setWidgetResizable(editMode);
    editButton->setText(editMode ? saveString : editString);
    closeButton->setText(editMode ? cancelString : closeString);
}
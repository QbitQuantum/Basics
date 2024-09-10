void TranslatorView::openNormalTextFile()
{
    QString fileContent;
    fileContent = openFile();
    textEditNormalText->setPlainText(fileContent);
}
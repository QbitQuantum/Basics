void KisTemplateCreateDia::createTemplate(const QString &templatesResourcePath,
                                         const char *suffix,
                                         KisDocument *document, QWidget *parent)
{
    Q_UNUSED(suffix);
    QString fileName;
    {
        QTemporaryFile tempFile;
        if (!tempFile.open()) {
            qWarning("Creation of temporary file to store template failed.");
            return;
        }
        fileName = tempFile.fileName();
    }
    bool retval = document->exportDocument(QUrl::fromLocalFile(fileName));
    if (!retval) {
        qWarning("Could not save template");
        return;
    }
    const QPixmap thumbnail = document->generatePreview(QSize(thumbnailExtent, thumbnailExtent));
    KisTemplateCreateDia *dia = new KisTemplateCreateDia(templatesResourcePath, fileName, thumbnail, parent);
    dia->exec();
    delete dia;

    QDir d;
    d.remove(fileName);
}
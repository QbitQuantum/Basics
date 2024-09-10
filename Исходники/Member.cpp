Member::~Member()
{
    QFile file(a_file);
    file.remove();

    QString cheminPictures(a_filePictures);
    QFile filePictures (cheminPictures);
    filePictures.remove();
}
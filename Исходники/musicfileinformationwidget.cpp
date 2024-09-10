void MusicFileInformationWidget::saveModifyData()
{
    MusicSongTag tag;
    if(!tag.readFile(m_path))
    {
        return;
    }

    QString value = ui->fileAlbumEdit->text().trimmed();
    if(value != "-" && ui->fileAlbumEdit->getTextEdited()) tag.setAlbum(value);

    value = ui->fileArtistEdit->text().trimmed();
    if(value != "-" && ui->fileArtistEdit->getTextEdited()) tag.setArtist(value);

    value = ui->fileGenreEdit->text().trimmed();
    if(value != "-" && ui->fileGenreEdit->getTextEdited()) tag.setGenre(value);

    value = ui->fileTitleEdit->text().trimmed();
    if(value != "-" && ui->fileTitleEdit->getTextEdited()) tag.setTitle(value);

    value = ui->fileYearEdit->text().trimmed();
    if(value != "-" && ui->fileYearEdit->getTextEdited()) tag.setYear(value);
}
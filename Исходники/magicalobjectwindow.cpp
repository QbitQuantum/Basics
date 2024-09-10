void MagicalObjectWindow::on_removeButton_clicked()
{
    QItemSelectionModel *selection = ui->treeViewExistingObjects->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(indexElementSelectionne.isValid())
    {
        int rep = QMessageBox::question(this,tr("Effacer"),
                                        tr("Voulez-vous vraiment effacer cet object magique ?"),
                                        QMessageBox::Yes | QMessageBox::No);
        if (rep == QMessageBox::Yes)
        {
            QFile f;
            f.setFileName(MAGICAL_OBJECT_PATH + "/" + ui->comboRace->currentText() + "/" + objects->item(indexElementSelectionne.row(), 0)->text() + ".om");
            f.remove();
            updateTreeView(ui->comboRace->currentText());
        }
        else if (rep == QMessageBox::No)
        {
            QMessageBox::critical(this, tr("Annulation"), tr("Opération annulée"));
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Info"), tr("Veuillez sélectionner un régiment a supprimer."));
    }
}
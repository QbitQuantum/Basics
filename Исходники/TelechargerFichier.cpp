void TelechargerFichier::annulerTelechargement()
{
	QPushButton *bouton;
		bouton = qobject_cast<QPushButton *>(sender());
		bouton->setDisabled(true);

	QString toolTip = bouton->toolTip();
		toolTip = toolTip.replace(QRegExp("Téléchargement n°(.+)"), "\\1");

	int ligne = toolTip.toInt() - 1;

	QNetworkReply *reponse = reponses.value(ligne);
		reponse->abort();

	QProgressBar *progression = progressionsTelechargements.value(ligne);
		progression->setValue(progression->maximum());

	listeTelechargements->item(ligne, 3)->setText("Annulé");
}
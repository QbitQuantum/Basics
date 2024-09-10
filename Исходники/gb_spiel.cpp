void gesamtbild::zeitanzeige(/*int dora, int hin, int may*/)
{
			qWarning() << "Zeit";


			QDialog *zeitw = new QDialog(this);
			QVBoxLayout layout(zeitw);
			QLabel *anzeige = new QLabel(tr("Time: Day %1,").arg(GAMEDATA->gametime().day()).append(QString("%1 hours").arg(GAMEDATA->gametime().hour())), zeitw);

// 			anzeige->setText(anzeige->text().append(QString(", %2 Uhr %3").arg( gameview->stunde, gameview->minute)));gameview->stunde
// 			qWarning() << anzeige->text().append(QString(", %2 Uhr %3").arg( gameview->stunde, gameview->minute));

			QPushButton *ok = new QPushButton("Ok",zeitw);
			ok->move(50, 50);
			layout.addWidget(anzeige);
			layout.addWidget(ok);
// 			zeitw->setGeometry(width()/2,height()/2,200,100);
			zeitw->setLayout(&layout);
			zeitw->setAutoFillBackground(true);
			zeitw->move(gameview->width()/2,gameview->height()/2);
  			zeitw->raise();
			zeitw->show();

			connect(ok, SIGNAL(clicked()), gameview, SLOT(endePause()));
			connect(ok, SIGNAL(clicked()), zeitw, SLOT(close()));
			connect(ok, SIGNAL(clicked()), zeitw, SLOT(deleteLater()));
}
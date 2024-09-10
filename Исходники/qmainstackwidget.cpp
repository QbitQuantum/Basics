void qmainstackwidget::set_editsearch()
{
	edit_search = new QLineEdit(this);
	edit_search->setGeometry(0, 110, 283, 25);
	edit_search->setFont(QFont("Timers", 10, QFont::StyleOblique));
	edit_search->setStyleSheet("QLineEdit{border: 2px solid rgb(22, 154, 218);padding: 0 8px;background: rgb(21, 127, 178);selection-background-color: darkgray;color:rgb(240, 255, 255);}");
	QPushButton *search = new QPushButton(this);
	search->setFlat(true);
	QPixmap pix;
	pix.load("search.jpg");
	pix = pix.scaled(18, 18);
	QIcon icon_search(pix);
	search->setIcon(icon_search);
	search->setFixedSize(18, 18);
	search->move(edit_search->width() - search->width() - 2, (edit_search->height() - search->height()) / 2);
	search->setGeometry(263, 115, search->width(), search->height());
	search->setStyleSheet("QPushButton{ border-image:url(search.png); }"
		"QPushButton:press{border-image:url(search_press.png);}"
		"QPushButton:hover{border-image:url(search_hover.png);}");
	search->setCursor(QCursor(Qt::PointingHandCursor));
}
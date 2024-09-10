void TopLevel::setupMenuBar()
{
    file = new QPopupMenu();
    options = new QPopupMenu();

    file->insertItem(klocale->translate("E&xit"),
		     KApplication::getKApplication(), SLOT(quit()));

    options->setCheckable(TRUE);
    swallowID = options->insertItem(klocale->translate("&Swallow modules"),
                        this, SLOT(swallowChanged()));

    QPopupMenu *helpMenu = kapp->getHelpMenu(true, klocale->translate("KDE Control Center - "
					"Version 1.0\n\n"
					"Written by Matthias Hölzer\n"
					"([email protected])\n\n"
					"Thanks to:\n"
					"S. Kulow, P. Dowler, M. Wuebben & M. Jones."));

    menubar = new KMenuBar(this);
    menubar->insertItem(klocale->translate("&File"), file);
    menubar->insertItem(klocale->translate("&Options"), options);
    menubar->insertSeparator(-1);
    menubar->insertItem(klocale->translate("&Help"), helpMenu);

    setMenu(menubar);
}
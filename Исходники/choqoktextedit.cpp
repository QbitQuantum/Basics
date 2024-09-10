void TextEdit::slotAboutToShowContextMenu(QMenu* menu)
{
    if(menu){
        kDebug();
        KAction *act = new KAction(i18n("Set spell check language"), menu);
        act->setMenu(d->langActions);
        menu->addAction(act);

        KAction *shorten = new KAction(i18nc("Replace URLs by a shortened URL", "Shorten URLs"), menu);
        connect(shorten, SIGNAL(triggered(bool)), SLOT(shortenUrls()));
        menu->addAction(shorten);
    }
}
TQCString MenuManager::createMenu(TQPixmap icon, TQString text)
{
    static int menucount = 0;
    menucount++;
    TQCString name;
    name.sprintf("kickerclientmenu-%d", menucount );
    KickerClientMenu* p = new KickerClientMenu( 0, name );
    clientmenus.append(p);
    m_kmenu->initialize();
    p->text = text;
    p->icon = icon;
    p->idInParentMenu = m_kmenu->insertClientMenu( p );
    p->createdBy = kapp->dcopClient()->senderId();
    m_kmenu->adjustSize();
    return name;
}
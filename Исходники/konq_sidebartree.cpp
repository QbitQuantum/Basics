// For F2 and other shortcuts to work we can't use a KAction; it would conflict with the
// KAction from the active dolphinpart. So we have to use ShortcutOverride.
// Many users requested keyboard shortcuts to work in the sidebar, so it's worth the ugliness (#80584)
bool KonqSidebarTree::eventFilter(QObject* obj, QEvent* ev)
{
    if (ev->type() == QEvent::ShortcutOverride) {
        QKeyEvent *e = static_cast<QKeyEvent *>( ev );
        if (overrideShortcut(e)) {
            e->accept();
            return true;
        }
    }
    return K3ListView::eventFilter(obj, ev);
}
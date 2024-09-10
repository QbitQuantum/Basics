MediaKeyListener::MediaKeyListener (QObject *receiver) : QAbstractNativeEventFilter (), m_receiver(receiver) {

#if defined Q_OS_WIN

    if (!RegisterHotKey (NULL, TO_WIN_KNUM(HotKey::Stop), MOD_NOREPEAT, VK_MEDIA_STOP)) { throw KeyNotBoundException () ; }
    if (!RegisterHotKey (NULL, TO_WIN_KNUM(HotKey::Play), MOD_NOREPEAT, VK_MEDIA_PLAY_PAUSE)) { throw KeyNotBoundException () ; }
    if (!RegisterHotKey (NULL, TO_WIN_KNUM (HotKey::Prev), MOD_NOREPEAT, VK_MEDIA_PREV_TRACK)) { throw KeyNotBoundException () ; }
    if (!RegisterHotKey (NULL, TO_WIN_KNUM (HotKey::Next), MOD_NOREPEAT, VK_MEDIA_NEXT_TRACK)) { throw KeyNotBoundException () ; }

    if (!RegisterHotKey (NULL, TO_WIN_KNUM (HotKey::AltStop), MOD_ALT | MOD_NOREPEAT, VK_MEDIA_STOP)) { throw KeyNotBoundException () ; }
    if (!RegisterHotKey (NULL, TO_WIN_KNUM (HotKey::AltPlay), MOD_ALT | MOD_NOREPEAT, VK_MEDIA_PLAY_PAUSE)) { throw KeyNotBoundException () ; }
    if (!RegisterHotKey (NULL, TO_WIN_KNUM (HotKey::AltPrev), MOD_ALT | MOD_NOREPEAT, VK_MEDIA_PREV_TRACK)) { throw KeyNotBoundException () ; }
    if (!RegisterHotKey (NULL, TO_WIN_KNUM (HotKey::AltNext), MOD_ALT | MOD_NOREPEAT, VK_MEDIA_NEXT_TRACK)) { throw KeyNotBoundException () ; }

    QEvent::registerEventType (HotKey::Stop);
    QEvent::registerEventType (HotKey::Play);
    QEvent::registerEventType (HotKey::Prev);
    QEvent::registerEventType (HotKey::Next);
    QEvent::registerEventType (HotKey::AltStop);
    QEvent::registerEventType (HotKey::AltPlay);
    QEvent::registerEventType (HotKey::AltPrev);
    QEvent::registerEventType (HotKey::AltNext);

#endif
    
}
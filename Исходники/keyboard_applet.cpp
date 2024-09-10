KeyboardApplet::KeyboardApplet(QObject *parent, const QVariantList &args):
    Plasma::Applet(parent, args),
    xEventNotifier(),
    rules(Rules::readRules(Rules::READ_EXTRAS)),
    keyboardConfig(new KeyboardConfig()),
    layoutsMenu(new LayoutsMenu(*keyboardConfig, *rules, flags))
{
    if( ! X11Helper::xkbSupported(NULL) ) {
        setFailedToLaunch(true, i18n("XKB extension failed to initialize"));
        return;
    }

    m_svg = new Plasma::Svg(this);
    m_svg->setImagePath("widgets/labeltexture");
    m_svg->setContainsMultipleImages(true);
    resize(48,48);

    setHasConfigurationInterface(false);

    setAspectRatioMode(Plasma::KeepAspectRatio);
    //setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    setBackgroundHints(DefaultBackground);
    connect(Plasma::Theme::defaultTheme(), SIGNAL(themeChanged()), this, SLOT(themeChanged()));

    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.connect(QString(), KEYBOARD_DBUS_OBJECT_PATH, KEYBOARD_DBUS_SERVICE_NAME, KEYBOARD_DBUS_CONFIG_RELOAD_MESSAGE, this, SLOT(configChanged()));
}
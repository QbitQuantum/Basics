MWidgetController *MSettingsLanguageSettingsFactory::createWidget(const MSettingsLanguageSettings &settingsItem, MSettingsLanguageWidget &rootWidget, MDataStore *dataStore)
{
    // Create content layout to layout content items in
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    MStylableWidget *widget = new MStylableWidget;
    widget->setStyleName("MSettingsLanguage");
    widget->setLayout(layout);

    createChildren(layout, settingsItem, rootWidget, dataStore);
    layout->addStretch();

    return widget;
}
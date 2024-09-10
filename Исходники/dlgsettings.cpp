DlgSettings::~DlgSettings()
{
    for (int i=0; i<ui_.tab->count(); ++i)
    {
        QWidget* w = ui_.tab->widget(i);
        w->setParent(nullptr);
    }
    ui_.tab->clear();
}
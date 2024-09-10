LyricsProvidersDialog::LyricsProvidersDialog(QString state, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LyricsProvidersDialog)
{
    ui->setupUi(this);

    ui->upButton->setIcon(QIcon::fromTheme("keyboard_move_up"));
    ui->checkButton->setIcon(QIcon::fromTheme("widgets_tickmark_grid"));
    ui->downButton->setIcon(QIcon::fromTheme("keyboard_move_down"));
    ui->providersList->setItemDelegate(new ProviderListItemDelegate(ui->providersList));

    QMap<QString,QString> availableProviders = LyricsManager::listProviders();
    QStringList configList = state.split(',', QString::SkipEmptyParts);

    foreach(QString config, configList) {
        bool active;

        if (active = config.startsWith('+'))
            config = config.mid(1);

        if (availableProviders.contains(config))
            addProvider(config, availableProviders.value(config), active);

        availableProviders.remove(config);
    }
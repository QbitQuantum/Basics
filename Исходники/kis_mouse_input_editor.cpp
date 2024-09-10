KisMouseInputEditor::KisMouseInputEditor(QWidget *parent)
    : KPushButton(parent), d(new Private)
{
    QWidget *popup = new QWidget();

    d->ui = new Ui::KisMouseInputEditor;
    d->ui->setupUi(popup);
    d->ui->mouseButton->setType(KisInputButton::MouseType);

    d->ui->clearModifiersButton->setIcon(KisIconUtils::loadIcon("edit-clear"));
    d->ui->clearMouseButton->setIcon(KisIconUtils::loadIcon("edit-clear"));

    QWidgetAction *action = new QWidgetAction(this);
    action->setDefaultWidget(popup);

    QMenu *menu = new QMenu(this);
    menu->addAction(action);
    setMenu(menu);

    QTimer::singleShot(0, this, SLOT(showMenu()));

    connect(d->ui->mouseButton, SIGNAL(dataChanged()), SLOT(updateLabel()));
    connect(d->ui->modifiersButton, SIGNAL(dataChanged()), SLOT(updateLabel()));
    connect(d->ui->clearMouseButton, SIGNAL(clicked(bool)), d->ui->mouseButton, SLOT(clear()));
    connect(d->ui->clearModifiersButton, SIGNAL(clicked(bool)), d->ui->modifiersButton, SLOT(clear()));
}
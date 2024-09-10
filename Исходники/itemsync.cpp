ItemSync::ItemSync(const QString &label, const QString &icon, ItemWidget *childItem)
    : QWidget( childItem->widget()->parentWidget() )
    , ItemWidgetWrapper(childItem, this)
    , m_label( new QTextEdit(this) )
    , m_icon( new IconWidget(icon, this) )
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetMinimumSize);

    auto labelLayout = new QHBoxLayout;
    connect( layout, &QVBoxLayout::destroyed,
             labelLayout, &QHBoxLayout::deleteLater );
    labelLayout->setContentsMargins(0, 0, 0, 0);
    labelLayout->setSpacing(0);

    labelLayout->addWidget(m_icon);
    labelLayout->addWidget(m_label);
    labelLayout->addStretch();

    layout->addLayout(labelLayout);

    QWidget *w = childItem->widget();
    layout->addWidget(w);
    w->setObjectName("item_child");
    w->setParent(this);

    m_label->setObjectName("item_child");

    m_label->document()->setDefaultFont(font());

    QTextOption option = m_label->document()->defaultTextOption();
    option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    m_label->document()->setDefaultTextOption(option);

    m_label->setReadOnly(true);
    m_label->setUndoRedoEnabled(false);

    m_label->setFocusPolicy(Qt::NoFocus);
    m_label->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_label->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_label->setFrameStyle(QFrame::NoFrame);
    m_label->setContextMenuPolicy(Qt::NoContextMenu);

    m_label->viewport()->installEventFilter(this);

    m_label->setPlainText(label);
}
//----------------------------------------------------------------------------------------
OfsTreeWidget::OfsTreeWidget(QWidget *parent, unsigned int capabilities, std::string initialSelection) : QTreeWidget(parent), mCapabilities(capabilities) 
{
    mSelected = initialSelection;

    setColumnCount(1);
    setHeaderHidden(true);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setDragDropOverwriteMode(false);
    
    if(capabilities & CAP_ALLOW_DROPS)
        setDragDropMode(QAbstractItemView::DropOnly);

    mUnknownFileIcon = mOgitorMainWindow->mIconProvider.icon(QFileIconProvider::File);

    mFile = Ogitors::OgitorsRoot::getSingletonPtr()->GetProjectFile();

    QTreeWidgetItem* item = 0;
    QTreeWidgetItem* pItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Project")));
    pItem->setIcon(0, mOgitorMainWindow->mIconProvider.icon(QFileIconProvider::Folder));
    pItem->setTextColor(0, Qt::black);
    QFont fnt = pItem->font(0);
    fnt.setBold(true);
    pItem->setFont(0, fnt);
    pItem->setWhatsThis(0, QString("/"));
    
    addTopLevelItem(pItem);

    fillTree(pItem, "/");

    if(capabilities & CAP_SHOW_FILES)
        fillTreeFiles(pItem, "/");

    expandItem(pItem);

    if(mSelected == "/")
        setItemSelected(pItem, true);
    else
    {
        NameTreeWidgetMap::iterator it = mItemMap.find(mSelected);

        if(it != mItemMap.end())
        {
            clearSelection();
            scrollToItem(it->second);
            setItemSelected(it->second, true);
        }
    }

    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(onSelectionChanged()));

    if(capabilities & CAP_SHOW_FILES)
    {
        connect(this, SIGNAL(itemCollapsed( QTreeWidgetItem * )), this, SLOT(onItemCollapsed( QTreeWidgetItem * )));
        connect(this, SIGNAL(itemExpanded( QTreeWidgetItem * )), this, SLOT(onItemExpanded( QTreeWidgetItem * )));
    }
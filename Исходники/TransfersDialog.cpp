TransfersDialog::TransfersDialog(QWidget *parent)
: QWidget(parent) {
    /* Invoke the Qt Designer generated object setup routine */
    ui.setupUi(this);

    connect(ui.downloadButton, SIGNAL(clicked()), this, SLOT(download()));
    connect(ui.downloadsList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(downloadsListContextMenu(QPoint)));
    connect(ui.uploadsList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(uploadsListContextMenu(QPoint)));

    //To popup a box informing that a friend is attempting to send a file.
    //QList<qlonglong> is not a default registerd type for QT's meta-object system, so we must first manually register it.
    qRegisterMetaType<QList<qlonglong> >("QList<qlonglong>");
    QObject::connect(guiNotify, SIGNAL(suggestionReceived(unsigned int, QString, QStringList, QStringList, QList<qlonglong>)),
                     this, SLOT(suggestionReceived(unsigned int, QString, QStringList, QStringList, QList<qlonglong>)), Qt::QueuedConnection);

    QHeaderView *header = ui.downloadsList->header() ;
    header->hideSection(DOWNLOAD_FRIEND_ID);
    header->hideSection(DOWNLOAD_ITEM_TYPE);
    header->hideSection(DOWNLOAD_ITEM_ID);
    header->hideSection(DOWNLOAD_FINAL_LOCATION);

    header = ui.uploadsList->header() ;
    header->hideSection(UPLOAD_LIBRARYMIXER_ID);
    header->hideSection(UPLOAD_ITEM_ID);
    header->hideSection(UPLOAD_ITEM_TYPE);

    //Without this preliminary resizing, empty columns will visibly resize after view already displayed
    ui.downloadsList->resizeColumnToContents(DOWNLOAD_NAME_COLUMN);
    ui.downloadsList->resizeColumnToContents(DOWNLOAD_FRIEND_COLUMN);
    ui.downloadsList->resizeColumnToContents(DOWNLOAD_SPEED_COLUMN);
    ui.downloadsList->resizeColumnToContents(DOWNLOAD_REMAINING_COLUMN);
    ui.downloadsList->resizeColumnToContents(DOWNLOAD_TOTAL_SIZE_COLUMN);
    ui.downloadsList->resizeColumnToContents(DOWNLOAD_PERCENT_COLUMN);
    ui.downloadsList->resizeColumnToContents(DOWNLOAD_STATUS_COLUMN);
    ui.uploadsList->resizeColumnToContents(UPLOAD_FILE_COLUMN);
    ui.uploadsList->resizeColumnToContents(UPLOAD_FRIEND_COLUMN);
    ui.uploadsList->resizeColumnToContents(UPLOAD_SPEED_COLUMN);
    ui.uploadsList->resizeColumnToContents(UPLOAD_TRANSFERRED_COLUMN);
    ui.uploadsList->resizeColumnToContents(UPLOAD_STATUS_COLUMN);

    ui.downloadsList->sortItems(0, Qt::AscendingOrder);
    ui.uploadsList->sortItems(0, Qt::AscendingOrder);

    connect(files, SIGNAL(responseLendOfferReceived(uint,uint,QString,QStringList,QStringList,QList<qlonglong>)),
            this, SLOT(responseLendOfferReceived(uint,uint,QString,QStringList,QStringList,QList<qlonglong>)), Qt::QueuedConnection);

    /* This needs to change in the future, but for now, we simply refresh the entire view (including total transfer rates in corner) once every second. */
    QTimer *timer = new QTimer(this);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(insertTransfers()));
    timer->start(1000);
}
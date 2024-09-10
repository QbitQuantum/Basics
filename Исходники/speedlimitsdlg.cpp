    SpeedLimitsDlg::SpeedLimitsDlg(bt::TorrentInterface* current, Core* core, QWidget* parent)
        : QDialog(parent), core(core), current(current)
    {
        setupUi(this);
        setWindowIcon(QIcon::fromTheme("kt-speed-limits"));
        setWindowTitle(i18n("Speed Limits"));

        model = new SpeedLimitsModel(core, this);
        QSortFilterProxyModel* pm = new QSortFilterProxyModel(this);
        pm->setSourceModel(model);
        pm->setSortRole(Qt::UserRole);

        m_speed_limits_view->setModel(pm);
        m_speed_limits_view->setItemDelegate(new SpinBoxDelegate(this));
        m_speed_limits_view->setUniformRowHeights(true);
        m_speed_limits_view->setSortingEnabled(true);
        m_speed_limits_view->sortByColumn(0, Qt::AscendingOrder);
        m_speed_limits_view->header()->setSortIndicatorShown(true);
        m_speed_limits_view->header()->setClickable(true);
        m_speed_limits_view->setAlternatingRowColors(true);

        QPushButton* apply_btn = m_buttonBox->button(QDialogButtonBox::Apply);
        apply_btn->setEnabled(false);
        connect(model, &SpeedLimitsModel::enableApply, apply_btn, &QPushButton::setEnabled);
        connect(apply_btn, &QPushButton::clicked, this, &SpeedLimitsDlg::apply);
        connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

        m_upload_rate->setValue(Settings::maxUploadRate());
        m_download_rate->setValue(Settings::maxDownloadRate());
        connect(m_upload_rate, SIGNAL(valueChanged(int)), this, SLOT(spinBoxValueChanged(int)));
        connect(m_download_rate, SIGNAL(valueChanged(int)), this, SLOT(spinBoxValueChanged(int)));
        connect(m_filter, SIGNAL(textChanged(QString)), pm, SLOT(setFilterFixedString(QString)));
        loadState();

        // if current is specified, select it and scroll to it
        if (current)
        {
            kt::QueueManager* qman = core->getQueueManager();
            int idx = 0;
            QList<bt::TorrentInterface*>::iterator itr = qman->begin();
            while (itr != qman->end())
            {
                if (*itr == current)
                    break;

                idx++;
                itr++;
            }

            if (itr != qman->end())
            {
                QItemSelectionModel* sel = m_speed_limits_view->selectionModel();
                QModelIndex midx = pm->mapFromSource(model->index(idx, 0));
                QModelIndex midx2 = pm->mapFromSource(model->index(idx, 4));
                sel->select(QItemSelection(midx, midx2), QItemSelectionModel::Select);
                m_speed_limits_view->scrollTo(midx);
            }
        }
    }
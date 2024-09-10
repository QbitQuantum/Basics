RegDisplayPanel::RegDisplayPanel(QWidget *parent, IoBackend *io_backend, const SocRegRef& reg_ref)
    :QGroupBox(parent), m_io_backend(io_backend), m_reg(reg_ref), m_reg_font(font())
{
    bool read_only = m_io_backend->IsReadOnly();

    QVBoxLayout *right_layout = new QVBoxLayout;

    const soc_dev_addr_t& dev_addr = m_reg.GetDevAddr();
    const soc_reg_t& reg = m_reg.GetReg();
    const soc_reg_addr_t& reg_addr = m_reg.GetRegAddr();

    m_reg_font.setWeight(100);
    m_reg_font.setKerning(false);

    QString reg_name;
    reg_name.sprintf("HW_%s_%s", dev_addr.name.c_str(), reg_addr.name.c_str());
    QStringList names;
    QVector< soc_addr_t > addresses;
    names.append(reg_name);
    addresses.append(reg_addr.addr);
    if(reg.flags & REG_HAS_SCT)
    {
        names.append(reg_name + "_SET");
        names.append(reg_name + "_CLR");
        names.append(reg_name + "_TOG");
        addresses.append(reg_addr.addr + 4);
        addresses.append(reg_addr.addr + 8);
        addresses.append(reg_addr.addr + 12);
    }

    QString str;
    str += "<table align=left>";
    for(int i = 0; i < names.size(); i++)
        str += "<tr><td><b>" + names[i] + "</b></td></tr>";
    str += "</table>";
    QLabel *label_names = new QLabel;
    label_names->setTextFormat(Qt::RichText);
    label_names->setText(str);

    QString str_addr;
    str_addr += "<table align=left>";
    for(int i = 0; i < names.size(); i++)
        str_addr += "<tr><td><b>" + QString().sprintf("0x%03x", addresses[i]) + "</b></td></tr>";
    str_addr += "</table>";
    QLabel *label_addr = new QLabel;
    label_addr->setTextFormat(Qt::RichText);
    label_addr->setText(str_addr);

    QHBoxLayout *top_layout = new QHBoxLayout;
    top_layout->addStretch();
    top_layout->addWidget(label_names);
    top_layout->addWidget(label_addr);
    top_layout->addStretch();

    m_raw_val_name = new QLabel;
    m_raw_val_name->setText("Raw value:");
    m_raw_val_edit = new RegLineEdit;
    m_raw_val_edit->SetReadOnly(read_only);
    m_raw_val_edit->GetLineEdit()->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_raw_val_edit->GetLineEdit()->setValidator(new SocFieldValidator(m_raw_val_edit));
    m_raw_val_edit->EnableSCT(!!(reg.flags & REG_HAS_SCT));
    m_raw_val_edit->GetLineEdit()->setFont(m_reg_font);
    QHBoxLayout *raw_val_layout = new QHBoxLayout;
    raw_val_layout->addStretch();
    raw_val_layout->addWidget(m_raw_val_name);
    raw_val_layout->addWidget(m_raw_val_edit);
    raw_val_layout->addStretch();

    m_value_table = new GrowingTableWidget;
    m_value_table->setRowCount(reg.field.size());
    m_value_table->setColumnCount(5);
    for(size_t row = 0; row < reg.field.size(); row++)
    {
        const soc_reg_field_t& field = reg.field[row];
        QString bits_str;
        if(field.first_bit == field.last_bit)
            bits_str.sprintf("%d", field.first_bit);
        else
            bits_str.sprintf("%d:%d", field.last_bit, field.first_bit);
        QTableWidgetItem *item = new QTableWidgetItem(bits_str);
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        m_value_table->setItem(row, FieldBitsColumn, item);
        item = new QTableWidgetItem(QString(field.name.c_str()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        m_value_table->setItem(row, FieldNameColumn, item);
        item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setData(Qt::DisplayRole, QVariant::fromValue(SocFieldCachedValue()));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        m_value_table->setItem(row, FieldValueColumn, item);
        item = new QTableWidgetItem("");
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        m_value_table->setItem(row, FieldMeaningColumn, item);
        item = new QTableWidgetItem(QString(field.desc.c_str()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        m_value_table->setItem(row, FieldDescColumn, item);
    }
    m_value_table->setHorizontalHeaderItem(FieldBitsColumn, new QTableWidgetItem("Bits"));
    m_value_table->setHorizontalHeaderItem(FieldNameColumn, new QTableWidgetItem("Name"));
    m_value_table->setHorizontalHeaderItem(FieldValueColumn, new QTableWidgetItem("Value"));
    m_value_table->setHorizontalHeaderItem(FieldMeaningColumn, new QTableWidgetItem("Meaning"));
    m_value_table->setHorizontalHeaderItem(FieldDescColumn, new QTableWidgetItem("Description"));
    m_value_table->verticalHeader()->setVisible(false);
    m_value_table->resizeColumnsToContents();
    m_value_table->horizontalHeader()->setStretchLastSection(true);
    m_value_table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    SocFieldCachedItemDelegate *m_table_delegate = new SocFieldCachedItemDelegate(this);
    m_table_edit_factory = new QItemEditorFactory();
    SocFieldCachedEditorCreator *m_table_edit_creator = new SocFieldCachedEditorCreator();
    // FIXME see QTBUG-30392
    m_table_edit_factory->registerEditor((QVariant::Type)qMetaTypeId< SocFieldCachedValue >(),
        m_table_edit_creator);
    m_table_delegate->setItemEditorFactory(m_table_edit_factory);
    m_value_table->setItemDelegate(m_table_delegate);

    m_sexy_display = new RegSexyDisplay(reg_ref, this);
    m_sexy_display->setFont(m_reg_font);

    m_desc = new QLabel(this);
    m_desc->setTextFormat(Qt::RichText);
    m_desc->setText(QString::fromStdString(m_reg.GetReg().desc));

    right_layout->addWidget(m_desc);
    right_layout->addLayout(top_layout);
    if(raw_val_layout)
        right_layout->addLayout(raw_val_layout);
    right_layout->addWidget(m_sexy_display);
    right_layout->addWidget(m_value_table);

    setTitle("Register Description");
    m_viewport = new QWidget;
    m_viewport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_viewport->setLayout(right_layout);
    m_scroll = new QScrollArea;
    m_scroll->setWidget(m_viewport);
    m_scroll->setWidgetResizable(true);
    m_scroll->setFrameShape(QFrame::NoFrame);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_scroll, 1);
    setLayout(layout);
    AllowWrite(false);

    m_ignore_cell_change = false;
    // load data
    Reload();

    connect(m_raw_val_edit->GetLineEdit(), SIGNAL(returnPressed()), this, SLOT(OnRawRegValueReturnPressed()));
    connect(m_value_table, SIGNAL(cellChanged(int, int)), this, SLOT(OnRegFieldValueChanged(int, int)));
}
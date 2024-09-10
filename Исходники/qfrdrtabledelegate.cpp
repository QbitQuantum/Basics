QWidget *QFRDRTableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const {
    QVariant dat=index.data(Qt::DisplayRole);
    QString expression=index.data(QFRDRTable::TableExpressionRole).toString();
    if (expression.isEmpty()) {
        if (dat.type()==QVariant::Invalid) {
            dat=index.data(Qt::EditRole);
        }
         if ( dat.type() == QVariant::DateTime || dat.type() == QVariant::Time || dat.type() == QVariant::Date ) {
             QDateTimeEdit *editor = new QDateTimeEdit(parent);
             //editor->setDisplayFormat("dd/M/yyyy");
             editor->setCalendarPopup(true);
             return editor;
         }
         if ( !index.isValid() || dat.type() == QVariant::Double ) {
             QFDoubleEdit* editor=new QFDoubleEdit(parent);
             editor->setCheckBounds(false, false);
             editor->setShowUpDown(false);
             return editor;
         }
         if ( dat.type() == QVariant::Int || dat.type() == QVariant::LongLong ) {
             QSpinBox* editor=new QSpinBox(parent);
             editor->setRange(INT_MIN, INT_MAX);
             editor->setButtonSymbols(QAbstractSpinBox::NoButtons);
             return editor;
         }
         if ( dat.type() == QVariant::UInt || dat.type() == QVariant::ULongLong ) {
             QSpinBox* editor=new QSpinBox(parent);
             editor->setRange(0, UINT_MAX);
             editor->setButtonSymbols(QAbstractSpinBox::NoButtons);
             return editor;
         }
         if ( dat.type() == QVariant::Bool) {
             QCheckBox* editor=new QCheckBox(parent);
             return editor;
         }

         QLineEdit *editor = new QLineEdit(parent);

         // create a completer with the strings in the column as model
         QStringList allStrings;
         for (int i = 1; i<index.model()->rowCount(); i++) {
             QString strItem(index.model()->data(index.sibling(i, index.column()),
                 Qt::EditRole).toString());

             if (!allStrings.contains(strItem))
                 allStrings.append(strItem);
         }

         QCompleter *autoComplete = new QCompleter(allStrings);
         editor->setCompleter(autoComplete);
         connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
         return editor;
    } else {
        QWidget* widExpression=new QWidget(parent);
        widExpression->setFocusPolicy(Qt::StrongFocus);
        widExpression->setAutoFillBackground(true);
        QHBoxLayout* layout=new QHBoxLayout();
        layout->setContentsMargins(0,0,0,0);
        layout->setSpacing(1);
        widExpression->setLayout(layout);
        QLabel* label=new QLabel(widExpression);
        layout->addWidget(label, 1);
        label->setTextFormat(Qt::RichText);
        label->setText(tr("<b><font color=\"blue\">&Sigma;:</font> %1</b><i>&nbsp;&nbsp;= %2</i>").arg(expression).arg(dat.toString()));
        label->setAutoFillBackground(true);
        QFont f=label->font();
        f.setPointSizeF(f.pointSizeF()*0.9);
        label->setFont(f);
        QAction* actEdtExp;        
        QToolButton* btnEdtExp=createButtonAndAction(actEdtExp, QIcon(":/table/formula.png"), tr("edit expression ..."), widExpression);
        actEdtExp->setParent(widExpression);
        connect(actEdtExp, SIGNAL(triggered()), this, SLOT(doEditExpression()));
        layout->addWidget(btnEdtExp);
        QAction* actClearExp;
        QToolButton* btnClearExp=createButtonAndAction(actClearExp, QIcon(":/table/formulaclear.png"), tr("clear expression ..."), widExpression);
        actClearExp->setParent(widExpression);
        connect(actClearExp, SIGNAL(triggered()), this, SLOT(doClearExpression()));
        layout->addWidget(btnClearExp);
        widExpression->setFocus();
        return widExpression;
    }
}
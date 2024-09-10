QPointer<QWidget> QuBoolean::makeWidget(Questionnaire *questionnaire)
{
    bool read_only = questionnaire->readOnly();

    QPointer<QWidget> widget = new QWidget();
    widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QHBoxLayout* layout = new QHBoxLayout();
    widget->setLayout(layout);
    // To align things in a QHBoxLayout, align the widgets within the layout:
    //      layout->setAlignment(widget, alignment)
    // not the layout:
    //      layout->setAlignment(alignment)

    // Label
    QWidget* labelwidget = nullptr;
    if (!m_text.isEmpty() && !m_as_text_button) {
        // Text label
        if (!read_only && m_content_clickable) {
            ClickableLabelWordWrapWide* label = new ClickableLabelWordWrapWide(m_text);
            // label->setObjectName("debug_green");
            connect(label, &ClickableLabelWordWrapWide::clicked,
                    this, &QuBoolean::clicked);
            labelwidget = label;
        } else {
            LabelWordWrapWide* label = new LabelWordWrapWide(m_text);
            labelwidget = label;
        }
        int fontsize = questionnaire->fontSizePt(
            m_big_text ? UiConst::FontSize::Big : UiConst::FontSize::Normal);
        QString css = UiFunc::textCSS(fontsize, m_bold, m_italic);
        labelwidget->setStyleSheet(css);
        // needs_stretch stays false (or we'll prevent the text expanding)
    } else if (!m_image_filename.isEmpty()) {
        // Image label
        QPixmap image = UiFunc::getPixmap(m_image_filename, m_image_size);
        if (!read_only && m_content_clickable) {
            ClickableLabel* label = new ClickableLabel();
            label->setPixmap(image);
            connect(label, &ClickableLabel::clicked,
                    this, &QuBoolean::clicked);
            labelwidget = label;
        } else {
            QLabel* label = new QLabel();
            label->setFixedSize(image.size());
            label->setPixmap(image);
            labelwidget = label;
        }
    }
    // otherwise... no label, just the indicator

    // Indicator
    m_indicator = new BooleanWidget();
    m_indicator->setSize(m_big_indicator);
    m_indicator->setReadOnly(read_only);
    if (m_as_text_button) {
        m_indicator->setAppearance(BooleanWidget::Appearance::Text);
        m_indicator->setText(m_text);
    } else {
        m_indicator->setAppearance(BooleanWidget::Appearance::CheckRed);
    }
    if (!read_only) {
        connect(m_indicator, &BooleanWidget::clicked,
                this, &QuBoolean::clicked);
    }

    // Whole thing
    if (labelwidget) {
        if (m_indicator_on_left) {
            layout->addWidget(m_indicator);
            layout->addWidget(labelwidget);
        } else {
            layout->addWidget(labelwidget);
            layout->addWidget(m_indicator);
        }
        layout->setAlignment(labelwidget, Qt::AlignVCenter);
    } else {
        // Just the indicator
        layout->addWidget(m_indicator);
    }
    layout->addStretch();
    layout->setAlignment(m_indicator, Qt::AlignTop);

    setFromField();

    return widget;
}
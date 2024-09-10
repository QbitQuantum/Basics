QPointer<QWidget> QuMCQGridDouble::makeWidget(Questionnaire* questionnaire)
{
    bool read_only = questionnaire->readOnly();
    m_widgets1.clear();
    m_widgets2.clear();

    // As per QuMCQGrid

    QGridLayout* grid = new QGridLayout();
    grid->setHorizontalSpacing(UiConst::MCQGRID_HSPACING);
    grid->setVerticalSpacing(UiConst::MCQGRID_VSPACING);

    int n_subtitles = m_subtitles.size();
    int n_rows = 1 + n_subtitles + m_questions_with_fields.size();
    int n_cols = m_options1.size() + m_options2.size() + 3;
    Qt::Alignment response_align = McqFunc::response_widget_align;
    int row = 0;

    // First column: titles, subtitles, questions
    // Then vertical break
    // Then m_options1
    // Then vertical break
    // Then m_options2

    // I note in passing:
    // http://stackoverflow.com/questions/25101085/style-sheet-is-appliped-to-the-cells-in-qgridlayout-instead-of-the-parent-contai

    // Title row
    McqFunc::addOptionBackground(grid, row, 0, n_cols);
    McqFunc::addTitle(grid, row, m_title);
    addOptions(grid, row);
    ++row;  // new row after title/option text

    // Main question rows (with any preceding subtitles)
    for (int qi = 0; qi < m_questions_with_fields.size(); ++qi) {

        // Any preceding subtitles?
        for (int s = 0; s < n_subtitles; ++s) {
            const McqGridSubtitle& sub = m_subtitles.at(s);
            if (sub.pos() == qi) {
                // Yes. Add a subtitle row.
                McqFunc::addOptionBackground(grid, row, 0, n_cols);
                McqFunc::addSubtitle(grid, row, sub.string());
                if (sub.repeatOptions()) {
                    addOptions(grid, row);
                }
                ++row;  // new row after subtitle
            }
        }

        // The question
        McqFunc::addQuestion(grid, row,
                                 m_questions_with_fields.at(qi).question());

        // The response widgets
        for (bool first : {true, false}) {
            const NameValueOptions& opts = first ? m_options1 : m_options2;
            int n_options = opts.size();
            QList<QList<QPointer<BooleanWidget>>>& widgets =
                    first ? m_widgets1 : m_widgets2;
            QList<QPointer<BooleanWidget>> question_widgets;
            for (int vi = 0; vi < n_options; ++vi) {
                QPointer<BooleanWidget> w = new BooleanWidget();
                w->setAppearance(BooleanWidget::Appearance::Radio);
                w->setReadOnly(read_only);
                if (!read_only) {
                    connect(w, &BooleanWidget::clicked,
                            std::bind(&QuMCQGridDouble::clicked,
                                      this, qi, first, vi));
                }
                grid->addWidget(w, row, colnum(first, vi), response_align);

                question_widgets.append(w);
            }
            widgets.append(question_widgets);
        }

        ++row;  // new row after question/response widgets
    }

    // Set widths, if asked
    if (m_question_width > 0 &&
            m_option1_widths.size() == m_options1.size() &&
            m_option2_widths.size() == m_options2.size()) {
        grid->setColumnStretch(0, m_question_width);
        for (bool first : {true, false}) {
            QList<int>& widths = first ? m_option1_widths : m_option2_widths;
            for (int i = 0; i < widths.size(); ++i) {
                grid->setColumnStretch(colnum(first, i), widths.at(i));
            }
        }
    }

    // Vertical lines
    McqFunc::addVerticalLine(grid, spacercol(true), n_rows);
    McqFunc::addVerticalLine(grid, spacercol(false), n_rows);

    QPointer<QWidget> widget = new QWidget();
    widget->setLayout(grid);
    widget->setObjectName("mcq_grid_double");
    if (m_expand) {
        widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    } else {
        widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    }

    setFromFields();

    return widget;
}
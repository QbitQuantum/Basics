FormatTextEdit::FormatTextEdit(QWidget *parent)
    : ExpandingTextEdit(parent)
{
    setLineWrapMode(QTextEdit::WidgetWidth);
    setAcceptRichText(false);
    QTextOption option = document()->defaultTextOption();
    option.setFlags(option.flags()
                    | QTextOption::ShowLineAndParagraphSeparators
                    | QTextOption::ShowTabsAndSpaces);
    document()->setDefaultTextOption(option);

    // Do not set different background if disabled
    QPalette p = palette();
    p.setColor(QPalette::Disabled, QPalette::Base, p.color(QPalette::Active, QPalette::Base));
    setPalette(p);

    setEditable(true);

    m_highlighter = new MessageHighlighter(this);
}
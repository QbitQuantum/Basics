TextBox::TextBox(const Widget2 *const widget) :
    Widget(widget),
    MouseListener(),
    KeyListener(),
    mTextRows(),
    mCaretColumn(0),
    mCaretRow(0),
    mMinWidth(getWidth()),
    mEditable(true),
    mOpaque(true)
{
    mAllowLogic = false;
    setText("");
    setFocusable(true);

    addMouseListener(this);
    addKeyListener(this);
    adjustSize();

    mForegroundColor = getThemeColor(Theme::TEXTBOX);
    setOpaque(false);
    setFrameSize(0);
}
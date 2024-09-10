GuiTable::GuiTable(const Widget2 *const widget,
                   TableModel *const initial_model,
                   const bool opacity) :
    Widget(widget),
    MouseListener(),
    KeyListener(),
    mModel(nullptr),
    mTopWidget(nullptr),
    mActionListeners2(),
    mHighlightColor(getThemeColor(ThemeColorId::HIGHLIGHT)),
    mSelectedRow(-1),
    mSelectedColumn(-1),
    mLinewiseMode(false),
    mWrappingEnabled(false),
    mOpaque(opacity),
    mSelectable(true)
{
    mAllowLogic = false;
    mBackgroundColor = getThemeColor(ThemeColorId::BACKGROUND);

    setModel(initial_model);
    setFocusable(true);

    addMouseListener(this);
    addKeyListener(this);
}
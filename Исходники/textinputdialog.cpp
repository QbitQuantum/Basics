void TextInputDialog::adjustSize()
{
    const int titleWidth = 3 * getFont()->getWidth(getCaption()) / 2;
    const int fontHeight = getFont()->getHeight();

    setWidth(titleWidth + 4 * getPadding());
    setHeight(fontHeight + mOkButton->getHeight() +
              mValueField->getHeight() + 8 * getPadding());

    setDefaultSize(getWidth(), getHeight(), ImageRect::CENTER);

    Layout &layout = getLayout();
    layout.setRowHeight(0, Layout::AUTO_SET);
    layout.setRowHeight(1, Layout::AUTO_SET);
    layout.setColWidth(2, Layout::AUTO_SET);
    layout.setColWidth(3, Layout::AUTO_SET);
}
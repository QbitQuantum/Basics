void ComboBox::setItems(const std::vector<std::string> &items, const std::vector<std::string> &itemsShort) {
    assert(items.size() == itemsShort.size());
    mItems = items;
    mItemsShort = itemsShort;
    if (mSelectedIndex < 0 || mSelectedIndex >= (int) items.size())
        mSelectedIndex = 0;
    while (mPopup->childCount() != 0)
        mPopup->removeChild(mPopup->childCount()-1);
    mPopup->setLayout(new GroupLayout(10));
    int index = 0;
    for (const auto &str: items) {
        Button *button = new Button(mPopup, str);
        button->setFlags(Button::RadioButton);
        button->setCallback([&, index] {
            mSelectedIndex = index;
            setCaption(mItemsShort[index]);
            setPushed(false);
            popup()->setVisible(false);
            if (mCallback)
                mCallback(index);
        });
        index++;
    }
    setSelectedIndex(mSelectedIndex);
}
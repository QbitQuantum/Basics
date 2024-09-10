void StorageWindow::fontChanged()
{
    Window::fontChanged();

    if (mWidgets.size() > 0)
        clear();

    place(0, 0, mSlotsLabel).setPadding(3);
    place(1, 0, mSlotsBar, 3);
    place(0, 1, mInvenScroll, 4, 4);
    place(2, 5, mCloseButton);
    place(3, 5, mRetrieveButton);

    Layout &layout = getLayout();
    layout.setRowHeight(0, mRetrieveButton->getHeight());

    restoreFocus();
}
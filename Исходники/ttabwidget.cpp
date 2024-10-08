void TTabWidget::setTabVisible(int idx, bool visible)
{
    if (hidden_idx.contains(idx) != visible)
        return;

    int bar_idx = idx;
    int vector_idx = 0;
    while (vector_idx < hidden_idx.size() && hidden_idx.at(vector_idx) < idx) {
        bar_idx--;
        vector_idx++;
    }

    if (visible ? vector_idx >= hidden_idx.size() : bar_idx >= count())
        return;

    doing_stuff = true;

    if (!visible) {
        QWidget *wid = widget(bar_idx);
        hidden_wid.insert(vector_idx, wid);
        hidden_idx.insert(vector_idx, idx);
        hidden_data.insert(vector_idx, qMakePair<QIcon, QString>(tabIcon(bar_idx), tabText(bar_idx)));

        removeTab(bar_idx);
        wid->setParent(this);
    } else {
        insertTab(bar_idx, hidden_wid.at(vector_idx), hidden_data.at(vector_idx).first, hidden_data.at(vector_idx).second);

        hidden_wid.remove(vector_idx);
        hidden_idx.remove(vector_idx);
        hidden_data.remove(vector_idx);
    }

    doing_stuff = false;
}
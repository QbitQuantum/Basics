bool ListViewItemWidget::OnEvent(const TBWidgetEvent &ev)
{
    if (ev.type == EVENT_TYPE_WHEEL)
    {
        return false;
    }

    if (ev.type == EVENT_TYPE_POINTER_DOWN || ev.type == EVENT_TYPE_RIGHT_POINTER_UP)
    {
        TBWidget* parent = GetParent();

        while (parent)
        {
            if (parent->IsOfType<TBSelectList>())
            {
                TBWidgetEvent nev = ev;
                nev.ref_id = item_->id;
                parent->InvokeEvent(nev);
                break;
            }

            parent = parent->GetParent();
        }

        return true;
    }

    // get clicks this way, not sure we want to
    if (ev.type == EVENT_TYPE_CLICK &&  ev.target == expandBox_ && ev.target->GetID() == item_->id)
    {
        item_->SetExpanded(!item_->GetExpanded());

        source_->list_->InvalidateList();

        // want to bubble
        return false;
    }

    return TBLayout::OnEvent(ev);
}
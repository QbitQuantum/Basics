void UIDragDrop::HandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    if (dragObject_.Null() && dragSourceWidget_.Null())
        return;

    if (dragObject_.Null())
    {
        dragObject_ = dragSourceWidget_->GetDragObject();

        if (dragObject_.Null())
        {
            dragSourceWidget_ = 0;
            return;
        }

    }

    using namespace MouseMove;

    int x = eventData[P_X].GetInt();
    int y = eventData[P_Y].GetInt();

    // tolerance to 8 pixels to start drag/drop operation
    IntVector2 mousePos(x, y);
    mousePos -= mouseDownPosition_;
    if (Abs(mousePos.x_) < 8 && Abs(mousePos.y_) < 8)
        return;

    // initialize if necessary
    if (dragLayout_->GetVisibility() == UI_WIDGET_VISIBILITY_GONE)
    {
        dragLayout_->GetInternalWidget()->SetZ(WIDGET_Z_TOP);
        dragLayout_->SetVisibility(UI_WIDGET_VISIBILITY_VISIBLE);
        dragText_->SetText(dragObject_->GetText());

        UIPreferredSize* sz = dragLayout_->GetPreferredSize();
        dragLayout_->SetRect(IntRect(0, 0, sz->GetMinWidth(), sz->GetMinHeight()));
    }

    // see if we have a widget
    TBWidget* tbw = TBWidget::hovered_widget;

    while(tbw && (!tbw->GetDelegate() || tbw->IsOfType<TBLayout>()))
    {
        tbw = tbw->GetParent();
    }

    if (!tbw || !tbw->GetParent())
        return;

    UIWidget* hoverWidget = (UIWidget*) tbw->GetDelegate();

    if (!hoverWidget->GetInternalWidget())
        return;

    if (hoverWidget != currentTargetWidget_)
    {
        if (currentTargetWidget_)
        {
            VariantMap exitData;
            exitData[DragExitWidget::P_WIDGET] = currentTargetWidget_;
            exitData[DragExitWidget::P_DRAGOBJECT] = dragObject_;
            currentTargetWidget_->SendEvent(E_DRAGEXITWIDGET, exitData);
        }

        currentTargetWidget_ = hoverWidget;

        VariantMap enterData;
        enterData[DragEnterWidget::P_WIDGET] = currentTargetWidget_;
        enterData[DragEnterWidget::P_DRAGOBJECT] = dragObject_;
        currentTargetWidget_->SendEvent(E_DRAGENTERWIDGET, enterData);

    }

    dragLayout_->SetPosition(x, y - 20);

}
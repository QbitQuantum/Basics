void UIViewport::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & ViewComponentFieldMask)
    {
        clearChildren();
        if(getViewComponent() != NULL)
        {
            pushToChildren(getViewComponent());
        }
    }

    if((whichField & ViewSizeFieldMask) && getViewComponent() != NULL)
    {
        updateViewComponentSize();

        produceStateChanged(ChangeEvent::create(UIViewportRefPtr(this), getSystemTime()));
    }

    if((whichField & ViewPositionFieldMask) && getViewComponent() != NULL)
    {
        getViewComponent()->editPosition().setValues(-getViewPosition().x(),-getViewPosition().y());

        produceStateChanged(ChangeEvent::create(UIViewportRefPtr(this), getSystemTime()));
    }

    if((whichField & ViewSizeFieldMask) ||
       (whichField & ViewPositionFieldMask) ||
       (whichField & SizeFieldMask))
    {
        produceStateChanged(ChangeEvent::create(UIViewportRefPtr(this), getSystemTime()));
    }

    if(whichField & SizeFieldMask &&
       getViewComponent() != NULL &&
       (getViewComponent()->getScrollableTracksViewportHeight() || getViewComponent()->getScrollableTracksViewportWidth()))
    {
        updateViewComponentSize();
    }
}
void UIEditField::SetTextAlign(TEXT_ALIGN align)
{
    if (!widget_)
        return;

    // safe cast?
    TBEditField* w = (TBEditField*) widget_;

    switch (align)
    {
        case TEXT_ALIGN_CENTER:
            w->SetTextAlign(TB_TEXT_ALIGN_CENTER);
            break;
        case TEXT_ALIGN_LEFT:
            w->SetTextAlign(TB_TEXT_ALIGN_LEFT);
            break;
        case TEXT_ALIGN_RIGHT:
            w->SetTextAlign(TB_TEXT_ALIGN_RIGHT);
            break;
    }

}
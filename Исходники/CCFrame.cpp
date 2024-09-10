Frame* EventFrame::clone()
{
    EventFrame* frame = EventFrame::create();
    frame->setEvent(_event);

    frame->cloneProperty(this);

    return frame;
}
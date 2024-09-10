void pan_manipulator::handle_mouse_down(visionaray::mouse_event const& event)
{

    if (dragging_)
    {
        return;
    }

    dragging_ = true;

    // TODO: do this in base?
    last_pos_ = event.get_pos();

    camera_manipulator::handle_mouse_down(event);

}
void arcball_manipulator::handle_mouse_down(visionaray::mouse_event const& event)
{

    bool buttons   = event.get_buttons() & buttons_;
    bool modifiers = (modifiers_ == keyboard::NoKey && event.get_modifiers() == keyboard::NoKey)
                   || event.get_modifiers()  & modifiers_;

    if (!dragging_ && buttons && modifiers)
    {
        dragging_ = true;
        ball_.down_pos = ball_.project(
                event.get_pos().x,
                event.get_pos().y,
                camera_.get_viewport()
                );
        ball_.down_rotation = ball_.rotation;

        down_modifiers_ = event.get_modifiers();
    }

    camera_manipulator::handle_mouse_down(event);

}
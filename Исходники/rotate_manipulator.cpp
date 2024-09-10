bool rotate_manipulator::handle_mouse_move(visionaray::mouse_event const& event)
{
    auto bdisc = flip( bounding_disc(), camera_.get_viewport() );

    mouse_over_ = bdisc.contains(event.get_pos());

    if (dragging_ && event.get_buttons() & buttons_)
    {
        auto brect = flip( bounding_rect(), camera_.get_viewport() );

        vec3 curr_pos = ball_.project(
                event.get_pos().x,
                event.get_pos().y,
                brect
                );

        auto last_vsr = rotation(ball_.rotation);
        ball_.rotation = quat::rotation(ball_.down_pos, curr_pos) * ball_.down_rotation;

        auto vsr = rotation(ball_.rotation);

        auto trans = model_matrix_(3);

        model_matrix_.col3 = vec4(0.0f, 0.0f, 0.0f, 1.0f);

        auto vm = camera_.get_view_matrix();
        vm.col3 = vec4(0.0f, 0.0f, 0.0f, 1.0f);

        model_matrix_ = inverse(vm) * vsr * inverse(last_vsr) * vm * model_matrix_;
        model_matrix_.col3 = trans;

        return true;
    }
    else
    {
        hovered_ = select_from_mouse_pointer(event);
        return false;
    }
}
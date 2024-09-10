bool dev::sixense::process_tick(app::event *E)
{
    const double dt = E->data.tick.dt;

    if (::host->root())
        translate();

    if (flying)
    {
        quat o = ::host->get_orientation();
        quat q = normal(inverse(init_q) * curr_q);
        quat r = normal(slerp(quat(), q, 1.0 / 30.0));
        vec3 d = (curr_p - init_p) * dt * move_rate;

        ::host->set_orientation(o * r);
        ::host->offset_position(o * d);
    }

    return false;
}
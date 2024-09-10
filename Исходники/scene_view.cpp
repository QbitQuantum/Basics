void scene_view::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->localPos().x();
    int y = event->localPos().y();

    const bool shift = event->modifiers().testFlag(Qt::ShiftModifier);
    const bool alt = event->modifiers().testFlag(Qt::AltModifier);

    bool lock_mouse = false;

    auto btns = event->buttons();
    if (btns.testFlag(Qt::RightButton))
    {
        if (shift)
        {
            m_camera_yaw += x - m_mouse_x;
            m_camera_pitch += y - m_mouse_y;
            m_camera_yaw.normalize();
            m_camera_pitch.clamp(-90, 90);
        }
        else if (alt)
        {
            m_camera_pos.y -= (y - m_mouse_y) * 10.0f;
            m_camera_pos.y = nya_math::clamp(m_camera_pos.y, 20.0f, 5000.0f);
        }
        else
        {
            nya_math::vec2 dpos(x - m_mouse_x, y - m_mouse_y);
            dpos.rotate(m_camera_yaw);
            dpos *= m_camera_pos.y / 30.0f;
            m_camera_pos.x += dpos.x, m_camera_pos.z += dpos.y;
            m_camera_pos.x = nya_math::clamp(m_camera_pos.x, -location_size, location_size);
            m_camera_pos.z = nya_math::clamp(m_camera_pos.z, -location_size, location_size);
        }
    }
    else if (btns.testFlag(Qt::LeftButton))
    {
        nya_math::vec2 dpos(x - m_mouse_x, y - m_mouse_y);
        dpos.rotate(m_camera_yaw);
        dpos *= m_camera_pos.y / 300.0f;
        if (shift)
            dpos *= 10.0f;

        if (m_mode == mode_edit)
        {
            for (auto &o: m_selection["objects"])
            {
                if (o >= m_objects.size())
                    continue;

                auto &obj = m_objects[o];
                obj.pos.x += dpos.x, obj.pos.z += dpos.y;
                obj.pos.y = m_location_phys.get_height(obj.pos.x, obj.pos.z, true);
            }

            for (auto &o: m_selection["paths"])
            {
                if (o >= m_paths.size())
                    continue;

                auto &pth = m_paths[o];
                for (auto &p: pth.points)
                {
                    p.x += dpos.x, p.z += dpos.y;
                    p.y = m_location_phys.get_height(p.x, p.z, true);
                }
            }

            if (!m_selection["player spawn"].empty())
            {
                m_player.pos.x += dpos.x, m_player.pos.z += dpos.y;
                m_player.pos.y = m_location_phys.get_height(m_player.pos.x, m_player.pos.z, true);
            }
        }
    }
    else if (alt)
    {
        const float add = -(y - m_mouse_y) * (shift ? 10.0f : 1.0f);
        lock_mouse = true;

        if (m_mode == mode_add || m_mode == mode_path)
            m_selected_add.y = nya_math::clamp(m_selected_add.y + add, 0.0f, 10000.0f);

        if (m_mode == mode_zone)
            m_zone_add.radius = nya_math::clamp(m_zone_add.radius + add, 1.0f, 10000.0f);

        if (m_mode == mode_edit)
        {
            for (auto &o: m_selection["objects"])
            {
                if (o < m_objects.size())
                    m_objects[o].y = nya_math::clamp(m_objects[o].y + add, 0.0f, 10000.0f);
            }

            if (!m_selection["player spawn"].empty())
                m_player.y = nya_math::clamp(m_player.y + add, 0.0f, 10000.0f);
        }
    }
    else if (shift)
    {
        const nya_math::angle_deg add = (y - m_mouse_y) * 4.0f;
        lock_mouse = true;

        if (m_mode == mode_add)
            m_selected_add.yaw = (m_selected_add.yaw + add).normalize();

        if (m_mode == mode_edit)
        {
            const float far_dist = 100000.0f;
            nya_math::vec3 vmin(far_dist, far_dist, far_dist), vmax(-far_dist, -far_dist, -far_dist);

            for (auto &o: m_selection["objects"])
            {
                if (o >= m_objects.size())
                    continue;

                m_objects[o].yaw = (m_objects[o].yaw + add).normalize();
                vmin = nya_math::vec3::min(vmin, m_objects[o].pos);
                vmax = nya_math::vec3::max(vmax, m_objects[o].pos);
            }

            for (auto &o: m_selection["paths"])
            {
                if (o >= m_paths.size())
                    continue;

                for (auto &p: m_paths[o].points)
                {
                    vmin = nya_math::vec3::min(vmin, p.xyz());
                    vmax = nya_math::vec3::max(vmax, p.xyz());
                }
            }

            if (!m_selection["player spawn"].empty())
            {
                m_player.yaw = (m_player.yaw + add).normalize();
                vmin = nya_math::vec3::min(vmin, m_player.pos);
                vmax = nya_math::vec3::max(vmax, m_player.pos);
            }

            auto c = vmin + (vmax - vmin) * 0.5;

            const nya_math::quat rot(nya_math::angle_deg(), add, 0);

            for (auto &o: m_selection["objects"])
            {
                if (o >= m_objects.size())
                    continue;

                m_objects[o].pos = c + rot.rotate(m_objects[o].pos - c);
            }

            for (auto &o: m_selection["paths"])
            {
                if (o >= m_paths.size())
                    continue;

                for (auto &p: m_paths[o].points)
                    p.xyz() = c + rot.rotate(p.xyz() - c);
            }

            if (!m_selection["player spawn"].empty())
                m_player.pos = c + rot.rotate(m_player.pos - c);
        }
    }

    if (lock_mouse)
    {
        QPoint glob = mapToGlobal(QPoint(m_mouse_x, m_mouse_y));
        clearFocus();
        QCursor::setPos(glob);
        setFocus();
    }
    else
        m_mouse_x = x, m_mouse_y = y;

    update();
}
void Water::UpdateWater()
{
    if (!m_water_visible || !m_render_cam)
        return;

    if (m_waterplane_node)
    {
        Vector3 cameraPos(m_render_cam->getPosition().x, m_water_height, m_render_cam->getPosition().z);
        Vector3 sightPos(cameraPos);

        Ray lineOfSight(m_render_cam->getPosition(), m_render_cam->getDirection());
        Plane waterPlane(Vector3::UNIT_Y, Vector3::UNIT_Y * m_water_height);

        std::pair<bool, Real> intersection = lineOfSight.intersects(waterPlane);

        if (intersection.first && intersection.second > 0.0f)
            sightPos = lineOfSight.getPoint(intersection.second);

        Real offset = std::min(cameraPos.distance(sightPos), std::min(m_map_size.x, m_map_size.z) * 0.5f);

        Vector3 waterPos = cameraPos + (sightPos - cameraPos).normalisedCopy() * offset;
        Vector3 bottomPos = Vector3(waterPos.x, m_bottom_height, waterPos.z);

        if (waterPos.distance(m_waterplane_node->getPosition()) > 200.0f || m_waterplane_force_update_pos)
        {
            m_waterplane_node->setPosition(Vector3(waterPos.x, m_water_height, waterPos.z));
            m_bottomplane_node->setPosition(bottomPos);
            m_waterplane_force_update_pos = false; //Happens only once
        }
        if (RoR::App::gfx_water_waves.GetActive() && RoR::App::mp_state.GetActive() == RoR::MpState::DISABLED)
            this->ShowWave(m_waterplane_node->getPosition());
    }

    m_frame_counter++;
    if (App::gfx_water_mode.GetActive() == GfxWaterMode::FULL_FAST)
    {
        if (m_frame_counter % 2)
        {
            m_reflect_cam->setOrientation(m_render_cam->getOrientation());
            m_reflect_cam->setPosition(m_render_cam->getPosition());
            m_reflect_cam->setFOVy(m_render_cam->getFOVy());
            m_reflect_rtt_target->update();
        }
        else
        {
            m_refract_cam->setOrientation(m_render_cam->getOrientation());
            m_refract_cam->setPosition(m_render_cam->getPosition());
            m_refract_cam->setFOVy(m_render_cam->getFOVy());
            m_refract_rtt_target->update();
        }
    }
    else if (App::gfx_water_mode.GetActive() == GfxWaterMode::FULL_HQ)
    {
        m_reflect_cam->setOrientation(m_render_cam->getOrientation());
        m_reflect_cam->setPosition(m_render_cam->getPosition());
        m_reflect_cam->setFOVy(m_render_cam->getFOVy());
        m_reflect_rtt_target->update();
        m_refract_cam->setOrientation(m_render_cam->getOrientation());
        m_refract_cam->setPosition(m_render_cam->getPosition());
        m_refract_cam->setFOVy(m_render_cam->getFOVy());
        m_refract_rtt_target->update();
    }
    else if (App::gfx_water_mode.GetActive() == GfxWaterMode::REFLECT)
    {
        m_reflect_cam->setOrientation(m_render_cam->getOrientation());
        m_reflect_cam->setPosition(m_render_cam->getPosition());
        m_reflect_cam->setFOVy(m_render_cam->getFOVy());
        m_reflect_rtt_target->update();
    }
}
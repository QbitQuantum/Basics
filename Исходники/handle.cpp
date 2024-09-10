bool handle::getIsPointInside(ofVec2f t_mouse) {
    return t_mouse.distance(m_posC) <= m_radius;
}
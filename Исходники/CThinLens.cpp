CVector3D CThinLens::Ray_Direction(CPoint2D _sp, CPoint2D _lp) const {
    CVector3D direction;
    CPoint2D p;
    p.x = _sp.x * m_f / m_d;
    p.y = _sp.y * m_f / m_d;

    direction = (p.x - _lp.x) * m_u + (p.y - _lp.y) * m_v - m_f * m_w;
    direction.Normalize();

    return direction;
}
void TransformState::flattenWithTransform(const TransformationMatrix& t)
{
    if (m_direction == ApplyTransformDirection) {
        m_lastPlanarPoint = t.mapPoint(m_lastPlanarPoint);
        if (m_mapQuad)
            m_lastPlanarQuad = t.mapQuad(m_lastPlanarQuad);
    } else {
        TransformationMatrix inverseTransform = t.inverse();
        m_lastPlanarPoint = inverseTransform.projectPoint(m_lastPlanarPoint);
        if (m_mapQuad)
            m_lastPlanarQuad = inverseTransform.projectQuad(m_lastPlanarQuad);
    }

    // We could throw away m_accumulatedTransform if we wanted to here, but that
    // would cause thrash when traversing hierarachies with alternating
    // preserve-3d and flat elements.
    if (m_accumulatedTransform)
        m_accumulatedTransform->makeIdentity();
    m_accumulatingTransform = false;
}
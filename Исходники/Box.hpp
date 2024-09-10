    /**
    * @brief Box3D general constructor
    * @param center_ The center of the box
    * @param x_base_ Firsr axis of the base
    * @param y_base_ Second axis of the base
    * @param sizes_ Size of the box
    */
    Box3D (const Vector3D& center_, const Vector3D &x_base_, const Vector3D &y_base_, const Vector3D &sizes_) : m_center (center_), m_extent(sizes_*0.5f) {
        m_axis[0] = x_base_.normalize();
        m_axis[1] = y_base_.normalize();
        m_axis[2] = m_axis[0].cross_product(m_axis[1]);
        m_axis[1] = m_axis[0].cross_product(m_axis[2]);

    }
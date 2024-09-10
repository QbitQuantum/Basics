    static void lookAt(const vec3<Type>& eye, const vec3<Type>& center, const vec3<Type>& up)
    {
        const vec3<Type> forward = (center - eye).normalized();
        const vec3<Type> side = forward.cross(up).normalized();
        const vec3<Type> upVector = side.cross(forward);

        matrix4<Type> m;
        m.m_data[0][0] = side.x();
        m.m_data[1][0] = side.y();
        m.m_data[2][0] = side.z();
        m.m_data[3][0] = -side.dot(eye);
        m.m_data[0][1] = upVector.x();
        m.m_data[1][1] = upVector.y();
        m.m_data[2][1] = upVector.z();
        m.m_data[3][1] = -upVector.dot(eye);
        m.m_data[0][2] = -forward.x();
        m.m_data[1][2] = -forward.y();
        m.m_data[2][2] = -forward.z();
        m.m_data[3][2] = -forward.dot(eye);
        m.m_data[0][3] = 0;
        m.m_data[1][3] = 0;
        m.m_data[2][3] = 0;
        m.m_data[3][3] = 1;

        return m;
    }
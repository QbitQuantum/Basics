    void Evaluate()
    {
        float frame = GetFrame()->GetValue();

        int count = m_keys.GetCount();

        if (frame <= m_keys[0].m_frame) {
            //
            // Before first key
            //

            //  , add a SetRotate(const Quaternion&) to Matrix

            Vector vec;
            float angle = m_keys[0].m_quat.GetRotation(vec);
            GetValueInternal().SetRotate(vec, angle);
        } else if (frame >= m_keys[count - 1].m_frame) {
            //
            // After last key
            //

            Vector vec;
            float angle = m_keys[count - 1].m_quat.GetRotation(vec);
            GetValueInternal().SetRotate(vec, angle);
        } else {
            //
            // Between two keys
            //

            int index = 0;

            while (frame > m_keys[index + 1].m_frame) {
                index++;
            }

            float interpolant = (frame - m_keys[index].m_frame) / (m_keys[index + 1].m_frame - m_keys[index].m_frame);

            Quaternion quat = Slerp(m_keys[index].m_quat, m_keys[index + 1].m_quat, interpolant);
            Vector vec;
            float angle = quat.GetRotation(vec);
            GetValueInternal().SetRotate(vec, angle);
        }
    }
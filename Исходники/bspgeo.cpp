    float GetRadius(const Matrix& mat)
    {
        float radius = 0;
        int count = m_vvertex.GetCount();
        for(int index = 0; index < count; index++) {
            Vector vec = mat.Transform(m_vvertex[index].GetPosition());
            radius = max(radius, vec.Length());
        }

        return radius;
    }
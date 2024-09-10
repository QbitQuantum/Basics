void GLMesh::CalculateNormals()
{
    for (unsigned int i = 0; i < _iCount - 2; i++)
    {
        GLVertex p1 = _vertices[_indices[i+0]];
        GLVertex p2 = _vertices[_indices[i+1]];
        GLVertex p3 = _vertices[_indices[i+2]];
        Vector3D normal = (p2.Position - p1.Position) * (p3.Position - p1.Position);
        normal.Normalize();
        if (i%2) normal *= -1;

        _vertices[_indices[i+0]].Normal += normal;
        _vertices[_indices[i+1]].Normal += normal;
        _vertices[_indices[i+2]].Normal += normal;
    }

    for (unsigned int v=0; v< _vCount - 2; v++)
    {
        _vertices[v].Normal.Normalize();
    }
}
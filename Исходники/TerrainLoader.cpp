void CalculateNormals(vector<VertexPosNormTanTex>& vertices, const vector<DWORD>& indices)
{
    DWORD numTris = indices.size() / 3;
    for (DWORD i = 0; i < numTris; ++i)
    {
        Vector3 normal;

        const Vector3& pos1 = vertices[indices[i * 3]].position, 
                       pos2 = vertices[indices[i * 3 + 1]].position, 
                       pos3 = vertices[indices[i * 3 + 2]].position;

        Vector3 v1 = pos2 - pos1;
        Vector3 v2 = pos3 - pos1;
        v1.Normalize();
        v2.Normalize();
        Vector3 cross = v1.Cross(v2);
        cross.Normalize();

        /*vertices[indices[i * 3 + 0]].normal += cross;
        vertices[indices[i * 3 + 1]].normal += cross;
        vertices[indices[i * 3 + 2]].normal += cross;*/

        if (vertices[indices[i * 3 + 0]].normal == Vector3::Zero)
            vertices[indices[i * 3 + 0]].normal = cross;
        else
        {
            vertices[indices[i * 3 + 0]].normal += cross;
            vertices[indices[i * 3 + 0]].normal.Normalize();
        }

        if (vertices[indices[i * 3 + 1]].normal == Vector3::Zero)
            vertices[indices[i * 3 + 1]].normal = cross;
        else
        {
            vertices[indices[i * 3 + 1]].normal += cross;
            vertices[indices[i * 3 + 1]].normal.Normalize();
        }

        if (vertices[indices[i * 3 + 2]].normal == Vector3::Zero)
            vertices[indices[i * 3 + 2]].normal = cross;
        else
        {
            vertices[indices[i * 3 + 2]].normal += cross;
            vertices[indices[i * 3 + 2]].normal.Normalize();
        }
    }
    /*for_each(vertices.begin(), vertices.end(), [](VertexPosNormTanTex& vpnt)
    {
        vpnt.normal.Normalize();
    });*/
}
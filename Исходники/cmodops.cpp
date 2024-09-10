Vector3f
averageFaceVectors(const vector<Face>& faces,
                   uint32 thisFace,
                   uint32* vertexFaces,
                   uint32 vertexFaceCount,
                   float cosSmoothingAngle)
{
    const Face& face = faces[thisFace];

    Vector3f v = Vector3f(0, 0, 0);
    for (uint32 i = 0; i < vertexFaceCount; i++)
    {
        uint32 f = vertexFaces[i];
        float cosAngle = face.normal.dot(faces[f].normal);
        if (f == thisFace || cosAngle > cosSmoothingAngle)
            v += faces[f].normal;
    }

    if (v.squaredNorm() == 0.0f)
        v = Vector3f(1.0f, 0.0f, 0.0f);
    else
        v.normalize();

    return v;
}
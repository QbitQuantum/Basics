_Use_decl_annotations_
void BIH::Query(const AABB& test, uint32_t* numTriangles)
{
    *numTriangles = 0;
    if (!test.Intersects(_bounds))
    {
        return;
    }

    Query(test, _root, numTriangles);
}
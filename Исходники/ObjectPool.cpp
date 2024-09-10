irr::scene::SAnimatedMesh* ObjectPool::readMySimpleObject(const std::string& meshFilename, float scale)
{
    FILE* f;
    unsigned int numOfVertices, numOfPols;
    float x,y,z,tu,tv;
    irr::u32 r,g,b;
    int ret, index;
    irr::u32 verInd;
    irr::video::S3DVertex vtx;
    vtx.Color.set(255,255,255,255);
    vtx.Normal.set(0,1,0);

#ifdef MSO_DEBUG
    printf("Read my simple object: %s\n", name);
#endif
    
    errno_t error = fopen_s(&f, meshFilename.c_str(), "r");
    
    if (error)
    {
        printf("my simple object file unable to open: %s\n", meshFilename.c_str());
        return 0;
    }
    
    irr::scene::SMeshBuffer* buffer = new irr::scene::SMeshBuffer();
    irr::scene::SMesh* mesh = new irr::scene::SMesh();
    
#ifdef MSO_DEBUG
    printf("read vertices\n");
#endif    
    ret = fscanf_s(f, "vertices\n%u\n", &numOfVertices);
    if (ret <= 0)
    {
       printf("error reading %s ret %d errno %d\n", meshFilename.c_str(), ret, errno);
       fclose(f);
       return 0;
    }

#ifdef MSO_DEBUG
    printf("vertices: %u\n", numOfVertices);
#endif    

    for (unsigned int ind = 0; ind < numOfVertices; ind++)
    {
#ifdef MSO_DEBUG
    printf("read a vertex\n");
#endif    
        ret = fscanf_s(f, "%d %f %f %f %f %f %u %u %u\n", &index, &x, &y, &z, &tu, &tv, &r, &g, &b);
        if (ret <= 0)
        {
           printf("error reading %s ret %d errno %d\n", meshFilename.c_str(), ret, errno);
           fclose(f);
           return 0;
        }
#ifdef MSO_DEBUG
    printf("vertex read done\n");
#endif    
        vtx.Pos.X = x*scale;
        vtx.Pos.Z = z*scale;
        vtx.Pos.Y = y*scale;
        vtx.TCoords.X = tu;
        vtx.TCoords.Y = tv;
        vtx.Color.set(255,r,g,b);
        buffer->Vertices.push_back(vtx);
    }
#ifdef MSO_DEBUG
    printf("read polygons number\n");
#endif    
    ret = fscanf_s(f, "polygons\n%u\n", &numOfPols);
    if (ret <= 0)
    {
       printf("error reading %s ret %d errno %d\n", meshFilename.c_str(), ret, errno);
       fclose(f);
       return 0;
    }
#ifdef MSO_DEBUG
    printf("polygons: %u\n", numOfPols);
#endif    
    for (unsigned int ind = 0; ind < numOfPols*3; ind++)
    {
#ifdef MSO_DEBUG
    printf("read a poly part\n");
#endif    
        ret = fscanf_s(f, "%u\n", &verInd);
        if (ret <= 0)
        {
           printf("error reading %s ret %d errno %d\n", meshFilename.c_str(), ret, errno);
           fclose(f);
           return 0;
        }
#ifdef MSO_DEBUG
    printf("read a poly part done\n");
#endif    
        if (verInd >= numOfVertices)
        {
           printf("!!!!! verInd >= numOfVertices: %d > %u\n", verInd, numOfVertices);
        }
        buffer->Indices.push_back(verInd);
    }

#ifdef MSO_DEBUG
    printf("renormalize\n");
#endif    
    for (irr::s32 ind=0; ind<(irr::s32)buffer->Indices.size(); ind+=3)
    {
        irr::core::plane3d<irr::f32> p(
            buffer->Vertices[buffer->Indices[ind+0]].Pos,
            buffer->Vertices[buffer->Indices[ind+1]].Pos,
            buffer->Vertices[buffer->Indices[ind+2]].Pos);
        p.Normal.normalize();

        buffer->Vertices[buffer->Indices[ind+0]].Normal = p.Normal;
        buffer->Vertices[buffer->Indices[ind+1]].Normal = p.Normal;
        buffer->Vertices[buffer->Indices[ind+2]].Normal = p.Normal;
    }
#ifdef MSO_DEBUG
    printf("renormalize done\n");
#endif    
   
    buffer->recalculateBoundingBox();

    irr::scene::SAnimatedMesh* animatedMesh = new irr::scene::SAnimatedMesh();
    mesh->addMeshBuffer(buffer);
    mesh->recalculateBoundingBox();
    animatedMesh->addMesh(mesh);
    animatedMesh->recalculateBoundingBox();

    mesh->drop();
    buffer->drop();

    fclose(f);
#ifdef MSO_DEBUG
    printf("read done return %p\n", animatedMesh);
#endif    

    return animatedMesh;
}
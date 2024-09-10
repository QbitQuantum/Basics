LVEDRENDERINGENGINE_API bool __stdcall LvEd_FrustumPick(ObjectGUID renderSurface, float viewxform[], float projxform[],float* rect, HitRecord** hits, int* count)
{
    ErrorHandler::ClearError();
    *hits = 0;
    *count = 0;
    float w = rect[2];
    float h = rect[3];

    if(w == 0 || h == 0)
    {
        return false;
    }


    // init camera.
    Matrix view = viewxform;
    Matrix proj = projxform;
    RenderContext::Inst()->Cam().SetViewProj(view,proj);  
    
    // same code used for rendering.
    s_engineData->pickCollector.ClearLists();
    s_engineData->pickCollector.SetFlags( RenderContext::Inst()->State()->GetGlobalRenderFlags() );

    s_engineData->GameLevel->GetRenderables(&s_engineData->pickCollector, RenderContext::Inst());
   
    RenderSurface* pRenderSurface = reinterpret_cast<RenderSurface*>(renderSurface);

    float3 corners[8];
    float x0 = rect[0];
    float y0 = rect[1];
    float x1 = x0 + w;
    float y1 = y0 + h;       
           
    Matrix viewProj = view * proj;
    Matrix invWVP; // inverse of world view projection matrix.
    s_engineData->HitRecords.clear();
    float3 zeroVector(0,0,0);
    Frustum fr; // frustum in local space.
    for(auto it = s_engineData->pickCollector.GetList().begin(); it != s_engineData->pickCollector.GetList().end(); it++)
    {
        RenderableNode& r = (*it);
        if(r.mesh == NULL) continue;

        invWVP = r.WorldXform * viewProj;
        invWVP.Invert();

        corners[0] = pRenderSurface->Unproject(float3(x0,y1,0),invWVP);
        corners[4] = pRenderSurface->Unproject(float3(x0,y1,1),invWVP);

        corners[1] = pRenderSurface->Unproject(float3(x1,y1,0),invWVP);
        corners[5] = pRenderSurface->Unproject(float3(x1,y1,1),invWVP);

        corners[2] = pRenderSurface->Unproject(float3(x1,y0,0),invWVP);
        corners[6] = pRenderSurface->Unproject(float3(x1,y0,1),invWVP);

        corners[3] = pRenderSurface->Unproject(float3(x0,y0,0),invWVP);
        corners[7] = pRenderSurface->Unproject(float3(x0,y0,1),invWVP);
        fr.InitFromCorners(corners);

        int test = FrustumAABBIntersect(fr,r.mesh->bounds);                
        if(test)
        {
            if(test == 1 
                && r.GetFlag(RenderableNode::kTestAgainstBBoxOnly) == false
                && r.mesh != NULL 
                && r.mesh->primitiveType == PrimitiveType::TriangleList)
            {
                Mesh* mesh = r.mesh;
               
                Triangle tr;                
                bool triHit = FrustumMeshIntersect(fr, 
                     &mesh->pos[0],
                   (uint32_t)mesh->pos.size(),
                   &mesh->indices[0],
                   (uint32_t)mesh->indices.size());
                
                if( triHit == false) continue;               
            }
            
            HitRecord hit;
            hit.objectId = r.objectId;
            hit.index = 0;
            hit.hitPt = zeroVector;
            hit.normal = zeroVector;
            hit.nearestVertex = zeroVector;
            hit.distance = 0;
            hit.hasNormal = false;
            hit.hasNearestVertex = false;
            s_engineData->HitRecords.push_back(hit);
        }
    }

    // return the results to the C#. 
    if(s_engineData->HitRecords.size() > 0)
    {
        *hits = &s_engineData->HitRecords[0];
        *count = (int)s_engineData->HitRecords.size();
    }
    return *count > 0;
}
void CurveGob::Update(const FrameTime& fr, UpdateTypeEnum updateType)
{
    bool boundDirty = m_boundsDirty;
    super::Update(fr,updateType);
    m_boundsDirty = boundDirty;

    if(!m_boundsDirty) return;

    m_mesh.pos.clear();    
    if(m_needsRebuild)
    {        
        SAFE_DELETE(m_mesh.vertexBuffer);
    }

    if(m_points.size()<2)
    {
        m_localBounds = AABB(float3(-0.5f,-0.5f,-0.5f), float3(0.5f,0.5f,0.5f));
        UpdateWorldAABB();       
        return;
    }

    // compute local bounds.
    m_localBounds =  m_points[0]->GetLocalBounds();
    m_localBounds.Transform(m_points[0]->GetTransform());
    for( auto it = m_points.begin(); it != m_points.end(); ++it)
    {
        (*it)->Update(fr,updateType);
        AABB local = (*it)->GetLocalBounds();
        local.Transform((*it)->GetTransform());
        m_localBounds.Extend(local);
    }

    // compute world bound.
    float3 min,max;
    min = m_points[0]->GetBounds().Min();
    max = m_points[0]->GetBounds().Max();
    for( auto it = m_points.begin(); it != m_points.end(); ++it)
    {
        min = minimize(min, (*it)->GetBounds().Min());
        max = maximize(max, (*it)->GetBounds().Max());
    }
    m_bounds = AABB(min,max);                    
    m_boundsDirty = false;
    std::vector<float3> verts;
    switch(m_type)
    {
    default:
        Logger::Log(OutputMessageType::Error, "Invalid curve type, '%d'\n", m_type);
        // fall through and just pretend it is Linear

    case Linear:
        {// add all the normal control point positions
            
            for(auto it = m_points.begin(); it != m_points.end(); ++it)
            {
                float3 vert = float3(&(*it)->GetTransform().M41);
                verts.push_back(vert);
            }
            if(m_closed)
            {
                verts.push_back(verts[0]);
            }
            break;
        }
    case CatmullRom:
        {          
            std::vector<float3> points;
            //// since catmull-rom interpolation requires additional points, we want to calculate
            //// to 'fake' points to be the endpoints. That way our line will exists for all the
            //// actual control points.
            size_t size = m_points.size();
            if(m_closed)
            {
                // add the last point before others for consistent interpolation
                points.push_back(float3(&m_points[size-1]->GetTransform().M41));
            }
            else
            {
                // add an extra point in front of the 1st control point for interpolation
                float3 p1(&m_points[0]->GetTransform().M41);
                float3 p2(&m_points[1]->GetTransform().M41);
                float3 delta = p1 - p2; // from p2 to p1
                points.push_back(p1 + delta);
            }

            // add all normal control point positions
            for(auto it = m_points.begin(); it != m_points.end(); ++it)
            {
                points.push_back(float3(&(*it)->GetTransform().M41));
            }

            if(m_closed)
            {
                // add first and second points for consistent interpolation
                points.push_back(&m_points[0]->GetTransform().M41);
                points.push_back(&m_points[1]->GetTransform().M41);
            }
            else
            {
                // add an extra point in after of the last control point for interpolation
                float3 p1 = points[size-1];
                float3 p2 = points[size-2];
                float3 delta = p1 - p2; // from p2 to p1
                points.push_back(p1 + delta);
            }

            // Interpolate                        
            size_t sz = points.size() - 2;               
            for(unsigned int index = 1; index < sz; index++)
            {       
                float3 p0 = points[index-1];
                float3 p1 = points[index];
                float3 p2 = points[index+1];
                float3 p3 = points[index+2];

                for(int i = 0; i < m_steps; ++i)
                {                    
                    float s = (float)i / (float)m_steps;                    
                    verts.push_back(Vec3CatmullRom(p0,p1,p2,p3,s));
                }                
            }    
            verts.push_back(points[sz]);           
            break;
        }
    case Bezier:
        {
            std::vector<float3> points;
             // add all normal control point positions
            for(auto it = m_points.begin(); it != m_points.end(); ++it)
            {
                points.push_back(float3(&(*it)->GetTransform().M41));
            }

            BezierSpline spline(&points[0],(int)points.size(),m_closed);

            for(int i = 0;  i < spline.CurveCount(); i++)
            {
                const BezierCurve& curve = spline.GetCurveAt(i);
                for(int k = 0; k < m_steps; k++)
                {
                    float s = (float)k / (float)m_steps;
                    verts.push_back(curve.Eval(s));                                    
                }
            }
            // Handle last point
            if (m_closed && m_points.size() > 2)
                verts.push_back(points[0]);
            else 
                verts.push_back(points[points.size()-1]);
            break;        
        }
    }
    
    for(auto it = verts.begin(); it != verts.end(); it++)
    {
        m_mesh.pos.push_back(*it);
    }
    m_mesh.ComputeBound();
    if(m_needsRebuild)
    {                       
        m_mesh.vertexBuffer = GpuResourceFactory::CreateVertexBuffer(&verts[0], VertexFormat::VF_P, (uint32_t)verts.size(), BufferUsage::DYNAMIC);
    }
    else
    {
        ID3D11DeviceContext* context = gD3D11->GetImmediateContext();
        assert(m_mesh.vertexBuffer != NULL);        
        m_mesh.vertexBuffer->Update(context,&verts[0],(uint32_t)verts.size());
    }    
    
    m_needsRebuild = false;    
}
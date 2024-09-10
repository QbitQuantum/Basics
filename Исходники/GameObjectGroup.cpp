    void GameObjectGroup::Update(const FrameTime& fr, UpdateTypeEnum updateType)
    {
        bool boundDirty = m_boundsDirty;
        super::Update(fr,updateType);
        m_boundsDirty = boundDirty;
        for( auto it = m_children.begin(); it != m_children.end(); ++it)
        {
            (*it)->Update(fr,updateType);
        }


        // Update bounds
        if(m_boundsDirty)
        {            
            bool usechildbounds = false;
            AABB childbounds; // default ctor will set initial value of min and max.
            // merge bounds for the the visibile children.
            for (auto it = m_children.begin(); it != m_children.end(); ++it)
            {
                if( (*it)->IsVisible())
                {                    
                    AABB local = (*it)->GetLocalBounds();
                    local.Transform((*it)->GetTransform());
                    childbounds.Extend( local );
                    usechildbounds = true;
                }
            }
                 
            // set local bounds 
            m_localBounds = usechildbounds ? childbounds : AABB(float3(-0.5f,-0.5f,-0.5f), float3(0.5f,0.5f,0.5f));
            UpdateWorldAABB();                      
        }
    }
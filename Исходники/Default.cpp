bool Default::forEachEntity(Core::Slackgine* sg, Core::Entity* entity)
{
    // Manage the entity stack
    if ( mEntityStack.size() > 0 && mEntityStack.back() != entity->getParent() )
        mEntityStack.pop_back();
    mEntityStack.push_back(entity);
    Transform entityTransform = mEntityStack.getTransform ();
    
    // Render it!
    if ( entity->getModel() != 0 )
    {
        l3m::Scene* sce = l3m::Util::findScene ( entity->getModel() );
        if ( sce != 0 )
        {
            // For each geometry...
            for ( l3m::Scene::NodesVector::iterator iter = sce->geometryNodes().begin();
                iter != sce->geometryNodes().end();
                ++iter )
            {
                l3m::Scene::Node& node = *iter;
                Transform transform = entityTransform * node.transform;
                sg->getRenderer()->render( node.geometry, transform, false, getMeshHandler() );

                // Enqueue transparent stuff for later
                for ( Geometry::meshNodeVector::iterator iter2 = node.geometry->m_meshNodes.begin();
                      iter2 != node.geometry->m_meshNodes.end();
                      ++iter2 )
                {
                    Mesh* mesh = (*iter2).mesh;
                    if ( mesh->material() != 0 && mesh->material()->isTransparent() == true )
                    {
                        Vector3 pos = m_matLookAt * transform.translation();
                        m_listTransparencies.push_back(DeferredMesh(node.geometry, mesh, pos.length(), transform));
                    }
                }
            }
        }
    }
    
    return true;
}
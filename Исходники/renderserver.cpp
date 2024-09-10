void
RenderServer::RenderScene(boost::shared_ptr<BaseNode> node, unsigned pass)
{
    boost::shared_ptr<RenderNode> renderNode = shared_dynamic_cast<RenderNode>(node);
    if (renderNode.get() != 0 &&
        !renderNode->IsVisible())
      return;
    
    if (renderNode.get() != 0 &&
        ((pass == 0 && !renderNode->IsTransparent()) || (pass == 1 && renderNode->IsTransparent()))
       )
        {
            glPushMatrix();

            if (mEnablePicking)
                {
                    // assign an OpenGL name to the RenderNode
                    GLuint name = (mNextName++);
                    mNameMap[name] = renderNode;
                    glPushName(name);
                }

            glMultMatrixf(node->GetWorldTransform().m);

            renderNode->RenderInternal();

            if (mEnablePicking)
                {
                    // pop name from OpenGL name stack
                    glPopName();
                }

            if (mEnablePicking)
                {
                    // pop name from OpenGL name stack
                    glPopName();
                }

            glPopMatrix();
        }

    // traverse the the hierarchy
    for (TLeafList::iterator i = node->begin(); i!= node->end(); ++i)
    {
        boost::shared_ptr<BaseNode> node = shared_dynamic_cast<BaseNode>(*i);
        if (node.get() == 0)
        {
            continue;
        }

        RenderScene(node, pass);
    }
}
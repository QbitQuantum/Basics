    Node::~Node()
    {
#if FZ_GL_SHADERS
        setFilter(NULL);
        setGLProgram(nullptr);
#endif
        if(p_camera)
            delete p_camera;
        
        Node *child;
        FZ_LIST_FOREACH_MUTABLE(m_children, child)
        {
            child->setParent(NULL);
            child->release();
        }
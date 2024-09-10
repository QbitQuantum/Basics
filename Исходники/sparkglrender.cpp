SparkGLRender::RenderSelectionContext::RenderSelectionContext(shared_ptr<BaseNode> node)
{
    assert(node.get() != 0);
    glPushMatrix();
    glMultMatrixf(node->GetWorldTransform().m);
}
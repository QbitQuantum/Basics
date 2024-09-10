void GraphDrawer::drawEdges()
{
    if (changed)
    {
        //ci::app::console() << "Redrawing edges" << std::endl;
        ci::gl::ScopedFramebuffer scpFbEdge(edgeFbo);
        ci::gl::ScopedViewport scpVpEdge(edgeFbo->getSize());
        
        ci::gl::pushMatrices();
        ci::gl::setMatricesWindow(edgeFbo->getSize());
        ci::gl::clear(ci::ColorA(0, 0, 0, 0.0f));

        for (int nodeIdx = 0; nodeIdx < g->getNodeCount(); ++nodeIdx)
        {
            auto &node = g->getNode(nodeIdx);
            for (auto &edge : node)
            {
                drawEdge(edge.from, edge.to, colorScheme.edgeColor, settings.edgeWidth);
            }
        }
        ci::gl::popMatrices();
    }
    ci::gl::draw(edgeFbo->getColorTexture());
}
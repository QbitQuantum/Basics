void CURRENT_CLASS::apply(osg::Transform &transform)
{
    if(shouldContinueTraversal(transform))
    {
        // Compute transform for current node
        osg::Matrix currMatrix = _viewMatrices.back();
        bool pushMatrix = transform.computeLocalToWorldMatrix(currMatrix,this);

        if(pushMatrix)
        {
            // Store the new modelview matrix and view frustum
            _viewMatrices.push_back(currMatrix);
            pushLocalFrustum();
        }

        ++_currentDepth;
        traverse(transform);
        --_currentDepth;

        if(pushMatrix)
        {
            // Restore the old modelview matrix and view frustum
            _localFrusta.pop_back();
            _bbCorners.pop_back();
            _viewMatrices.pop_back();
        }
    }
}
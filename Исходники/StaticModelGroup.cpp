void StaticModelGroup::OnWorldBoundingBoxUpdate()
{
    // Update transforms and bounding box at the same time to have to go through the objects only once
    unsigned index = 0;

    BoundingBox worldBox;

    for (unsigned i = 0; i < instanceNodes_.Size(); ++i)
    {
        Node* node = instanceNodes_[i];
        if (!node || !node->IsEnabled())
            continue;
        
        const Matrix3x4& worldTransform = node->GetWorldTransform();
        worldTransforms_[index++] = worldTransform;
        worldBox.Merge(boundingBox_.Transformed(worldTransform));
    }
    
    worldBoundingBox_ = worldBox;

    // Store the amount of valid instances we found instead of resizing worldTransforms_. This is because this function may be 
    // called from multiple worker threads simultaneously
    numWorldTransforms_ = index;
}
void AnimatedModel::UpdateBoneBoundingBox()
{
    if (skeleton_.GetNumBones())
    {
        // The bone bounding box is in local space, so need the node's inverse transform
        boneBoundingBox_.Clear();
        Matrix3x4 inverseNodeTransform = node_->GetWorldTransform().Inverse();

        const Vector<Bone>& bones = skeleton_.GetBones();
        for (Vector<Bone>::ConstIterator i = bones.Begin(); i != bones.End(); ++i)
        {
            Node* boneNode = i->node_;
            if (!boneNode)
                continue;

            // Use hitbox if available. If not, use only half of the sphere radius
            /// \todo The sphere radius should be multiplied with bone scale
            if (i->collisionMask_ & BONECOLLISION_BOX)
                boneBoundingBox_.Merge(i->boundingBox_.Transformed(inverseNodeTransform * boneNode->GetWorldTransform()));
            else if (i->collisionMask_ & BONECOLLISION_SPHERE)
                boneBoundingBox_.Merge(Sphere(inverseNodeTransform * boneNode->GetWorldPosition(), i->radius_ * 0.5f));
        }
    }

    boneBoundingBoxDirty_ = false;
    worldBoundingBoxDirty_ = true;
}
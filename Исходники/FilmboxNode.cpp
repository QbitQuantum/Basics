        KFbxXMatrix FilmboxNode::GetLocalTransform( int frame ) const
        {
            KFbxXMatrix world_transform  = GetWorldTransform( frame );
            KFbxXMatrix parent_transform = GetParentWorldTransform( frame );
            KFbxXMatrix world_to_local   = parent_transform.Inverse();
            KFbxXMatrix local_transform  = world_to_local * world_transform;

            return local_transform;
        }
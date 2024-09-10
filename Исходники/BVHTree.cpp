bool BVHTree::intersectHelp(shared_ptr<Object> avoid, const Vector3f& pos, const Vector3f& ray, BVHNode *node, HitRecord *hitRecord)
{
    if (node == NULL) { return false; }

    if ((node->bb)->intersection(pos, ray)) {
        // Check if leaf
        if (node->left == NULL && node->right == NULL) {

            shared_ptr<Object> object = node->bb->getObject(); 
            
            if (object != avoid) {
                
                Matrix4f inv = object->getInvXForm();
                
                Vector4f modelPos = inv * Vector4f(pos(0), pos(1), pos(2), 1);
                Vector4f modelRay = inv * Vector4f(ray(0), ray(1), ray(2), 0);
                
                float t = object->intersection(modelPos.head(3), modelRay.head(3));

                if (t >= 0) {
                    *hitRecord = HitRecord(t, object);
                    return HIT;
                } 
            }
              
            return !HIT;

        } else {
            // Either a node is a leaf, or it has two children
             HitRecord lHR, rHR;
             bool lHit, rHit;
             
             lHit = intersectHelp(avoid, pos, ray, node->left, &lHR);
             rHit = intersectHelp(avoid, pos, ray, node->right, &rHR);
             
             if (!lHit && !rHit) { 
                 return !HIT; 
             } else if (!lHit) { 
                 *hitRecord = rHR; 
             } else if (!rHit) { 
                 *hitRecord = lHR; 
             } else {
                 *hitRecord = lHR.getT() < rHR.getT() ? lHR : rHR;
             }
             
             return HIT;    
        }
    }

    return !HIT;
}
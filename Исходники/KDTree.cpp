void KDTree::Node::buildNode(const KDTree& tree, int maxDepth)
{
    
    // Find the median plan
    Vec3Df n;
    if (boundingBox.getSize() == boundingBox.getWidth() ){
        n = Vec3Df (boundingBox.getMax()[0] - boundingBox.getMin()[0], 0.0, 0.0);
    } else if (boundingBox.getSize() == boundingBox.getHeight()){
        n = Vec3Df (0.0, boundingBox.getMax()[1] - boundingBox.getMin()[1], 0.0);
    } else{
        n = Vec3Df( 0.0, 0.0, boundingBox.getMax()[2] - boundingBox.getMin()[2]);
    }
    
    n.normalize();
    Vec3Df position = getMedianPoint(tree.getMesh(), n);;
    
    plan.n = n;
    plan.position = position;
    
    if (depth == maxDepth) {
        return;
    }
    
    //seperate triangles
    
    vector<int> leftIndexes, rightIndexes;
    for (int idx : triangleIndexes){
        
        const Triangle& t = tree.getMesh().getTriangles()[idx];
        
        const Vec3Df& a = tree.getMesh().getVertices()[ t.getVertex(0)].getPos();
        const Vec3Df& b = tree.getMesh().getVertices()[ t.getVertex(1)].getPos();
        const Vec3Df& c = tree.getMesh().getVertices()[ t.getVertex(2)].getPos();
        
        
        //regarder si tous les sommets sont du même côté du plan...
        if ( plan.isLeft(a) && plan.isLeft(b) && plan.isLeft(c) ){
            //Ils sont tous à gauche
            leftIndexes.push_back(idx);
            
        } else if( plan.isRight(a) && plan.isRight(b) && plan.isRight(c) ){
            //Ils sont tous à droite
            rightIndexes.push_back(idx);
        } else {
            // Le triangle doit être ajouté des deux côtés
            rightIndexes.push_back(idx);
            leftIndexes.push_back(idx);
        }
        
    }
    
    if(rightIndexes == leftIndexes)
        return;
    
    if (triangleIndexes.size() == rightIndexes.size() || triangleIndexes.size() == leftIndexes.size())
        return;
    
    
    if(rightIndexes.size() != 0){
        right_node = new KDTree::Node(rightIndexes, depth + 1, tree);
        right_node->buildNode(tree, maxDepth);
    }
    
    if(leftIndexes.size() != 0){
        left_node = new KDTree::Node(leftIndexes, depth + 1, tree);
        left_node->buildNode(tree, maxDepth);
    }
    
}
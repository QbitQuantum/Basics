void collisionTester::setTransformFromOF(ofMatrix4x4& mat, ofVec3f& s, btCollisionObject& obj){
    
    btTransform trans;
    trans.setFromOpenGLMatrix(mat.getPtr());
    obj.setWorldTransform(trans);
    obj.getCollisionShape()->setLocalScaling(btVector3(s.x, s.y, s.z));
}
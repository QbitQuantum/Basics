void rigidBodyNode::updateShape(const MPlug& plug, MDataBlock& data, float& collisionMarginOffset)
{
	MObject thisObject(thisMObject());
    MPlug plgCollisionShape(thisObject, ia_collisionShape);
    MObject update;
    //force evaluation of the shape
    plgCollisionShape.getValue(update);

   /* vec3f prevCenter(0, 0, 0);
    quatf prevRotation(qidentity<float>());
    if(m_rigid_body) {
        prevCenter = m_rigid_body->collision_shape()->center();
        prevRotation = m_rigid_body->collision_shape()->rotation();
    }*/

    collision_shape_t::pointer  collision_shape;
	
    if(plgCollisionShape.isConnected()) {
        MPlugArray connections;
        plgCollisionShape.connectedTo(connections, true, true);
        if(connections.length() != 0) {
            MFnDependencyNode fnNode(connections[0].node());
            if(fnNode.typeId() == collisionShapeNode::typeId) {
				collisionShapeNode *pCollisionShapeNode = static_cast<collisionShapeNode*>(fnNode.userNode());
				pCollisionShapeNode->setCollisionMarginOffset(collisionMarginOffset); //mb
                collision_shape = pCollisionShapeNode->collisionShape();
            } else {
                std::cout << "rigidBodyNode connected to a non-collision shape node!" << std::endl;
            }
        }
    }

	data.outputValue(ca_rigidBody).set(true);
    data.setClean(plug);
}
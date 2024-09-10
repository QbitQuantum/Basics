void getPrimitivesFromRSB(boost::shared_ptr<Primitive3DFloatSet> evPrimitiveSet){
  std::vector<Primitive3DFilter::Primitive3D> rsbPrimitives;
  for(int i = 0; i < evPrimitiveSet->primitives_size(); ++i) {
    Primitive3DFloat primitiveProto = evPrimitiveSet->primitives(i);
    Primitive3DFilter::PrimitiveType primitiveType = Primitive3DFilter::CUBE;
    Primitive3DFloat_PrimitiveType typeRST = primitiveProto.type();
    if(typeRST == Primitive3DFloat_PrimitiveType_CUBE)
        primitiveType = Primitive3DFilter::CUBE;
    else if(typeRST == Primitive3DFloat_PrimitiveType_SPHERE)
        primitiveType = Primitive3DFilter::SPHERE;
    else if(typeRST == Primitive3DFloat_PrimitiveType_CYLINDER)
        primitiveType = Primitive3DFilter::CYLINDER;
    Translation positionProto = primitiveProto.pose().translation();
    Vec primitivePosition(positionProto.x()*1000.0, positionProto.y()*1000.0, positionProto.z()*1000.0, 1);
    Rotation rotation = primitiveProto.pose().rotation();
    Primitive3DFilter::Quaternion primitiveOrientation(Vec3(rotation.qx(), rotation.qy(), rotation.qz()), rotation.qw());
    Vec primitiveScale(primitiveProto.scale().x()*1000.0, primitiveProto.scale().y()*1000.0, primitiveProto.scale().z()*1000.0, 1);
    Primitive3DFilter::Primitive3D primitive(primitiveType, primitivePosition, primitiveOrientation, primitiveScale, 0, primitiveProto.description());
    rsbPrimitives.push_back(primitive);
  }
  primitivesMutex.lock();
  primitives = rsbPrimitives;
  primitivesMutex.unlock();
}
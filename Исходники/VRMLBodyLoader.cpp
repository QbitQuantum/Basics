void VRMLBodyLoaderImpl::readSegmentNode(LinkInfo& iLink, VRMLProtoInstance* segmentNode, const Affine3& T)
{
    if(isVerbose) putMessage(string("Segment node ") + segmentNode->defName);
    
    /*
      Mass = Sigma mass 
      C = (Sigma mass * T * c) / Mass 
      I = Sigma(R * I * Rt + G)       
      R = Rotation matrix part of T   
      G = y*y+z*z, -x*y, -x*z, -y*x, z*z+x*x, -y*z, -z*x, -z*y, x*x+y*y    
      (x, y, z ) = T * c - C
    */

    VRMLProtoFieldMap& sf = segmentNode->fields;
    SegmentInfo iSegment;
    readVRMLfield(sf["mass"], iSegment.m);
    Vector3 c;
    readVRMLfield(sf["centerOfMass"], c);
    iSegment.c = T.linear() * c + T.translation();
    iLink.c = (iSegment.c * iSegment.m + iLink.c * iLink.m) / (iLink.m + iSegment.m);
    iLink.m += iSegment.m;
    
    Matrix3 I;
    readVRMLfield(sf["momentsOfInertia"], I);
    iLink.I.noalias() += T.linear() * I * T.linear().transpose();

    MFNode& childNodes = get<MFNode>(segmentNode->fields["children"]);
    ProtoIdSet acceptableProtoIds;
    acceptableProtoIds.set(PROTO_SURFACE);
    acceptableProtoIds.set(PROTO_DEVICE);
    readJointSubNodes(iLink, childNodes, acceptableProtoIds, T);

    SgNodePtr node = sgConverter.convert(segmentNode);
    if(node){
        if(T.isApprox(Affine3::Identity())){
            iLink.visualShape->addChild(node);
        } else {
            SgPosTransform* transform = new SgPosTransform(T);
            transform->addChild(node);
            iLink.visualShape->addChild(transform);
        }
    }
}
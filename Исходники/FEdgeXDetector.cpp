void FEdgeXDetector::preProcessFace(WXFace *iFace){
    Vec3r firstPoint = iFace->GetVertex(0)->GetVertex();
    Vec3r N = iFace->GetNormal();

    // Compute the dot product between V (=_Viewpoint - firstPoint) and N:
    Vec3r V(_Viewpoint - firstPoint);
    N.normalize();
    V.normalize();
    iFace->SetDotP(N * V);

    // compute the distance between the face center and the viewpoint:
    Vec3r dist_vec(iFace->center() - _Viewpoint);
    iFace->SetZ(dist_vec.norm());
}
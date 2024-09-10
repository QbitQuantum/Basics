bool VoxRaytracer::GetEntryPoint(const HLine3f line, Vector4f &pt) const
{
    Vector4f s = m_Image->GetLocalPoint(line.direction());
    pt = m_Image->GetLocalPoint(line.origin());

    // Considers Structured grid dimensions //
    Vector4f dims = m_Image->GetDims().homogeneous().cast<float>();
    pt = pt.cwiseQuotient(dims);
    s  = s.cwiseQuotient(dims);

    float l = s.head(3).norm();
    Vector3f L(l/s(0), l/s(1), l/s(2));

    Vector3f offset;
    for(int i=0;i<3;++i)
        offset(i) = (s(i)>0) - (pt(i)-floor(pt(i))) ;
    offset = offset.cwiseProduct(L).cwiseAbs();

    int id; float d;
    for(int loop=0; loop<8; loop++)
    {
        int check_border = 0;
        for ( int i=0; i<3 ;++i) {
            check_border += pt(i) > 1;
            check_border += pt(i) < 0;
        }
        if(check_border == 0) {
            for(int i=0;i<3;++i)
                pt(i) *= (float)dims(i);
            pt = m_Image->GetWorldPoint(pt);
            return true;
        }

       d = offset.minCoeff(&id);
       for(int i=0; i<3; ++i)
           pt(i) += d / L(i);

       pt(id) = rintf(pt(id));


       offset.array() -= d;
       offset(id) = fabs(L(id));
    }
    for(int i=0;i<3;++i)
        pt(i) *= (float)dims(i);
    pt = m_Image->GetWorldPoint(pt);
    return false;
}
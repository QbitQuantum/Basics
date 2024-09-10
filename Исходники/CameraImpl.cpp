Point2d CameraATAN::Project(const Point3d& p3d)
{
    if(p3d.z<=0) return Point2d(-1,-1);

#ifdef __SSE3__
    if(useDistortion)
    {
        __m128d xy=(__m128d){p3d.x,p3d.y};
        if(p3d.z!=1.)
        {
            xy=_mm_sub_pd(xy,(__m128d){p3d.z,p3d.z});
        }
        __m128d xy2=_mm_mul_pd(xy,xy);

         xy2=_mm_hadd_pd(xy2,xy2);
         xy2=_mm_sqrt_pd(xy2);
        double r=((Point2d*)&xy2)->x;
        if(r < 0.001 || d == 0.0)
            r=1.0;
        else
            r=(d_inv* atan(r * tan2w) / r);
        xy=_mm_mul_pd((__m128d){fx,fy},xy);
        xy=_mm_mul_pd(xy,(__m128d){r,r});
        xy=_mm_add_pd(xy,(__m128d){cx,cy});
        return *(Point2d*)&xy;
    }
    else
    {
        if(p3d.z==1.)
        {
            __m128d xy = _mm_setr_pd(p3d.x,p3d.y);
            xy=_mm_add_pd(_mm_setr_pd(cx,cy),_mm_mul_pd(xy,(__m128d){fx,fy}));
            return *(Point2d*)&xy;
        }
        else if(p3d.z>0)
        {
            double z_inv=1./p3d.z;
            return Point2d(fx*z_inv*p3d.x+cx,fy*z_inv*p3d.y+cy);
        }
    }
#else
    if(useDistortion)
    {
        double X=p3d.x,Y=p3d.y;
        if(p3d.z!=1.)
        {
            double z_inv=1./p3d.z;
            X*=z_inv;Y*=z_inv;
        }
        double r= sqrt(X*X+Y*Y);
        if(r < 0.001 || d == 0.0)
            r= 1.0;
        else
            r=(d_inv* atan(r * tan2w) / r);

        return Point2d(cx + fx * r * X,cy + fy * r * Y);
    }
    else
    {
        if(p3d.z==1.)
        {
            return Point2d(fx*p3d.x+cx,fy*p3d.y+cy);
        }
        else
        {
            double z_inv=1./p3d.z;
            return Point2d(fx*z_inv*p3d.x+cx,fy*z_inv*p3d.y+cy);
        }
    }
#endif
    return Point2d(-1,-1);// let compiler happy
}
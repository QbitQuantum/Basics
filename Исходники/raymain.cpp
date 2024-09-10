void BeginRender()
{

    cout<<"\nBeginning Render...";
    
    float alpha = camera.fov;
    float l = 1.0;
    float h = l * tan(alpha/2.0 *(M_PI/180));
    float aspectRatio = (float)camera.imgWidth/camera.imgHeight;
    float s = aspectRatio * h;
    float dx = (2 * s)/camera.imgWidth;
    float dy = -(2 * h)/camera.imgHeight;
    float dxx = dx/2,dyy=dy/2;
    Point3 K(-s,h,-l);
    K.x += dxx;
    K.y += dyy;
    for(int i = 0; i< camera.imgHeight; i++){
        
        for(int j = 0; j<camera.imgWidth; j++){
            
            K.x += dx;
            Matrix3 RotMat;
            
            Point3 dvec = camera.dir - camera.pos;
            Point3 svec = camera.up.Cross(dvec);
            dvec.Normalize();
            svec.Normalize();
            camera.up.Normalize();
            RotMat.Set(svec,camera.up, dvec);
            Ray r(camera.pos, K);
            
            r.dir=r.dir*RotMat;
            
            r.dir.Normalize();
            
            HitInfo hInfo;
            hInfo.Init();
            if(rootNode.GetNumChild()>0){
//                for(int k=0; k < rootNode.GetNumChild(); ++k){
//                    RayTrace(rootNode.GetChild(k),r,i * camera.imgWidth + j);
//                }
                if(RayTrace_2(r, hInfo))
                {
                    renderImage.PutPixel(i *camera.imgWidth+j, white, hInfo.z);
                }
                else renderImage.PutPixel(i *camera.imgWidth+j, black, BIGFLOAT);
            }
            
            
        }
        K.x = -s;
        K.x += dxx;
        K.y += dy;
    }
    cout<<"Render Complete"<<endl;
    renderImage.ComputeZBufferImage();
    renderImage.SaveZImage("/Users/varunk/Desktop/RayTracerProj1/RayTracerProj1/zbuffer.ppm");
    renderImage.SaveImage("/Users/varunk/Desktop/RayTracerProj1/RayTracerProj1/renderimage.ppm");
    
}
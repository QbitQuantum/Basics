void drawTriangleToRaster(OWRaster *raster, 
                          OWTriangle& triangle, 
                          OWMaterial material, 
                          OWScene scene,
                          bool phong,
                          OWVector4* camPosition)
{
    OWColorFloat* fillcolorF = material.color;
    unsigned rasterHeight = raster->getHeight();
    unsigned rasterWidth = raster->getWidth();
    float lambda1;
    float lambda2;
    float lambda3;
    float zDepth;
    lambda1=lambda3=lambda2=0.0f;
    
    float zb1=triangle.zBuffer[0];
    float zb2=triangle.zBuffer[1];
    float zb3=triangle.zBuffer[2];
    
    float xLength = scene.maxX - scene.minX;
    float yLength = scene.maxY - scene.minY;
    
    float x1,x2,x3,y1,y2,y3,z1,z2,z3;
    x1 = triangle.getVec1().getX();
    x2 = triangle.getVec2().getX();
    x3 = triangle.getVec3().getX();
    
    y1 = triangle.getVec1().getY();
    y2 = triangle.getVec2().getY();
    y3 = triangle.getVec3().getY();
    
    z1 = triangle.getVec1().getZ();
    z2 = triangle.getVec2().getZ();
    z3 = triangle.getVec3().getZ();
    
    float maxTX=fminf(scene.maxX,fmaxf(x1, fmaxf(x2, x3)));
    float maxTY=fminf(scene.maxY,fmaxf(y1, fmaxf(y2, y3)));
    float minTX=fmaxf(scene.minX,fminf(x1, fminf(x2, x3)));
    float minTY=fmaxf(scene.minY,fminf(y1, fminf(y2, y3)));

    unsigned maxRX = ceilf(fminf(rasterWidth, (maxTX - scene.minX)/xLength*(float)rasterWidth));
    unsigned minRX = floorf(fmaxf(0.0f,       (minTX - scene.minX)/xLength*(float)rasterWidth));
    unsigned maxRY = ceilf(fminf(rasterWidth, (maxTY - scene.minY)/yLength*(float)rasterHeight));
    unsigned minRY = floorf(fmaxf(0.0f,       (minTY - scene.minY)/yLength*(float)rasterHeight));
    
    if (maxRX > rasterWidth) {
        printf("raster x max bound error.\n");
        //system("pause");
        maxRX = rasterWidth;
    }
    if (maxRY > rasterHeight) {
        printf("raster y max bound error.\n");
        //system("pause");
        maxRY = rasterHeight;
    }
    
    for (unsigned y=minRY; y<maxRY; y++) {
        for (unsigned x=minRX; x<maxRX; x++) {
            float fx=((float)x/(float)rasterWidth) * xLength+scene.minX;
            float fy=((float)y/(float)rasterHeight)* yLength+scene.minY;
            calculateTriBarycentricCoordinates(triangle, fx, fy, &lambda1, &lambda2, &lambda3);
            zDepth = zb1*lambda1 + zb2*lambda2 + zb3*lambda3;
            if(
               lambda1 >= 0.0f && lambda2 >= 0.0f && lambda3 >= 0.0f 
               //&& (lambda1 <= 0.02f || lambda2 <= 0.02f || lambda3 <= 0.02f)
               && raster->z_buffer[x + y * rasterWidth] > zDepth
               //lambda1 <= 1.0f && lambda2 <= 1.0f && lambda3 <= 1.0f
               )
            {
                raster->z_buffer[x + y * rasterWidth] = zDepth;
                OWColorChannelFloat red,green,blue;
                red = fillcolorF[0].r * lambda1 + fillcolorF[1].r * lambda2 + fillcolorF[2].r * lambda3;
                green = fillcolorF[0].g * lambda1 + fillcolorF[1].g * lambda2 + fillcolorF[2].g * lambda3;
                blue = fillcolorF[0].b * lambda1 + fillcolorF[1].b * lambda2 + fillcolorF[2].b * lambda3;
                if (phong == true) {
/***Phong Mode*************************************************************************************/
                    for (list<OWLight>::iterator iterLight = scene.lightList.begin(); iterLight != scene.lightList.end(); iterLight++) {
                        OWVector4* currVector = new OWVector4;
                        OWVector4* n = new OWVector4;
                        
                        currVector->setX(triangle.worldCoorVec[0].getX() * lambda1 + triangle.worldCoorVec[1].getX() * lambda2 + triangle.worldCoorVec[2].getX() * lambda3);
                        currVector->setY(triangle.worldCoorVec[0].getY() * lambda1 + triangle.worldCoorVec[1].getY() * lambda2 + triangle.worldCoorVec[2].getY() * lambda3);
                        currVector->setZ(triangle.worldCoorVec[0].getZ() * lambda1 + triangle.worldCoorVec[1].getZ() * lambda2 + triangle.worldCoorVec[2].getZ() * lambda3);
                        
                        for (int i=0; i<3; i++) {
                            triangle.norVec[i].normalise();
                        }
                        n->setX(triangle.norVec[0].getX() * lambda1 + triangle.norVec[1].getX() * lambda2 + triangle.norVec[2].getX() * lambda3);
                        n->setY(triangle.norVec[0].getY() * lambda1 + triangle.norVec[1].getY() * lambda2 + triangle.norVec[2].getY() * lambda3);
                        n->setZ(triangle.norVec[0].getZ() * lambda1 + triangle.norVec[1].getZ() * lambda2 + triangle.norVec[2].getZ() * lambda3);
                        
                        OWVector4* l = vectorSubtract((*iterLight).myPosition, currVector);
                        
                        l->normalise();
                        n->normalise();
                        float l_dot_n = l->dotProduct(*n);
                        float diffContr = fmaxf(0.0f, l_dot_n);
                        
                        n->scale(2*l_dot_n);
                        OWVector4* r = vectorSubtract(n,l);
                        OWVector4* v = vectorSubtract(camPosition, currVector);
                        r->normalise();
                        v->normalise();
                        
                        OWColorFloat Idif;
                        if (diffContr < 0.0f) {
                            diffContr = 0.0f;
                        }
                        Idif.a=1.0f;
                        Idif.r=(*iterLight).myColor.r * red * diffContr;
                        Idif.g=(*iterLight).myColor.g * green * diffContr;
                        Idif.b=(*iterLight).myColor.b * blue * diffContr;
                        
                        OWColorFloat shininessColor = material.shininessColor;
                        OWColorFloat Ispec;
                        float specContri = powf(v->dotProduct(*r), shininessColor.a);
                        //float specContri = v->dotProduct(*r);
                        if (
                            l_dot_n >= 0.0f 
                            && specContri >= 0.0f
                            ) {
                            Ispec.a = 1.0f;
                            Ispec.r = (*iterLight).myColor.r * shininessColor.r * specContri;
                            Ispec.g = (*iterLight).myColor.g * shininessColor.g * specContri;
                            Ispec.b = (*iterLight).myColor.b * shininessColor.b * specContri;
                        }else{
                            Ispec.a = 0.0f;
                            Ispec.r = 0.0f;
                            Ispec.g = 0.0f;
                            Ispec.b = 0.0f;
                        }
                        scene.ambient.a = 0.0f;
                        //OWColorFloat tempColor = Idif;
                        //OWColorFloat tempColor = Ispec;
                        //OWColorFloat tempColor = scene.ambient;
                        //OWColorFloat tempColor = colorAdd(Idif, scene.ambient);
                        //OWColorFloat tempColor = colorAdd(Idif, Ispec);
                        OWColorFloat tempColor = colorAdd(Idif, colorAdd(Ispec, scene.ambient));
                        
                        colorNormalise(tempColor);
                        
                        red = tempColor.r;
                        green = tempColor.g;
                        blue = tempColor.b;
                    }
                    
                }
               
                raster->pixels[x + y * rasterWidth] = drawARGBColorFromFloatColor(red, green, blue);
            }
        }
    }
    //triangle.printMyself();
    
}
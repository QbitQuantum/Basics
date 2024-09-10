void SCRenderer::DrawModel(RSEntity* object, size_t lodLevel ){

    if (!initialized)
        return;
    
    if (lodLevel >= object->NumLods()){
        printf("Unable to render this Level Of Details (out of range): Max level is  %lu\n",
               std::min(0UL,object->NumLods()-1));
        return;
    }
    
    
    float ambientLamber = 0.4f;
    
    Lod* lod = &object->lods[lodLevel] ;
    
    
    
        
        
    glDisable(GL_CULL_FACE);
    
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    
    //Texture pass
    if (lodLevel == 0){
        glEnable(GL_TEXTURE_2D);
        
        //glDepthFunc(GL_EQUAL);
        
        glAlphaFunc ( GL_GREATER, 0.0 ) ;
        glEnable ( GL_ALPHA_TEST ) ;
        
        
        for (int i=0 ; i < object->NumUVs(); i++) {
            
            uvxyEntry* textInfo = &object->uvs[i];
            
            //Seems we have a textureID that we don't have :( !
            if (textInfo->textureID >= object->images.size())
                continue;
            
            RSImage* image = object->images[textInfo->textureID];
            
            Texture* texture = image->GetTexture();
            
            glBindTexture(GL_TEXTURE_2D, texture->id);
            
            Triangle* triangle = &object->triangles[textInfo->triangleID];
            
            Vector3D normal;
            GetNormal(object, triangle, &normal);
            
            
            glBegin(GL_TRIANGLES);
            for(int j=0 ; j < 3 ; j++){
                
                Point3D vertice = object->vertices[triangle->ids[j]];
                
                Vector3D lighDirection;
                lighDirection = light;
                lighDirection.Substract(&vertice);
                lighDirection.Normalize();
                
                float lambertianFactor = lighDirection.DotProduct(&normal);
                if (lambertianFactor < 0  )
                    lambertianFactor = 0;
                
                lambertianFactor+= ambientLamber;
                if (lambertianFactor > 1)
                    lambertianFactor = 1;
                
                
                
                glColor4f(lambertianFactor, lambertianFactor, lambertianFactor,1);
                glTexCoord2f(textInfo->uvs[j].u/(float)texture->width, textInfo->uvs[j].v/(float)texture->height);
                glVertex3f(object->vertices[triangle->ids[j]].x,
                           object->vertices[triangle->ids[j]].y,
                           object->vertices[triangle->ids[j]].z);
            }
            glEnd();
            
            
        }
        
        
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    }


    
    

   
    //Pass 3: Let's draw the transparent stuff render RSEntity::TRANSPARENT)
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glBlendEquation(GL_ADD);

    //glDepthFunc(GL_LESS);
        
        
    for(int i = 0 ; i < lod->numTriangles ; i++){
        
        uint16_t triangleID = lod->triangleIDs[i];
        
        Triangle* triangle = &object->triangles[triangleID];
        
        if (triangle->property != RSEntity::TRANSPARENT)
            continue;
        
        
        Vector3D normal;
        GetNormal(object,triangle,&normal);
        
        glBegin(GL_TRIANGLES);
        for(int j=0 ; j < 3 ; j++){
            
            
            
            Point3D vertice = object->vertices[triangle->ids[j]];
            
            
            Vector3D sunDirection;
            sunDirection = light;
            sunDirection.Substract(&vertice);
            sunDirection.Normalize();

            
            float lambertianFactor = sunDirection.DotProduct(&normal);
            if (lambertianFactor < 0  )
                lambertianFactor = 0;
            
            lambertianFactor=0.2f;
            
            // int8_t gouraud = 255 * lambertianFactor;
            
            
            //gouraud = 255;
            
            glColor4f(lambertianFactor, lambertianFactor, lambertianFactor,1);
            
            glVertex3f(vertice.x,
                       vertice.y,
                       vertice.z);
        }
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    
    
    
    
    
    
    //Pass 1, draw color
    for(int i = 0 ; i < lod->numTriangles ; i++){
        //for(int i = 60 ; i < 62 ; i++){  //Debug purpose only back governal of F-16 is 60-62
        
        uint16_t triangleID = lod->triangleIDs[i];
        
        Triangle* triangle = &object->triangles[triangleID];
        
        if (triangle->property == RSEntity::TRANSPARENT)
            continue;
        
        Vector3D normal;
        GetNormal(object, triangle, &normal);
        
        glBegin(GL_TRIANGLES);
        for(int j=0 ; j < 3 ; j++){
            
            Point3D vertice = object->vertices[triangle->ids[j]];
            
            Vector3D lighDirection;
            lighDirection = light;
            lighDirection.Substract(&vertice);
            lighDirection.Normalize();
            
            float lambertianFactor = lighDirection.DotProduct(&normal);
            if (lambertianFactor < 0  )
                lambertianFactor = 0;
            
            lambertianFactor+= ambientLamber;
            if (lambertianFactor > 1)
                lambertianFactor = 1;
            
            const Texel* texel = palette.GetRGBColor(triangle->color);
            
            glColor4f(texel->r/255.0f*lambertianFactor, texel->g/255.0f*lambertianFactor, texel->b/255.0f*lambertianFactor,1);
            //glColor4f(texel->r/255.0f, texel->g/255.0f, texel->b/255.0f,1);
            
            glVertex3f(object->vertices[triangle->ids[j]].x,
                       object->vertices[triangle->ids[j]].y,
                       object->vertices[triangle->ids[j]].z);
        }
        glEnd();
    }
    

}
void drawPitchLocation()
{
    float cols = PitchHandler_getColCount(phctx);
    float dx = 0.0125;
    float rows = PitchHandler_getRowCount(phctx);
    float dy = 1.0 / rows;
    
    VertexObjectBuilder_startColoredObject(voCtxDynamic, GRAPHICS_TRIANGLES);
    for(int f=0; f<FINGERMAX; f++)
    {
        struct FingerInfo* fInfo = PitchHandler_fingerState(phctx,f);
        if(fInfo->isActive)
        {
            VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX,    fInfo->pitchY   ,0,  0,255,  0,255);            
            VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX-dx, fInfo->pitchY   ,0,127,255,127,  0);            
            VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX   , fInfo->pitchY-dy,0,127,255,127,  0);            
            
            VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX,    fInfo->pitchY   ,0,  0,255,  0,255);            
            VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX   , fInfo->pitchY+dy,0,127,255,127,  0);            
            VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX+dx, fInfo->pitchY   ,0,127,255,127,  0);            
            
            VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX,    fInfo->pitchY   ,0,  0,255,  0,255);            
            VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX   , fInfo->pitchY+dy,0,127,255,127,  0);            
            VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX-dx, fInfo->pitchY   ,0,127,255,127,  0);            
            
            VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX,    fInfo->pitchY   ,0,  0,255,  0,255);            
            VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX+dx, fInfo->pitchY   ,0,127,255,127,  0);            
            VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX   , fInfo->pitchY-dy,0,127,255,127,  0);            
            
        }
    }    
    VertexObjectBuilder_startColoredObject(voCtxDynamic, GRAPHICS_LINES);
    for(int f=0; f<FINGERMAX; f++)
    {
        struct FingerInfo* fInfo = PitchHandler_fingerState(phctx,f);
        if(fInfo->isActive)
        {
            //TODO: this is ONLY right for uniform tunings
            float y = ((int)(rows*fInfo->pitchY) + 0.5)/rows;
            float dy = 1.0/rows;
            float detune;
            float detune2;
            

            if(PitchHandler_getRowCount(phctx)>1.5)
            {
                detune = PitchHandler_getStrDetune(phctx,(int)(fInfo->pitchY*rows));
                float dx3 = (12*log2f(3.0/2) - detune)/cols;
                float dx4 = (12*log2f(4.0/3) - detune)/cols;
                float dx5 = (12*log2f(5.0/4) - detune)/cols;
                float dx6 = (12*log2f(6.0/5) - detune)/cols;
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX,    y,0,  0,0, 255,255);            
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX+0.75*dx3,    y+0.75*dy,0,  0,0, 255,0);  
                
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX,    y,0,  0,0,255,255);            
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX+dx4, y+dy,0,  0,0,255,0);      
                
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX,    y,0,  0,255, 0,255);            
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX+0.75*dx5, y+0.75*dy,0,  0,255, 0,0);    
                
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX,    y,0,  50,255, 0,255);            
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX+0.75*dx6, y+0.75*dy,0,  50,255, 0,0);            
                
                int bottomRow = ((fInfo->pitchY*rows)>0)==0;
                detune2 = PitchHandler_getStrDetune(phctx,bottomRow + (int)(fInfo->pitchY*rows - 1));                
                float dx32 = (12*log2f(3.0/2) - detune2)/cols;
                float dx42 = (12*log2f(4.0/3) - detune2)/cols;
                float dx52 = (12*log2f(5.0/4) - detune2)/cols;
                float dx62 = (12*log2f(6.0/5) - detune2)/cols;
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX,    y,0,  0,0, 255,255);            
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX-0.75*dx32,    y-0.75*dy,0,  0,0, 255,0);    
                
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX,    y,0,  0,0, 255,255);            
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX-dx42, y-dy,0,  0,0,255,0);      
                
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX,    y,0,  0,255, 0,255);            
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX-0.75*dx52, y-0.75*dy,0,  0,255, 0,0);      
                
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX,    y,0,  50,255, 0,255);            
                VertexObjectBuilder_addColoredVertex(voCtxDynamic,fInfo->pitchX-0.75*dx62, y-0.75*dy,0,  50,255, 0,0);                            
            }
        }
    } 
}
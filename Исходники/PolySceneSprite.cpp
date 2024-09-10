void SpriteSet::createFramesFromIslands(unsigned int minDistance, const Vector2 &defaultAnchor) {
    String imageFileName = getTexture()->getResourcePath();
    
    Image *image = new Image(imageFileName);
    
    
    std::vector<Polycode::Rectangle> rects;
    
    for(int y=0; y < image->getHeight(); y++) {
        for(int x=0; x < image->getWidth(); x++) {
            if(image->getPixel(x, y).a > 0.0) {
                Polycode::Rectangle rect = createBoxAtCoordinate(image,x,y);
                rects.push_back(rect);
                x += rect.w;
            }
        }
    }
    
    while(rects.size() > 1) {
        
        bool intersected = false;
        for(int i=0; i < rects.size(); i++) {
            for(int i2=0; i2 < rects.size(); i2++) {
                if(i != i2) {
                    if(rectIntersect(rects[i], rects[i2], minDistance)) {
                        
                        Polycode::Rectangle newRect;
                        
                        newRect.x = std::min(rects[i].x, rects[i2].x);
                        newRect.y = std::min(rects[i].y, rects[i2].y);
                        
                        newRect.w = std::max(rects[i].x + rects[i].w, rects[i2].x + rects[i2].w) - newRect.x;
                        newRect.h = std::max(rects[i].y + rects[i].h, rects[i2].y + rects[i2].h) - newRect.y;
                        
                        rects[i] = newRect;
                        rects.erase(rects.begin() + i2);
                        
                        intersected = true;
                        
                        break;
                    }
                }
            }
        }
        
        if(!intersected) {
            break;
        }
        
    }
    
    
    for(int i=0; i < rects.size(); i++) {
        SpriteFrame frame;
        frame.coordinates = rects[i];
        
        frame.coordinates.x = frame.coordinates.x / ((Number)image->getWidth());
        frame.coordinates.y = frame.coordinates.y / ((Number)image->getHeight());
        frame.coordinates.w = frame.coordinates.w / ((Number)image->getWidth());
        frame.coordinates.h = frame.coordinates.h / ((Number)image->getHeight());
        
        frame.anchorPoint = defaultAnchor;
        
        addSpriteFrame(frame);
    }
    
    delete image;
}
//--------------------------------------------------------------
void testApp::update(){
    
    ofVec3f diff ;          //Difference between particle and mouse
    float dist ;            //distance from particle to mouse ( as the crow flies ) 
    float ratio ;           //Ratio of how strong the effect is = 1 + (-dist/maxDistance) ;
    const ofVec3f mousePosition = ofVec3f( mouseX , mouseY , 0 ) ; //Allocate and retrieve mouse values once.
    const ofVec3f origin = ofVec3f(0,0,0);
    //Create an iterator to cycle through the vector
    std::vector<Particle>::iterator p ; 
    for ( p = particles.begin() ; p != particles.end() ; p++ ) 
    {
        ratio = 1.0f ; 
        p->velocity *= friction ; 
        //reset acceleration every frame
        p->acceleration = ofVec3f() ; 
        diff = mousePosition - p->position ;  
        dist = mousePosition.distance( p->position ) ; 
        //If within the zone of interaction
        if ( dist * .5 < forceRadius )  
        {
            ratio = -1 + dist / forceRadius ; 
            //Repulsion
            if ( cursorMode == 0 ) 
                p->acceleration -= ( diff * ratio) ;
            //Attraction
            else
                p->acceleration += ( diff * ratio ) ; 
        }
        if ( springEnabled ) 
        {
            //Move back to the original position
            p->acceleration += springFactor * (p->spawnPoint - p->position );
        }
        
        p->velocity += p->acceleration * ratio ; 
        p->position += p->velocity ; 
    }
    
    if ( ofGetFrameNum() % 300 == 0 ) 
    {
        curImageIndex++ ;
        setupParticles() ;
    }
}
void SpriteBehavior() // Din kod!
{
    SpritePtr i = gSpriteRoot; 
    SpritePtr j = i->next;
    
    int count = 0;
    float dPos;


    FPoint black_hole = {0,0};
    FPoint alignmentVel = {0,0};

    while(i != NULL){
	if(i->ai_type == DOG){
	    i = i->next;
	    continue;
	}

	count = 0;
	while(j != NULL){
	    
	    dPos = distance(i->position, j->position);

	    if(dPos < maxDist){
		count++;

		// Cohesion
		if(i->ai_type == SHEEP || j->ai_type != DOG){
		    black_hole.h += j->position.h;
		    black_hole.v += j->position.v;
		}

		if(j->ai_type != DOG){
		    // Alignment
		    alignmentVel.h += j->speed.h;
		    alignmentVel.v += j->speed.v;
		}
	    }

	    // Separation
	    if(dPos < minDist && (i != j)){
		i->speed.h += 1/(dPos + 0.1)*separationCoeff*(i->position.h - j->position.h);
		i->speed.v += 1/(dPos + 0.1)*separationCoeff*(i->position.v - j->position.v);
	    }

	    if(j->ai_type == DOG && dPos < maxDist){
		i->speed.h += 1/(dPos + 0.1)*10*separationCoeff*(i->position.h - j->position.h);
		i->speed.v += 1/(dPos + 0.1)*10*separationCoeff*(i->position.v - j->position.v);
	    }

	    j = j->next;
	}

	black_hole.h /= count;
	black_hole.v /= count;

	alignmentVel.h /= count;
	alignmentVel.v /= count;

	if(i->ai_type == SHEEP){
	    i->speed.h += cohesionCoeff*(black_hole.h - i->position.h);
	    i->speed.v += cohesionCoeff*(black_hole.v - i->position.v);

	    i->speed.h += alignmentCoeff*alignmentVel.h;
	    i->speed.v += alignmentCoeff*alignmentVel.v;
	}

	i->speed.h += i->randomness*((float)random()/RAND_MAX - 0.5);
	i->speed.v += i->randomness*((float)random()/RAND_MAX - 0.5);
	
	if(normFPoint(i->speed) > maxSpeed) {
	    i->speed.h = maxSpeed*normalizeFPoint(i->speed).h;
	    i->speed.v = maxSpeed*normalizeFPoint(i->speed).v;
	}

	i = i->next;
	j = gSpriteRoot;

	black_hole.h = 0;
	black_hole.v = 0;

	alignmentVel.h = 0;
	alignmentVel.v = 0;
    }
}
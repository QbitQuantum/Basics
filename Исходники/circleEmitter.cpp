bool circleEmitter::addParticle(){
    particle *newParticle;
    float speed;
    //Particle pool exists and max num particles not exceeded
    if(e != NULL && *managerParticleList != NULL && e->particleCount < e->totalParticles && emitting){
        newParticle = *managerParticleList;
        *managerParticleList = (*managerParticleList)->next;
        if(e->particleList != NULL){
            e->particleList->prev = newParticle;
        }
        newParticle->next = e->particleList;
        newParticle->prev = NULL;
        e->particleList = newParticle;
        
        float angle = randomAngle();
        float radScalar = randDist();
        newParticle->rand = radScalar;
        newParticle->radius = radius * radScalar;
        STVector3 point = STVector3(radius*radScalar*cosf(angle), 0, radius*radScalar*sinf(angle));
        STVector3 straightUp = STVector3(0,1,0);
        STVector3 circleDir = STVector3(e->dir.x, e->dir.y, e->dir.z);
        

        STVector3 a  = STVector3::Cross(straightUp, circleDir);
        float w = sqrt(powf(straightUp.Length(), 2) * powf(circleDir.Length(), 2)) + STVector3::Dot(straightUp, circleDir);
        Quaternion rotateCircle = Quaternion(w, a.x, a.y, a.z);
        rotateCircle.Normalize();

        STVector3 rotatedPoint = rotateCircle.rotate(point, rotateCircle);
        newParticle->pos.x = rotatedPoint.x + e->pos.x;
        newParticle->pos.y = rotatedPoint.y + e->pos.y;
        newParticle->pos.z = rotatedPoint.z + e->pos.z;

/*
        newParticle->pos.x = e->pos.x + radius*sinf(angle);
        newParticle->pos.y = e->pos.y;
        newParticle->pos.z = e->pos.z + radius*cosf(angle);
*/
        
        newParticle->prevPos.x = 0;
        newParticle->prevPos.y = 0;
        newParticle->prevPos.z = 0;
        
        newParticle->dir = e->dir + (e->dirVar*randDist());
        speed = e->speed + (e->speed * randDist());
        newParticle->dir.x *= speed;
        newParticle->dir.y *= speed;
        newParticle->dir.z *= speed;
        
        newParticle->life = e->life + (int)((float)e->lifeVar * randDist());

        newParticle->side = randDist();
        e->particleCount++;
        return true;
    }
    return false;
}
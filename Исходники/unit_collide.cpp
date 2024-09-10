bool Unit::InsideCollideTree( Unit *smaller,
                              QVector &bigpos,
                              Vector &bigNormal,
                              QVector &smallpos,
                              Vector &smallNormal,
                              bool bigasteroid,
                              bool smallasteroid )
{
    if (smaller->colTrees == NULL || this->colTrees == NULL)
        return false;
    if (hull < 0) return false;
    if (smaller->colTrees->usingColTree() == false || this->colTrees->usingColTree() == false)
        return false;
    csOPCODECollider::ResetCollisionPairs();
    Unit *bigger = this;

    csReversibleTransform bigtransform( bigger->cumulative_transformation_matrix );
    csReversibleTransform smalltransform( smaller->cumulative_transformation_matrix );
    smalltransform.SetO2TTranslation( csVector3( smaller->cumulative_transformation_matrix.p
                                                 -bigger->cumulative_transformation_matrix.p ) );
    bigtransform.SetO2TTranslation( csVector3( 0, 0, 0 ) );
    //we're only gonna lerp the positions for speed here... gahh!
    
    // Check for shield collisions here prior to checking for mesh on mesh or ray collisions below. 
    csOPCODECollider *tmpCol = smaller->colTrees->colTree( smaller, bigger->GetWarpVelocity() );
    if ( tmpCol
        && ( tmpCol->Collide( *bigger->colTrees->colTree( bigger,
                                                         smaller->GetWarpVelocity() ), &smalltransform, &bigtransform ) ) ) {
        csCollisionPair *mycollide = csOPCODECollider::GetCollisions();
        unsigned int     numHits   = csOPCODECollider::GetCollisionPairCount();
        if (numHits) {
            smallpos.Set( (mycollide[0].a1.x+mycollide[0].b1.x+mycollide[0].c1.x)/3.0f,
                         (mycollide[0].a1.y+mycollide[0].b1.y+mycollide[0].c1.y)/3.0f,
                         (mycollide[0].a1.z+mycollide[0].b1.z+mycollide[0].c1.z)/3.0f );
            smallpos = Transform( smaller->cumulative_transformation_matrix, smallpos );
            bigpos.Set( (mycollide[0].a2.x+mycollide[0].b2.x+mycollide[0].c2.x)/3.0f,
                       (mycollide[0].a2.y+mycollide[0].b2.y+mycollide[0].c2.y)/3.0f,
                       (mycollide[0].a2.z+mycollide[0].b2.z+mycollide[0].c2.z)/3.0f );
            bigpos = Transform( bigger->cumulative_transformation_matrix, bigpos );
            csVector3 sn, bn;
            sn.Cross( mycollide[0].b1-mycollide[0].a1, mycollide[0].c1-mycollide[0].a1 );
            bn.Cross( mycollide[0].b2-mycollide[0].a2, mycollide[0].c2-mycollide[0].a2 );
            sn.Normalize();
            bn.Normalize();
            smallNormal.Set( sn.x, sn.y, sn.z );
            bigNormal.Set( bn.x, bn.y, bn.z );
            smallNormal = TransformNormal( smaller->cumulative_transformation_matrix, smallNormal );
            bigNormal   = TransformNormal( bigger->cumulative_transformation_matrix, bigNormal );
            return true;
        }
    }
    un_iter i;
    static float rsizelim = XMLSupport::parse_float( vs_config->getVariable( "physics", "smallest_subunit_to_collide", ".2" ) );
    clsptr  bigtype = bigasteroid ? ASTEROIDPTR : bigger->isUnit();
    clsptr  smalltype     = smallasteroid ? ASTEROIDPTR : smaller->isUnit();
    if ( bigger->SubUnits.empty() == false
        && (bigger->graphicOptions.RecurseIntoSubUnitsOnCollision == true || bigtype == ASTEROIDPTR) ) {
        i = bigger->getSubUnits();
        float rad = smaller->rSize();
        for (Unit *un; (un = *i); ++i) {
            float subrad = un->rSize();
            if ( (bigtype != ASTEROIDPTR) && (subrad/bigger->rSize() < rsizelim) ) {
                break;
            }
            if ( ( un->Position()-smaller->Position() ).Magnitude() <= subrad+rad ) {
                if ( ( un->InsideCollideTree( smaller, bigpos, bigNormal, smallpos, smallNormal, bigtype == ASTEROIDPTR,
                                              smalltype == ASTEROIDPTR ) ) )
                    return true;
            }
        }
    }
    if ( smaller->SubUnits.empty() == false
        && (smaller->graphicOptions.RecurseIntoSubUnitsOnCollision == true || smalltype == ASTEROIDPTR) ) {
        i = smaller->getSubUnits();
        float rad = bigger->rSize();
        for (Unit *un; (un = *i); ++i) {
            float subrad = un->rSize();
            if ( (smalltype != ASTEROIDPTR) && (subrad/smaller->rSize() < rsizelim) )
                break;
            if ( ( un->Position()-bigger->Position() ).Magnitude() <= subrad+rad ) {
                if ( ( bigger->InsideCollideTree( un, bigpos, bigNormal, smallpos, smallNormal, bigtype == ASTEROIDPTR,
                                                  smalltype == ASTEROIDPTR ) ) )
                    return true;
            }
        }
    }
    //FIXME
    //doesn't check all i*j options of subunits vs subunits
    return false;
}
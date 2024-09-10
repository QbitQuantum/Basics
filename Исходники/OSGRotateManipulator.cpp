void RotateManipulator::doMovement(      Transform    *t,
                                   const Int32         coord,
                                   const Real32        value,
                                   const Vec3f        &translation,
                                   const Quaternion   &rotation,
                                   const Vec3f        &scaleFactor,
                                   const Quaternion   &scaleOrientation)
{
    Vec3f axis(0.0f, 0.0f, 0.0f);
    axis[coord] = 1.0;
    const Quaternion rot(axis, value);

    Matrix ma, mb, mc, md, me, mf, mg;
    
    Vec3f sp( getPivot()[0] * scaleFactor[0],
              getPivot()[1] * scaleFactor[1],
              getPivot()[2] * scaleFactor[2]);
             
    ma.setTranslate( - translation      );
    mb.setRotate   ( rotation.inverse() );
    mc.setTranslate( - sp               );
    md.setRotate   ( rot                );
    me.setTranslate( sp                 );
    mf.setRotate   ( rotation           );
    mg.setTranslate( translation        );
    
    
    t->editMatrix().multLeft(ma);
    t->editMatrix().multLeft(mb);
    t->editMatrix().multLeft(mc);
    t->editMatrix().multLeft(md);
    t->editMatrix().multLeft(me);
    t->editMatrix().multLeft(mf);
    t->editMatrix().multLeft(mg);
}
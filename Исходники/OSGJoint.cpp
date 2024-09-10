NewActionTypes::ResultE Joint::intersectActorEnter(
    ActorBase::FunctorArgumentType &funcArg)
{
    IntersectActor *pIA        = dynamic_cast<IntersectActor *>(
                                                           funcArg.getActor());
    Matrix          matrix     = this->getMatrix();
    Line            transLine;
    Pnt3f           pos;
    Vec3f           dir;

    matrix.mult(this->getJointTransformation());
    matrix.invert();

    matrix.multFull(pIA->getRay().getPosition (), pos);
    matrix.mult    (pIA->getRay().getDirection(), dir);

    transLine.setValue(pos, dir);

    pIA->beginEditState();
    {
        pIA->setRay        (transLine                           );
        pIA->setScaleFactor(pIA->getScaleFactor() / dir.length());
    }
    pIA->endEditState  ();

    pIA->setupChildrenPriorities();

    return NewActionTypes::Continue;
}
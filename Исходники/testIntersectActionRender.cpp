Action::ResultE transformEnter(CNodePtr& node, Action * action) 
{ 
    IntersectAction * ia = dynamic_cast<IntersectAction*>(action);
    NodePtr n( node );
    Transform* core =  dynamic_cast<Transform*>(get_pointer(n->getCore()));
    Matrix m = core->getMatrix();
    m.invert();
    
    Pnt3f pos;
    Vec3f dir;
    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);
    
    ia->setLine( Line( pos, dir ), ia->getMaxDist() );
    return Action::Continue; 
}
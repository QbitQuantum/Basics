OSG::Action::ResultE dontEnterTrans(OSG::Node *node)
{   
    SLOG << "entering " << node << OSG::endLog;

    if(node->getCore()->getType().isDerivedFrom(OSG::Transform::getClassType()))
    {
        OSG::Transform *t = dynamic_cast<OSG::Transform *>(node->getCore());
        
        SLOG << "derived from transform, skipping children" << OSG::endLog;
        SLOG << "Matrix: " << OSG::endLog << t->getMatrix();
        return OSG::Action::Skip;
    }   
    return OSG::Action::Continue; 
}
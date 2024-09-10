void DAGNode::updateContext()
{
    if ( !getParents().empty() )
    {
        if( debug_ )
        {
            std::cerr<<"DAGNode::updateContext, node = "<<getName()<<", incoming context = "<< getParents()[0]->getContext() << std::endl;
        }
        // TODO
        // ahem.... not sure here... which parent should I copy my context from exactly ?
        copyContext(*dynamic_cast<Context*>(getParents()[0]));
    }
    simulation::Node::updateContext();
}
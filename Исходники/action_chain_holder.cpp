/*!

 */
void
ActionChainHolder::update( const WorldModel & wm )
{
    static GameTime s_update_time( 0, 0 );
    static FieldEvaluator::ConstPtr s_update_evaluator;
    static ActionGenerator::ConstPtr s_update_generator;

    if ( s_update_time == wm.time()
         && s_update_evaluator == M_evaluator
         && s_update_generator == M_generator )
    {
        return;
    }
    s_update_time = wm.time();
    s_update_evaluator = M_evaluator;
    s_update_generator = M_generator;

    M_graph = ActionChainGraph::Ptr( new ActionChainGraph( M_evaluator, M_generator ) );
    M_graph->calculate( wm );
}
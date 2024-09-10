T simulate_aig_function( const aig_graph& aig, const aig_function& f,
                         const aig_simulator<T>& simulator )
{
  T value = simulate_aig_node<T>( aig, f.node, simulator );
  return f.complemented ? simulator.invert( value ) : value;
}
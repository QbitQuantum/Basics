// This works fine, but iterating over a list like this is
// fairly slow. See if you can speed it up!
int ReduceFunction::reduce( const List &list ) const {
  int result = identity();
  for( size_t p = 0; p < list.length(); ++p ) {
    result = function( result, list.value( p ) );
  }
  return result;
}
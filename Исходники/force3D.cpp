void force3D( Geometry& g, const Kernel::FT& defaultZ )
{
    transform::ForceZ t( defaultZ ) ;
    g.accept( t ) ;
}
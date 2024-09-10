void       translate( Geometry& g, const Kernel::Vector_3& v )
{
    transform::AffineTransform3 visitor(
        CGAL::Aff_transformation_3< Kernel >( CGAL::TRANSLATION, v )
    );
    g.accept( visitor ) ;
}
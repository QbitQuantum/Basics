heavysideFunction::value_type
heavysideFunction::operator()( node_type const& pointHat ) const
{
    node_type Ellipse( pbeqspace_type::Dim );
    node_type point( pbeqspace_type::Dim );

    point = element_prod( *M_stretch,pointHat ) + ( *M_translation );

    molecule_type::atoms_const_iterator_type atom( M_molecule->begin() );

    for ( ; atom != M_molecule->end(); ++atom )
    {
        Ellipse =  point  - atom->center();

        //if ( norm_inf(Ellipse) >  atom->radius() ) continue;

        if  ( norm_2( Ellipse ) < atom->radius2() )
        {
            return 0;
        }
    }

    return 1;
}
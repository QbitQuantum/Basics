inline bool getPatch( MLSGrid* grid, const Transform& C_m2g, const Point& p, MLSGrid::SurfacePatch& patch, double sigma_threshold )
{
    MLSGrid::Position pos;
    if( grid->toGrid((C_m2g * p).head<2>(), pos) )
    {
        // offset the z-coordinate which is given in map to grid
        MLSGrid::SurfacePatch probe( patch );
        probe.mean += C_m2g.translation().z();

        MLSGrid::SurfacePatch* res =
            grid->get( pos, probe, sigma_threshold );

        if( res )
        {
            patch = *res;
            // offset the z-coordinate, so that it is expressed in terms
            // of the map and not the grid
            patch.mean -= C_m2g.translation().z();
            return true;
        }
    }
    return false;
}
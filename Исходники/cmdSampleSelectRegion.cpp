/*
Description:
  Selects point cloud points using a 2D selection region.
Parameters:
  view     - [in]  The view in which the selection region was defined.
  cloud    - [in]  The point cloud to test.
  points3d - [in]  The 2D (screen) points that define the selection region.
  indices  - [out] The indices of the points in the point cloud
                   that lie inside of the selection region.
Returns:
  The number of indices added to the output array.
*/
static int RhRegionSelectPointCloudPoints(
    CRhinoView* view,
    const ON_PointCloud& cloud,
    ON_SimpleArray<CPoint>& points2d,
    ON_SimpleArray<int>& indices
)
{
    if( 0 == view )
        return 0;

    const int index_count = indices.Count();

    CRgn rgn;
    if( rgn.CreatePolygonRgn(points2d.Array(), points2d.Count(), WINDING) )
    {
        ON_Xform w2s;
        view->ActiveViewport().VP().GetXform( ON::world_cs, ON::screen_cs, w2s );

        int i;
        ON_3dPoint point;

        for( i = 0; i < cloud.m_P.Count(); i++ )
        {
            point = cloud.m_P[i];
            point.Transform( w2s );
            if( rgn.PtInRegion((int)point.x, (int)point.y) )
                indices.Append( i );
        }
    }

    return indices.Count() - index_count;
}
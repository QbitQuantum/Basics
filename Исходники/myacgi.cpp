Adesk::Boolean 
myWorldGeometry::polyline  (const AcGiPolyline& polylineObj) const
{
    _print(_T("\t\tmyWorldGeometry::polyline2\n"));
    polyline (polylineObj.points(), 
              polylineObj.vertexList(), 
              polylineObj.normal(), 
              polylineObj.baseSubEntMarker());
    return Adesk::kFalse;
}
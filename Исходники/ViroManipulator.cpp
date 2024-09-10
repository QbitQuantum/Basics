// Computes all intersections in line segment (p1,p2) and returns the nearest impact point in 
// vResult and its associated surface normal.
bool ViroManipulator::Intersect(osg::Vec3d p1,osg::Vec3d p2, osg::Vec3d& vResult,osg::Vec3d& vNorm){
	osg::ref_ptr<osg::LineSegment> seg = new osg::LineSegment;
	seg->set(p1,p2);
	if ( !seg->valid() ) return false;

	osgUtil::IntersectVisitor iv;
	iv.setTraversalMode(osgUtil::IntersectVisitor::TRAVERSE_ACTIVE_CHILDREN); //Only visible children
	iv.setLODSelectionMode(osgUtil::IntersectVisitor::USE_SEGMENT_START_POINT_AS_EYE_POINT_FOR_LOD_LEVEL_SELECTION);
	iv.addLineSegment(seg.get());
	iv.setEyePoint( _vEye );

	_NODE->accept( iv );

	bool hitfound = false;
	if (iv.hits()){
		osgUtil::IntersectVisitor::HitList& hitList = iv.getHitList(seg.get());
		if (!hitList.empty()){
			for(osgUtil::IntersectVisitor::HitList::iterator hitr=hitList.begin(); hitr!=hitList.end(); ++hitr){
				if( hitr->_geode.valid() && (hitr->_geode.get()->getName()!="Contraint_OutBox_Geode") && (hitr->_geode.get()->getName()!="environment")){
						osg::Vec3d ip = hitr->getWorldIntersectPoint();
						osg::Vec3d in = hitr->getWorldIntersectNormal();

						if(!hitfound){
							vResult = ip;
							vNorm   = in;
							}
						else{
							osg::Vec3d vLastIP    = vResult;
							osg::Vec3d vCurrentIP = ip;
							double dPrev    = Vec3d(_vEye - vLastIP).length();
							double dCurrent = Vec3d(_vEye - vCurrentIP).length();

							if( dCurrent < dPrev ){
								vResult = ip;
								vNorm   = in;
								}
							}
						hitfound = true;
						}
					}
				}
			}
	if (hitfound){
		vNorm.normalize();
		vNorm = RightNormal(vResult,vNorm);
		}
	
	return hitfound;
}
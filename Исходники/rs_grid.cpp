/**
 * find the closest grid point
 *@return the closest grid to given point
 *@coord: the given point
 */
RS_Vector RS_Grid::snapGrid(const RS_Vector& coord) const {
	if( cellV.x<RS_TOLERANCE || cellV.y<RS_TOLERANCE) return coord;
	RS_Vector vp(coord-baseGrid);
	if(isometric){
		//use remainder instead of fmod to locate the left-bottom corner for both positive and negative displacement
		RS_Vector vp1( vp-RS_Vector( remainder(vp.x-0.5*cellV.x,cellV.x)+0.5*cellV.x, remainder(vp.y-0.5*cellV.y,cellV.y)+0.5*cellV.y));
		RS_VectorSolutions sol({vp1,vp1+cellV,vp1+cellV*0.5, vp1+RS_Vector(cellV.x,0.), vp1+RS_Vector(0.,cellV.y)});
		vp1=sol.getClosest(vp);
		return baseGrid+vp1;

	}else{
		return baseGrid+vp-RS_Vector(remainder(vp.x,cellV.x),remainder(vp.y,cellV.y));
	}
}
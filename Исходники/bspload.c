/* scales the input vector to the new length and returns it */
Vector3D *V3Scale(Vector3D *v, FixedPoint newlen) {
    FixedPoint len;
    
    len = V3Length(v);
    
    if (len != 0.0) {
	v->x = mulDiv(v->x,newlen,len);
	v->y = mulDiv(v->y,newlen,len);
	v->z = mulDiv(v->z,newlen,len);
    }
    return(v);
}
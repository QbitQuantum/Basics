/*************
 * DESCRIPTION:   sets a scale orientation translate matrix
 * INPUT:         s           scale factors
 *                ox,oy,oz    orientation
 *                d           translation values
 * OUTPUT:        none
 *************/
void MATRIX::SetSOTMatrix(const VECTOR *s, const VECTOR *ox, const VECTOR *oy, const VECTOR *oz, const VECTOR *d)
{
    IdentityMatrix();
    m[ 1] = d->x;
    m[ 2] = d->y;
    m[ 3] = d->z;
    m[ 5] = ox->x * s->x;
    m[ 9] = ox->y * s->x;
    m[13] = ox->z * s->x;
    m[ 6] = oy->x * s->y;
    m[10] = oy->y * s->y;
    m[14] = oy->z * s->y;
    m[ 7] = oz->x * s->z;
    m[11] = oz->y * s->z;
    m[15] = oz->z * s->z;
}
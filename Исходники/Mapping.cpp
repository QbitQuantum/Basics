/** \fn void fromITP(struct position *delpos, btQuaternion &delrot, int armserial)
 * \brief Transform a position increment and an orientation increment from ITP coordinate frame into local robot coordinate frame.
 *        Do this using inv(R)*C*R : R= transform, C= increment
 * \param delpos - a pointer points to a position struct
 * \param delrot - a reference of a btQuanternion class
 * \param armserial - an integer number of of mechanisam id
 * \question why post multiply with R inverse?
*/
void fromITP(struct position *delpos, btQuaternion &delrot, int armserial)
{
    const btTransform ITP2Gold ( btMatrix3x3 (0,0,-1,  -1,0,0,  0,1,0), btVector3 (0,0,0) );
    const btTransform ITP2Green( btMatrix3x3 (0,0,-1,  1,0,0,  0,-1,0), btVector3 (0,0,0) );
    btTransform incr (delrot, btVector3(delpos->x, delpos->y, delpos->z));

    if (armserial == GOLD_ARM_SERIAL)
    {
        incr = ITP2Gold  * incr * ITP2Gold.inverse();
    }
    else
    {
        incr = ITP2Green * incr * ITP2Green.inverse();
    }

    delrot = incr.getRotation();
    delpos->x = (int)(incr.getOrigin()[0]);
    delpos->y = (int)(incr.getOrigin()[1]);
    delpos->z = (int)(incr.getOrigin()[2]);
}
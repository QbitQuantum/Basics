//----------------------------------------------------------------------------
void PhysicsModule::GetData (APoint& center, HMatrix& incrRot) const
{
    // Position is a point exactly on the hill.
    APoint position;
    position[0] = (float)(A1*mState[0]);
    position[1] = (float)(A2*mState[2]);
    position[2] = (float)(A3 - mState[0]*mState[0] - mState[2]*mState[2]);

    // Lift this point off the hill in the normal direction by the radius of
    // the ball so that the ball just touches the hill.  The hill is
    // implicitly specified by F(x,y,z) = z - [a3 - (x/a1)^2 - (y/a2)^2]
    // where (x,y,z) is the position on the hill.  The gradient of F is a
    // normal vector, Grad(F) = (2*x/a1^2,2*y/a2^2,1).
    AVector normal;
    normal[0] = 2.0f*position[0]/(float)mAux[0];
    normal[1] = 2.0f*position[1]/(float)mAux[1];
    normal[2] = 1.0f;
    normal.Normalize();

    center = position + ((float)Radius)*normal;

    // Let the ball rotate as it rolls down hill.  The axis of rotation is
    // the perpendicular to hill normal and ball velocity.  The angle of
    // rotation from the last position is A = speed*deltaTime/radius.
    AVector velocity;
    velocity[0] = (float)(A1*mState[1]);
    velocity[1] = (float)(A1*mState[3]);
    velocity[2] = -2.0f*(velocity[0]*(float)mState[0] +
        velocity[1]*(float)mState[2]);

    float speed = velocity.Normalize();
    float angle = speed*((float)mDeltaTime)/((float)Radius);
    AVector axis = normal.UnitCross(velocity);
    incrRot = HMatrix(axis, angle);
}
/**
 * This method uses the new position of the given object,
 * its previous position and the map to determine whether
 * the object is colliding with the walls
 */
bool MovementMap::IsColliding(const Rect box)
{
//    // Checks the center
//    if (!IsZero(box.Center().GetX(), box.Center().GetY())) return true;
    // Checks the above limit
    if (!IsZero(box.GetX()+box.GetW()/2, box.GetY())) return true;
    // Checks the right limit
    if (!IsZero(box.GetX() + box.GetW(), box.GetY() + box.GetH()/2)) return true;
    // Checks the left limit
    if (!IsZero(box.GetX(), box.GetY()+box.GetH()/2)) return true;
    // Checks the upper-right limit
    if (!IsZero(box.GetX()+box.GetW(), box.GetY())) return true;
    // Checks the upper-left limit
    if (!IsZero(box.GetX(), box.GetY())) return true;
    // Checks the lower limit
    if (!IsZero(box.Center().GetX(), box.Center().GetY() + box.GetH()/2)) return true;
    // Checks the lower-right limit
    if (!IsZero(box.GetX()+box.GetW(), box.GetY()+box.GetH())) return true;
    // Checks the lower-left limit
    if (!IsZero(box.GetX(), box.GetY()+box.GetH())) return true;
    return false;
//    return IsCollidingWithGround(box);
}
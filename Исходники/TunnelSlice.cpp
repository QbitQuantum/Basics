Vector3 TunnelSlice::requestWallMove(Direction dir, float offset) const
{
    Vector3 move = rot * requestWallDistance(dir);
    move = move * ((move.length() - offset) / move.length());
    
    return move;
}
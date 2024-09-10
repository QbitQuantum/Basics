void KServer::recv_landscape( vce::VSint32 floorID, vce::VSint32 x1,vce::VSint32 y1,vce::VSint32 x2,vce::VSint32 y2)
{
    if( !m_authenticationSuccess )return;
    if( !m_pc )return;

    Floor *fl = World::getFloor(floorID);
    if(!fl)return;

    TileType data[4000];
    int ind = 0;
    for(int y=y1; y < y2; y++ ){
        for(int x=x1; x < x2; x++){
            data[ind++] = fl->getTile(Coord(x,y)).typeID;
            if( ind == ARRAYLEN(data)) break;
        }
        if( ind == ARRAYLEN(data)) break;        
    }
    send_landscapeResult( floorID, x1,y1,x2,y2, data, ind );
    
}
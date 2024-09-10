void PtexReader::TiledFaceBase::getPixel(int ui, int vi, void* result)
{
    int tileu = ui >> _tileres.ulog2;
    int tilev = vi >> _tileres.vlog2;
    PtexPtr<PtexFaceData> tile ( getTile(tilev * _ntilesu + tileu) );
    tile->getPixel(ui - (tileu<<_tileres.ulog2),
                   vi - (tilev<<_tileres.vlog2), result);
}
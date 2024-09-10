ShadedSurfaceLayer::ShadedSurfaceLayer(DataGrid* grid)
: Layer(),
  _DataGrid(grid),
  _Ramp(DefaultColorRamp),
  _TexBitmap(0),
  _TexWidth(0),
  _TexHeight(0),
  _TextureID(-1),
  _DisplayList(0),
  _Compiled(false)
{
  if(_DataGrid)
  {
    Variant value;
    MPI_Offset pos[MAX_DIMS];
    _MinVal = MaxVariant(MPITypeToVariantType(_DataGrid->GetType()));
    _MaxVal = MinVariant(MPITypeToVariantType(_DataGrid->GetType()));
    for(pos[XDIM] = 0; pos[XDIM] < _DataGrid->GetDimLen(XDIM); pos[XDIM]++)
    {
      for(pos[YDIM] = 0; pos[YDIM] < _DataGrid->GetDimLen(YDIM); pos[YDIM]++)
      {
        if(_DataGrid->HasData(pos))
        {
          _DataGrid->GetElemAsVariant(pos, &value);
          if(0 > VariantCompare(value, _MinVal)) _MinVal = value;
          if(0 < VariantCompare(value, _MaxVal)) _MaxVal = value;
        }
      }
    }

    printf("min=%f, max=%f\n", 
           VariantValueAsDouble(_MinVal), VariantValueAsDouble(_MaxVal));
  }
}
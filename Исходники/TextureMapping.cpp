// convert from old version of texture mapping defintion
void CMappingDefinition::ReadOld_t(CTStream &strm) // throw char *
{
  // old texture mapping orientation and offsets structure
  // - obsolete - used only for loading old worlds
  class CTextureMapping_old {
  public:
    ULONG tm_ulFlags;       // flags
    ANGLE tm_aRotation;     // angle of texture rotation
    FLOAT tm_fOffsetU;      // texture offsets (in meters)
    FLOAT tm_fOffsetV;
  } tmo;
  strm.Read_t(&tmo, sizeof(tmo));

  FLOAT fSin = Sin(tmo.tm_aRotation);
  FLOAT fCos = Cos(tmo.tm_aRotation);

  md_fUOffset = -tmo.tm_fOffsetU;
  md_fVOffset = -tmo.tm_fOffsetV;
  md_fUoS = +fCos;
  md_fUoT = -fSin;
  md_fVoS = +fSin;
  md_fVoT = +fCos;
}
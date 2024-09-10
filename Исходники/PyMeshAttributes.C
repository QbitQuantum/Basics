std::string
PyMeshAttributes_ToString(const MeshAttributes *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    if(atts->GetLegendFlag())
        SNPRINTF(tmpStr, 1000, "%slegendFlag = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%slegendFlag = 0\n", prefix);
    str += tmpStr;
    const char *lineStyle_values[] = {"SOLID", "DASH", "DOT", "DOTDASH"};
    SNPRINTF(tmpStr, 1000, "%slineStyle = %s%s  # SOLID, DASH, DOT, DOTDASH\n", prefix, prefix, lineStyle_values[atts->GetLineStyle()]);
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%slineWidth = %d\n", prefix, atts->GetLineWidth());
    str += tmpStr;
    const unsigned char *meshColor = atts->GetMeshColor().GetColor();
    SNPRINTF(tmpStr, 1000, "%smeshColor = (%d, %d, %d, %d)\n", prefix, int(meshColor[0]), int(meshColor[1]), int(meshColor[2]), int(meshColor[3]));
    str += tmpStr;
    const char *meshColorSource_names = "Foreground, MeshCustom";
    switch (atts->GetMeshColorSource())
    {
      case MeshAttributes::Foreground:
          SNPRINTF(tmpStr, 1000, "%smeshColorSource = %sForeground  # %s\n", prefix, prefix, meshColorSource_names);
          str += tmpStr;
          break;
      case MeshAttributes::MeshCustom:
          SNPRINTF(tmpStr, 1000, "%smeshColorSource = %sMeshCustom  # %s\n", prefix, prefix, meshColorSource_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    const char *opaqueColorSource_names = "Background, OpaqueCustom";
    switch (atts->GetOpaqueColorSource())
    {
      case MeshAttributes::Background:
          SNPRINTF(tmpStr, 1000, "%sopaqueColorSource = %sBackground  # %s\n", prefix, prefix, opaqueColorSource_names);
          str += tmpStr;
          break;
      case MeshAttributes::OpaqueCustom:
          SNPRINTF(tmpStr, 1000, "%sopaqueColorSource = %sOpaqueCustom  # %s\n", prefix, prefix, opaqueColorSource_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    const char *opaqueMode_names = "Auto, On, Off";
    switch (atts->GetOpaqueMode())
    {
      case MeshAttributes::Auto:
          SNPRINTF(tmpStr, 1000, "%sopaqueMode = %sAuto  # %s\n", prefix, prefix, opaqueMode_names);
          str += tmpStr;
          break;
      case MeshAttributes::On:
          SNPRINTF(tmpStr, 1000, "%sopaqueMode = %sOn  # %s\n", prefix, prefix, opaqueMode_names);
          str += tmpStr;
          break;
      case MeshAttributes::Off:
          SNPRINTF(tmpStr, 1000, "%sopaqueMode = %sOff  # %s\n", prefix, prefix, opaqueMode_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    SNPRINTF(tmpStr, 1000, "%spointSize = %g\n", prefix, atts->GetPointSize());
    str += tmpStr;
    const unsigned char *opaqueColor = atts->GetOpaqueColor().GetColor();
    SNPRINTF(tmpStr, 1000, "%sopaqueColor = (%d, %d, %d, %d)\n", prefix, int(opaqueColor[0]), int(opaqueColor[1]), int(opaqueColor[2]), int(opaqueColor[3]));
    str += tmpStr;
    const char *smoothingLevel_names = "None, Fast, High";
    switch (atts->GetSmoothingLevel())
    {
      case MeshAttributes::None:
          SNPRINTF(tmpStr, 1000, "%ssmoothingLevel = %sNone  # %s\n", prefix, prefix, smoothingLevel_names);
          str += tmpStr;
          break;
      case MeshAttributes::Fast:
          SNPRINTF(tmpStr, 1000, "%ssmoothingLevel = %sFast  # %s\n", prefix, prefix, smoothingLevel_names);
          str += tmpStr;
          break;
      case MeshAttributes::High:
          SNPRINTF(tmpStr, 1000, "%ssmoothingLevel = %sHigh  # %s\n", prefix, prefix, smoothingLevel_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    if(atts->GetPointSizeVarEnabled())
        SNPRINTF(tmpStr, 1000, "%spointSizeVarEnabled = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%spointSizeVarEnabled = 0\n", prefix);
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%spointSizeVar = \"%s\"\n", prefix, atts->GetPointSizeVar().c_str());
    str += tmpStr;
    const char *pointType_names = "Box, Axis, Icosahedron, Octahedron, Tetrahedron, "
        "SphereGeometry, Point, Sphere";
    switch (atts->GetPointType())
    {
      case MeshAttributes::Box:
          SNPRINTF(tmpStr, 1000, "%spointType = %sBox  # %s\n", prefix, prefix, pointType_names);
          str += tmpStr;
          break;
      case MeshAttributes::Axis:
          SNPRINTF(tmpStr, 1000, "%spointType = %sAxis  # %s\n", prefix, prefix, pointType_names);
          str += tmpStr;
          break;
      case MeshAttributes::Icosahedron:
          SNPRINTF(tmpStr, 1000, "%spointType = %sIcosahedron  # %s\n", prefix, prefix, pointType_names);
          str += tmpStr;
          break;
      case MeshAttributes::Octahedron:
          SNPRINTF(tmpStr, 1000, "%spointType = %sOctahedron  # %s\n", prefix, prefix, pointType_names);
          str += tmpStr;
          break;
      case MeshAttributes::Tetrahedron:
          SNPRINTF(tmpStr, 1000, "%spointType = %sTetrahedron  # %s\n", prefix, prefix, pointType_names);
          str += tmpStr;
          break;
      case MeshAttributes::SphereGeometry:
          SNPRINTF(tmpStr, 1000, "%spointType = %sSphereGeometry  # %s\n", prefix, prefix, pointType_names);
          str += tmpStr;
          break;
      case MeshAttributes::Point:
          SNPRINTF(tmpStr, 1000, "%spointType = %sPoint  # %s\n", prefix, prefix, pointType_names);
          str += tmpStr;
          break;
      case MeshAttributes::Sphere:
          SNPRINTF(tmpStr, 1000, "%spointType = %sSphere  # %s\n", prefix, prefix, pointType_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    if(atts->GetShowInternal())
        SNPRINTF(tmpStr, 1000, "%sshowInternal = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%sshowInternal = 0\n", prefix);
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%spointSizePixels = %d\n", prefix, atts->GetPointSizePixels());
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%sopacity = %g\n", prefix, atts->GetOpacity());
    str += tmpStr;
    return str;
}
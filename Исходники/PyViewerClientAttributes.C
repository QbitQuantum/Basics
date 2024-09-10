std::string
PyViewerClientAttributes_ToString(const ViewerClientAttributes *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    const char *renderingType_names = "None, Image, Data";
    switch (atts->GetRenderingType())
    {
      case ViewerClientAttributes::None:
          SNPRINTF(tmpStr, 1000, "%srenderingType = %sNone  # %s\n", prefix, prefix, renderingType_names);
          str += tmpStr;
          break;
      case ViewerClientAttributes::Image:
          SNPRINTF(tmpStr, 1000, "%srenderingType = %sImage  # %s\n", prefix, prefix, renderingType_names);
          str += tmpStr;
          break;
      case ViewerClientAttributes::Data:
          SNPRINTF(tmpStr, 1000, "%srenderingType = %sData  # %s\n", prefix, prefix, renderingType_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    SNPRINTF(tmpStr, 1000, "%sid = %d\n", prefix, atts->GetId());
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%stitle = \"%s\"\n", prefix, atts->GetTitle().c_str());
    str += tmpStr;
    {   const intVector &windowIds = atts->GetWindowIds();
        SNPRINTF(tmpStr, 1000, "%swindowIds = (", prefix);
        str += tmpStr;
        for(size_t i = 0; i < windowIds.size(); ++i)
        {
            SNPRINTF(tmpStr, 1000, "%d", windowIds[i]);
            str += tmpStr;
            if(i < windowIds.size() - 1)
            {
                SNPRINTF(tmpStr, 1000, ", ");
                str += tmpStr;
            }
        }
        SNPRINTF(tmpStr, 1000, ")\n");
        str += tmpStr;
    }
    SNPRINTF(tmpStr, 1000, "%simageWidth = %d\n", prefix, atts->GetImageWidth());
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%simageHeight = %d\n", prefix, atts->GetImageHeight());
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%simageResolutionPcnt = %g\n", prefix, atts->GetImageResolutionPcnt());
    str += tmpStr;
    if(atts->GetExternalClient())
        SNPRINTF(tmpStr, 1000, "%sexternalClient = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%sexternalClient = 0\n", prefix);
    str += tmpStr;
    return str;
}
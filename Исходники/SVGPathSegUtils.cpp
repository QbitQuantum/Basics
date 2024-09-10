/* static */ void
SVGPathSegUtils::GetValueAsString(const float* aSeg, nsAString& aValue)
{
  // Adding new seg type? Is the formatting below acceptable for the new types?
  PR_STATIC_ASSERT(NS_SVG_PATH_SEG_LAST_VALID_TYPE ==
                     nsIDOMSVGPathSeg::PATHSEG_CURVETO_QUADRATIC_SMOOTH_REL);
  PR_STATIC_ASSERT(NS_SVG_PATH_SEG_MAX_ARGS == 7);

  PRUint32 type = DecodeType(aSeg[0]);
  PRUnichar typeAsChar = GetPathSegTypeAsLetter(type);

  // Special case arcs:
  if (IsArcType(type)) {
    bool largeArcFlag = aSeg[4] != 0.0f;
    bool sweepFlag = aSeg[5] != 0.0f;
    nsTextFormatter::ssprintf(aValue,
                              NS_LITERAL_STRING("%c%g,%g %g %d,%d %g,%g").get(),
                              typeAsChar, aSeg[1], aSeg[2], aSeg[3],
                              largeArcFlag, sweepFlag, aSeg[6], aSeg[7]);
  } else {

    switch (ArgCountForType(type)) {
    case 0:
      aValue = typeAsChar;
      break;

    case 1:
      nsTextFormatter::ssprintf(aValue, NS_LITERAL_STRING("%c%g").get(),
                                typeAsChar, aSeg[1]);
      break;

    case 2:
      nsTextFormatter::ssprintf(aValue, NS_LITERAL_STRING("%c%g,%g").get(),
                                typeAsChar, aSeg[1], aSeg[2]);
      break;

    case 4:
      nsTextFormatter::ssprintf(aValue, NS_LITERAL_STRING("%c%g,%g %g,%g").get(),
                                typeAsChar, aSeg[1], aSeg[2], aSeg[3], aSeg[4]);
      break;

    case 6:
      nsTextFormatter::ssprintf(aValue,
                                NS_LITERAL_STRING("%c%g,%g %g,%g %g,%g").get(),
                                typeAsChar, aSeg[1], aSeg[2], aSeg[3], aSeg[4],
                                aSeg[5], aSeg[6]);
      break;

    default:
      NS_ABORT_IF_FALSE(false, "Unknown segment type");
      aValue = NS_LITERAL_STRING("<unknown-segment-type>").get();
      return;
    }
  }
  
  // nsTextFormatter::ssprintf is one of the nsTextFormatter methods that
  // randomly appends '\0' to its output string, which means that the length
  // of the output string is one too long. We need to manually remove that '\0'
  // until nsTextFormatter is fixed.
  //
  if (aValue[aValue.Length() - 1] == PRUnichar('\0')) {
    aValue.SetLength(aValue.Length() - 1);
  }
}
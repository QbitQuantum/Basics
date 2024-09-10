String UrlUtils::CanonicalizePath(
    /* [in] */ const String& _path,
    /* [in] */ Boolean discardRelativePrefix)
{
    String path = _path;
    // the first character of the current path segment
    Int32 segmentStart = 0;

    // the number of segments seen thus far that can be erased by sequences of '..'.
    Int32 deletableSegments = 0;

    for (Int32 i = 0; i <= path.GetLength(); ) {
        Int32 nextSegmentStart;
        if (i == path.GetLength()) {
            nextSegmentStart = i;
        } else if (path.GetChar(i) == '/') {
            nextSegmentStart = i + 1;
        } else {
            i++;
            continue;
        }

        /*
         * We've encountered either the end of a segment or the end of the
         * complete path. If the final segment was "." or "..", remove the
         * appropriate segments of the path.
         */
        if (i == segmentStart + 1 && path.RegionMatches(segmentStart, String("."), 0, 1)) {
            // Given "abc/def/./ghi", remove "./" to get "abc/def/ghi".
            String part = path.Substring(0, segmentStart);
            part += path.Substring(nextSegmentStart);
            path = part;
            i = segmentStart;
        }
        else if (i == segmentStart + 2 && path.RegionMatches(segmentStart, String(".."), 0, 2)) {
            if (deletableSegments > 0 || discardRelativePrefix) {
                // Given "abc/def/../ghi", remove "def/../" to get "abc/ghi".
                deletableSegments--;
                Int32 prevSegmentStart = path.LastIndexOf('/', segmentStart - 2) + 1;
                String part = path.Substring(0, prevSegmentStart);
                part += path.Substring(nextSegmentStart);
                path = part;
                i = segmentStart = prevSegmentStart;
            }
            else {
                // There's no segment to delete; this ".." segment must be retained.
                i++;
                segmentStart = i;
            }
        }
        else {
            if (i > 0) {
                deletableSegments++;
            }
            i++;
            segmentStart = i;
        }
    }
    return path;
}
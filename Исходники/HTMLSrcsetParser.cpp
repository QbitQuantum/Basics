static void parseImageCandidatesFromSrcsetAttribute(StringView attribute, Vector<ImageCandidate>& imageCandidates)
{
    // FIXME: We should consider replacing the direct pointers in the parsing process with StringView and positions.
    if (attribute.is8Bit())
        parseImageCandidatesFromSrcsetAttribute<LChar>(attribute.characters8(), attribute.length(), imageCandidates);
    else
        parseImageCandidatesFromSrcsetAttribute<UChar>(attribute.characters16(), attribute.length(), imageCandidates);
}
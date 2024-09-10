/*----------------------------------------------------------------------------------------------
	Return true if the two characters represent runs that can be rendered in the same
	segment.
----------------------------------------------------------------------------------------------*/
bool FwGrTxtSrc::sameSegment(toffset ich1, toffset ich2)
{
	int ichMinBogus, ichLimBogus;
	LgCharRenderProps chrp1, chrp2;
	GrResult res = (GrResult)m_qts->GetCharProps(GrToVwOffset(ich1), &chrp1, &ichMinBogus, &ichLimBogus);
	if (ResultFailed(res))
		return false;
	res = (GrResult)m_qts->GetCharProps(GrToVwOffset(ich2), &chrp2, &ichMinBogus, &ichLimBogus);
	if (ResultFailed(res))
		return false;

	if (u_strcmp(chrp1.szFaceName, chrp2.szFaceName) != 0)
		return false;
	if (chrp1.ws != chrp2.ws)
	{
		// Can't compare default fonts for different writing systems.
		StrUni stuFace;
		stuFace.Assign(chrp1.szFaceName, 8);
		if (stuFace == L"<default")
			return false;
	}
	if (chrp1.dympHeight != chrp2.dympHeight)
		return false;
	if (chrp1.ttvBold != chrp2.ttvBold)
		return false;
	if (chrp1.ttvItalic != chrp2.ttvItalic)
		return false;
	if (chrp1.fWsRtl != chrp2.fWsRtl)
		return false;
	if (chrp1.nDirDepth != chrp2.nDirDepth)
		return false;
	if (chrp1.ssv != chrp2.ssv)
		return false;
	if (chrp1.dympOffset != chrp2.dympOffset)
		return false; // eventually improve on this

	return true;
}
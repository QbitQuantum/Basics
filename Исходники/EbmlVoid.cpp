uint64 EbmlVoid::ReplaceWith(EbmlElement & EltToReplaceWith, IOCallback & output, bool ComeBackAfterward, bool bWithDefault)
{
	EltToReplaceWith.UpdateSize(bWithDefault);
	if (HeadSize() + GetSize() < EltToReplaceWith.GetSize() + EltToReplaceWith.HeadSize()) {
		// the element can't be written here !
		return INVALID_FILEPOS_T;
	}
	if (HeadSize() + GetSize() - EltToReplaceWith.GetSize() - EltToReplaceWith.HeadSize() == 1) {
		// there is not enough space to put a filling element
		return INVALID_FILEPOS_T;
	}

	uint64 CurrentPosition = output.getFilePointer();

	output.setFilePointer(GetElementPosition());
	EltToReplaceWith.Render(output, bWithDefault);

	if (HeadSize() + GetSize() - EltToReplaceWith.GetSize() - EltToReplaceWith.HeadSize() > 1) {
	  // fill the rest with another void element
	  EbmlVoid aTmp;
	  aTmp.SetSize_(HeadSize() + GetSize() - EltToReplaceWith.GetSize() - EltToReplaceWith.HeadSize() - 1); // 1 is the length of the Void ID
	  int HeadBefore = aTmp.HeadSize();
	  aTmp.SetSize_(aTmp.GetSize() - CodedSizeLength(aTmp.GetSize(), aTmp.GetSizeLength(), aTmp.IsFiniteSize()));
	  int HeadAfter = aTmp.HeadSize();
	  if (HeadBefore != HeadAfter) {
		  aTmp.SetSizeLength(CodedSizeLength(aTmp.GetSize(), aTmp.GetSizeLength(), aTmp.IsFiniteSize()) - (HeadAfter - HeadBefore));
	  }
	  aTmp.RenderHead(output, false, bWithDefault); // the rest of the data is not rewritten
	}

	if (ComeBackAfterward) {
		output.setFilePointer(CurrentPosition);
	}

	return GetSize() + HeadSize();
}
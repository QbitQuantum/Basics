bool BrowseDlg::setPath(const tstring& aPath, bool forced) {
	if (aPath.empty())
		return false;

	checkinit();

	auto target = Text::toT(Util::validatePath(Text::fromT(aPath)));

	// Prefill the filename
	auto fileName = Util::getFileName(target);
	if (!fileName.empty()) {
		pfd->SetFileName(fileName.c_str());
	}

	// Set the given directory
	CComPtr<IShellItem> psiFolder;
	if (SUCCEEDED(SHCreateItemFromParsingName(Util::getFilePath(target).c_str(), NULL, IID_PPV_ARGS(&psiFolder)))) {
		if (forced) {
			check(pfd->SetFolder(psiFolder));
		} else {
			check(pfd->SetDefaultFolder(psiFolder));
		}
	}

	return true;
}
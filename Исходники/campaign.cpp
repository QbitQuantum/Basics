bool Campaign::readCampaign(const Common::UString &mmdFile, CampaignDescription &desc) {
	Common::ReadFile *file = new Common::ReadFile;
	if (!file->open(mmdFile)) {
		delete file;
		return false;
	}

	Aurora::GFF3File *gff = 0;
	try {
		gff = new Aurora::GFF3File(file, MKTAG('M', 'M', 'D', ' '));
	} catch (...) {
		return false;
	}

	gff->getTopLevel().getLocString("Meta_Name", desc.name);
	gff->getTopLevel().getLocString("Meta_Desc", desc.description);

	delete gff;

	desc.file = mmdFile;
	desc.tag  = Common::FilePath::getStem(mmdFile).toLower();

	return true;
}
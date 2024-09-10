void QxCommand::restore(QVariantList list)
{
	int i = 0;
	icon_.loadFromData(list.at(i++).toByteArray(), "PNG");
	description_ = list.at(i++).toString();
	keys_ = list.at(i++).toString();
	script_ = list.at(i++).toString();
	target_ = list.at(i++).toInt();
	if (i < list.length()) {
		autoSaveFile_ = list.at(i++).toBool();
		if (i < list.length()) 
			autoOpenNextLink_ = list.at(i++).toBool();
		else
			autoOpenNextLink_ = false;
	}
	else
		autoSaveFile_ = false;
}
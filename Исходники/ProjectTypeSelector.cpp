/*	isVolume
*	checks if selected file is a volume
*	if yes, returns true
*/	
bool
ProjectTypeSelector::isVolume()
{
	BString *SelectedFile = (BString*)FileList->FirstItem();
	BString SelectedFileTMP;
	BVolumeRoster objVolumeRoster;
	objVolumeRoster.Rewind();
	BVolume objVolume;
	char chVolumeName[B_FILE_NAME_LENGTH];
	
	SelectedFile->CopyInto(SelectedFileTMP, 0, (int)SelectedFile->Length());	
	SelectedFileTMP.RemoveAll("/");
	while(objVolumeRoster.GetNextVolume(&objVolume) != B_BAD_VALUE) {
		objVolume.GetName(chVolumeName);
		
		if(SelectedFileTMP.Compare(chVolumeName) == 0 && objVolume.IsReadOnly()) {
			fSizeOfFiles = objVolume.Capacity();
			return true;
		}
	}
	
	return false;
}
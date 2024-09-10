 /// \brief
 ///   Create or return an existing prefab type with the passed filename.
 inline VPrefab *LoadPrefab(const char *szFilename) {return (VPrefab *)LoadResource(szFilename);}
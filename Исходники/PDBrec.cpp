int PDBrec::InstallMapOfSEGIDstoChains(const std::string map) {
   int mapentries = 0;
   if (!map.empty()) {
      char SEGmapBuffer[SEGMAPBUFFSZ+1];
      std::string sid;
      char   cid = ' ';
      strncpy(SEGmapBuffer, map.c_str(), SEGMAPBUFFSZ);
      SEGmapBuffer[SEGMAPBUFFSZ] = '\0';
      char *t = strtok(SEGmapBuffer, ","); // 1st segid
      while (t) {
         sid = FormatSegToChainKey(t);
	 t = strtok(NULL, ","); // chainid
	 if (t) {
	    cid = (*t && (*t != '_')) ? toupper(t[0])
	                              : ' ';
//	    if (*sid && cid) {
	    if (!sid.empty() && cid) {
			_SEGtoChainMap.insert(std::make_pair(sid, cid));
	       mapentries++;
	    }
	    t = strtok(NULL, ","); // next segid
         }
      }
      if (mapentries) { _MappingSEGIDtoChains = TRUE; }
   }
   return mapentries;
}
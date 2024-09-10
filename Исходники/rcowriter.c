// packing: use RCO_DATA_COMPRESSION_* constants
uint8_t
write_rco (rRCOFile * rco, char *fn, writerco_options opts)
{
  uint32_t i;
  rRCOFile_writehelper rcoH;

  // delete file if exists
  if (file_exists (fn)) {
    if (remove (fn)) {
      error ("Unable to write to file %s", fn);
      return FALSE;
    }
  }

  rcoH.rco = rco;
  rcoH.fp = fopen (fn, "wb");
  if (!rcoH.fp) {
    error ("Unable to open file %s", fn);
    return FALSE;
  }

  PRFHeader header;

  header.signature = RCO_SIGNATURE;
  header.version =
      (opts.packHeader == RCO_DATA_COMPRESSION_RLZ ? 0x95 : opts.packHeader ==
      RCO_DATA_COMPRESSION_ZLIB ? 0x90 : 0x71);
  if (rco->verId) {		// we won't actually use specified value,
    // rather, we'll require using the minimum
    // version from above
    if (rco->verId > header.version)
      header.version = rco->verId;
  }
  header.null = 0;
  header.compression = (opts.packHeader << 4) | (rco->umdFlag & 0xF);

  header.pMainTable = 0xA4;	// pretty much always the case
  // set other sections to nothing for now
  header.pVSMXTable = header.pTextTable = header.pSoundTable =
      header.pModelTable = header.pImgTable = header.pObjTable =
      header.pAnimTable = RCO_NULL_PTR;
  header.pUnknown = header.pFontTable = RCO_NULL_PTR;

  // don't know positions of text/label/event data too, but we do know the
  // lengths for label/events
  // header.pTextData = header.pLabelData = header.pEventData = 0;
  header.lLabelData = rco->labelsLen;
  header.lEventData = rco->eventsLen;
  header.lTextData = 0;

  // set pointer sections to blank too
  header.pTextPtrs = header.pImgPtrs = header.pModelPtrs = header.pSoundPtrs =
      header.pObjPtrs = header.pAnimPtrs = RCO_NULL_PTR;

  header.lTextPtrs = header.lImgPtrs = header.lModelPtrs = header.lSoundPtrs =
      header.lObjPtrs = header.lAnimPtrs = 0;

  // also blank...
  header.pImgData = header.pSoundData = header.pModelData = RCO_NULL_PTR;
  header.lImgData = header.lSoundData = header.lModelData = 0;

  header.unknown[0] = header.unknown[1] = header.unknown[2] = 0xFFFFFFFF;

  // write resources to a separate file to get around the issue of unknown
  // packed size when writing the header (and you can't change it backed after
  // the header is packed...)
  FILE *fTmp = NULL;

  if ((rco->tblImage && rco->tblImage->numSubentries)
      || (rco->tblSound && rco->tblSound->numSubentries)
      || (rco->tblModel && rco->tblModel->numSubentries)) {
    uint32_t totalPackedLen = 0;
    rRCOEntry *rcoNode;

    fTmp = tmpfile ();

    if (rco->tblImage && rco->tblImage->numSubentries) {
      for (rcoNode = rco->tblImage->firstChild; rcoNode;
	  rcoNode = rcoNode->next) {
	// our compression decision thing
	uint32_t c = ((rRCOImgModelEntry *) (rcoNode->extra))->compression;

	if (((rRCOImgModelEntry *) (rcoNode->extra))->format < RCO_IMG_BMP) {
	  if (opts.packImgCompr != -1)
	    c = opts.packImgCompr;
	} else {
	  if (opts.packImg != -1)
	    c = opts.packImg;
	}

	if (rcoNode->srcLenUnpacked) {
	  rcoNode->srcLen = rco_write_resource (fTmp, rcoNode, c, &opts, rco);
	  if (!rcoNode->srcLen && rcoNode->labelOffset != RCO_NULL_PTR)
	    warning ("[resource] Can't write image resource '%s'!",
		rco->labels + rcoNode->labelOffset);
	}
	rcoNode->srcCompression = c;
	rcoNode->srcAddr = totalPackedLen;

	totalPackedLen +=
	    (rcoNode->srcLen % 4 ? (rcoNode->srcLen / 4) * 4 +
	    4 : rcoNode->srcLen);
      }
      header.lImgData = totalPackedLen;
    }

    totalPackedLen = 0;
    if (rco->tblSound && rco->tblSound->numSubentries) {
      for (rcoNode = rco->tblSound->firstChild; rcoNode;
	  rcoNode = rcoNode->next) {
	if (rcoNode->srcLenUnpacked) {
	  uint32_t packedLen = rco_write_resource (fTmp, rcoNode,
	      RCO_DATA_COMPRESSION_NONE,
	      &opts,
	      rco);

	  if (!packedLen && rcoNode->labelOffset != RCO_NULL_PTR)
	    warning ("[resource] Can't write sound resource '%s'!",
		rco->labels + rcoNode->labelOffset);
	  totalPackedLen += ALIGN_TO_4 (packedLen);
	  // if(totalPackedLen %4) totalPackedLen += 4-(totalPackedLen%4);
	}
      }
      header.lSoundData = totalPackedLen;
    }

    totalPackedLen = 0;
    if (rco->tblModel && rco->tblModel->numSubentries) {
      for (rcoNode = rco->tblModel->firstChild; rcoNode;
	  rcoNode = rcoNode->next) {
	uint32_t c = ((rRCOImgModelEntry *) (rcoNode->extra))->compression;

	if (opts.packModel != -1)
	  c = opts.packModel;

	if (rcoNode->srcLenUnpacked) {
	  rcoNode->srcLen = rco_write_resource (fTmp, rcoNode, c, &opts, rco);
	  if (!rcoNode->srcLen && rcoNode->labelOffset != RCO_NULL_PTR)
	    warning ("[resource] Can't write model resource '%s'!",
		rco->labels + rcoNode->labelOffset);
	}
	rcoNode->srcCompression = c;
	rcoNode->srcAddr = totalPackedLen;

	totalPackedLen +=
	    (rcoNode->srcLen % 4 ? (rcoNode->srcLen / 4) * 4 +
	    4 : rcoNode->srcLen);
      }
      header.lModelData = totalPackedLen;
    }

    rewind (fTmp);
  }

  filewrite (rcoH.fp, &header, sizeof (header));

  rcoH.tables = 0;

  // if compressing, write to memory
  if (opts.packHeader) {
    rcoH.tables = malloc (RCO_WRITE_MEM_BUFFER);
    rcoH.memPos = rcoH.tablesSize = 0;
    rcoH.tablesBuffered = RCO_WRITE_MEM_BUFFER;
    rcoH.memOffset = ftell (rcoH.fp);
  }

  rcoH.sizeImg = rcoH.sizeModel = rcoH.sizeSound = rcoH.sizeText = 0;
  rcoH.longestLangData = 0;

  write_entry (&rcoH, &(rco->tblMain), 0xA4	/* typically where the main
						 * table is written to */ , 0,
      TRUE);

  // fix up object/anim extra data
  {
    if (rco->tblObj)
      rco_write_fix_refs (rco->tblObj, &rcoH, rco, RCO_OBJ_EXTRA_LEN,
	  RCO_OBJ_EXTRA_LEN_NUM, TRUE);
    if (rco->tblAnim)
      rco_write_fix_refs (rco->tblAnim, &rcoH, rco, RCO_ANIM_EXTRA_LEN,
	  RCO_ANIM_EXTRA_LEN_NUM, FALSE);
  }

  {				// write hashtable data

    /* { // special case for text hashes if(rco->numPtrText) { header.pTextPtrs
     * = rcowrite_ftell(&rcoH); for(i=0; i<rco->numPtrText; i++) { uint32_t
     * writePtr = 0; if(rco->ptrText[i].textEntry && rco->ptrText[i].index)
     * writePtr = rco->ptrText[i].textEntry->offset + sizeof(RCOEntry) +
     * sizeof(RCOTextEntry) + (rco->ptrText[i].index -
     * ((rRCOTextEntry*)(rco->ptrText[i].textEntry->extra))->indexes)*sizeof(RCOTextIndex);
     * rco_fwrite(&rcoH, &writePtr, sizeof(uint32_t)); } } } */
    if (rco->tblText) {
      header.pTextPtrs = rcowrite_ftell (&rcoH);
      header.lTextPtrs = 0;

      // generate sorted list of text entries, sorted by languageID
      rRCOEntry **sList = make_sorted_list_of_subentries (rco->tblText,
	  text_hash_table_qsort);

      for (i = 0; i < rco->tblText->numSubentries; i++)
	header.lTextPtrs += write_text_hash_table (&rcoH, sList[i], rco);
      free (sList);

      header.lTextPtrs *= sizeof (uint32_t);
    }

    if (rco->tblImage) {
      header.pImgPtrs = rcowrite_ftell (&rcoH);
      header.lImgPtrs =
	  write_hash_table (&rcoH, rco->tblImage, rco) * sizeof (uint32_t);
    }
    if (rco->tblModel) {
      header.pModelPtrs = rcowrite_ftell (&rcoH);
      header.lModelPtrs =
	  write_hash_table (&rcoH, rco->tblModel, rco) * sizeof (uint32_t);
    }
    if (rco->tblSound) {
      header.pSoundPtrs = rcowrite_ftell (&rcoH);
      header.lSoundPtrs =
	  write_hash_table (&rcoH, rco->tblSound, rco) * sizeof (uint32_t);
    }
    if (rco->tblObj) {
      header.pObjPtrs = rcowrite_ftell (&rcoH);
      header.lObjPtrs =
	  write_hash_table (&rcoH, rco->tblObj, rco) * sizeof (uint32_t);
    }
    if (rco->tblAnim) {
      header.pAnimPtrs = rcowrite_ftell (&rcoH);
      header.lAnimPtrs =
	  write_hash_table (&rcoH, rco->tblAnim, rco) * sizeof (uint32_t);
    }
    /*
     * #define RCO_WRITERCO_WRITE_PTR_SECT(pd, pl, hp) { \ if(pl) { \ hp =
     * rcowrite_ftell(&rcoH); \ for(i=0; i<pl; i++) { \ if(pd[i]) \
     * rco_fwrite(&rcoH, &(((rRCOEntry*)(pd[i]))->offset), sizeof(uint32_t)); \
     * else { \ uint32_t zero = 0; \ rco_fwrite(&rcoH, &zero, sizeof(uint32_t)); \
     * } \ } \ } \ } //RCO_WRITERCO_WRITE_PTR_SECT(rco->ptrText,
     * rco->numPtrText, header.pTextPtrs);
     * RCO_WRITERCO_WRITE_PTR_SECT(rco->ptrImg, rco->numPtrImg,
     * header.pImgPtrs); RCO_WRITERCO_WRITE_PTR_SECT(rco->ptrModel,
     * rco->numPtrModel, header.pModelPtrs);
     * RCO_WRITERCO_WRITE_PTR_SECT(rco->ptrSound, rco->numPtrSound,
     * header.pSoundPtrs); RCO_WRITERCO_WRITE_PTR_SECT(rco->ptrObj,
     * rco->numPtrObj, header.pObjPtrs);
     * RCO_WRITERCO_WRITE_PTR_SECT(rco->ptrAnim, rco->numPtrAnim,
     * header.pAnimPtrs); */
  }

  {				// write label/event data (and text if
    // applicable)

    // write text (note, old behaviour - newer RCOs have text written in a
    // different location)
    if (!opts.packText && rco->tblText && rco->tblText->numSubentries) {
      rRCOEntry *rcoNode;

      header.pTextData = rcowrite_ftell (&rcoH);
      header.lTextData = rcoH.sizeText;
      for (rcoNode = rco->tblText->firstChild; rcoNode; rcoNode = rcoNode->next) {
	rco_write_text_resource (&rcoH, rcoNode, RCO_DATA_COMPRESSION_NONE,
	    &opts, ((rRCOTextEntry *) (rcoNode->extra))->lang,
	    (rco->tblText->lastChild == rcoNode));
      }
    }
    // write label+event data
    header.pLabelData = rcowrite_ftell (&rcoH);
    if (rco->labelsLen)
      rco_fwrite (&rcoH, rco->labels, rco->labelsLen);
    header.pEventData = rcowrite_ftell (&rcoH);
    if (rco->eventsLen)
      rco_fwrite (&rcoH, rco->events, rco->eventsLen);
    else if (rco->tblObj || rco->tblAnim) {	// weird case: if there's
      // object entries, there will
      // be 4 bytes for events; I'll
      // assume this covers anim as
      // well (although there isn't
      // an RCO with anim that
      // doesn't have objects)
      uint32_t zero = 0;

      rco_fwrite (&rcoH, &zero, sizeof (zero));
      header.lEventData = sizeof (zero);
    }
    // the text pointer is weird in that if there's no text, it's set equal to
    // the label pointer; even weirder, some RCOs have a null pointer (for
    // FW5.00 all except lftv_* RCOs have null pointers for pTextData if
    // there's no text)
    // my theory: if compressing, it will be RCO_NULL_PTR, otherwise it'll =
    // header.pLabelData
    // if(!header.lTextData) header.pTextData = RCO_NULL_PTR;
    // if(!header.lTextData) header.pTextData = header.pLabelData;
    if (!header.lTextData)
      header.pTextData = (opts.packHeader ? RCO_NULL_PTR : header.pLabelData);
  }

  // flush compression stuff here
  HeaderComprInfo ci;

  if (opts.packHeader) {
    uint8_t *bufferOut = NULL;

    ci.lenLongestText = rcoH.longestLangData;
    ci.lenUnpacked = rcoH.tablesSize;
    ci.lenPacked = 0;

    if (opts.packHeader == RCO_DATA_COMPRESSION_ZLIB) {
      uint32_t bound = compressBound (rcoH.tablesSize);

      bufferOut = (uint8_t *) malloc (bound);
      ci.lenPacked =
	  zlib_compress (rcoH.tables, rcoH.tablesSize, bufferOut, bound,
	  opts.zlibLevel, opts.zlibMethod);
    } else if (opts.packHeader == RCO_DATA_COMPRESSION_RLZ) {
      bufferOut = (uint8_t *) malloc (rcoH.tablesSize);
      ci.lenPacked =
	  rlz_compress (rcoH.tables, rcoH.tablesSize, bufferOut,
	  rcoH.tablesSize, opts.rlzMode);
    } else {
      error ("lulwut?");
      exit (1);
    }
    int comprMisalign = ci.lenPacked % 4;
    uint32_t packedLen = ci.lenPacked;

    if (rco->eSwap)
      es_headerComprInfo (&ci);
    filewrite (rcoH.fp, &ci, sizeof (ci));
    filewrite (rcoH.fp, bufferOut, packedLen);
    free (bufferOut);

    if (comprMisalign) {	// 4 byte align
      uint32_t zero = 0;

      filewrite (rcoH.fp, &zero, 4 - comprMisalign);
    }
  }
  // write text if packing header
  if (opts.packText && rco->tblText && rco->tblText->numSubentries) {
    rRCOEntry *rcoNode;

    // header.pTextData = rcowrite_ftell(&rcoH);
    header.pTextData = ftell (rcoH.fp);
    header.lTextData = 0;	// rcoH.sizeText;
    for (rcoNode = rco->tblText->firstChild; rcoNode; rcoNode = rcoNode->next) {
      header.lTextData +=
	  rco_write_text_resource (&rcoH, rcoNode, opts.packHeader, &opts,
	  ((rRCOTextEntry *) (rcoNode->extra))->lang,
	  (rco->tblText->lastChild == rcoNode));
    }
  }
  // write resources
  /* { uint32_t totalPackedLen = 0; if(rco->tblImage) { header.pImgData =
   * rcowrite_ftell(&rcoH); header.lImgData = rcoH.sizeImg; // TOxDO: this
   * model actually won't work - we have to update the offsets of ALL the
   * entries after packing... for(i=0; i<rco->tblImage->numSubentries; i++) {
   * uint32_t packedSize = rco_write_resource(&rcoH,
   * &(rco->tblImage->subentries[i]), RCO_DATA_COMPRESSION_NONE); // TOxDO:
   * change this // TOxDO: update packed size value uint32_t curFpos =
   * rcowrite_ftell(rcoH.fp); totalPackedLen += (packedSize % 4 ?
   * (packedSize/4)*4+4 : packedSize); } header.lImgData = totalPackedLen; }
   * totalPackedLen = 0; if(rco->tblSound) { header.pSoundData =
   * rcowrite_ftell(&rcoH); header.lSoundData = rcoH.sizeSound; for(i=0;
   * i<rco->tblSound->numSubentries; i++) { totalPackedLen +=
   * rco_write_resource(&rcoH, &(rco->tblSound->subentries[i]),
   * RCO_DATA_COMPRESSION_NONE); if(totalPackedLen %4) totalPackedLen +=
   * 4-(totalPackedLen%4); } header.lSoundData = totalPackedLen; } // TOxDO:
   * write model resources } */

  if ((rco->tblImage && rco->tblImage->numSubentries)
      || (rco->tblSound && rco->tblSound->numSubentries)
      || (rco->tblModel && rco->tblModel->numSubentries)) {
    // update data pointers
    uint32_t pos = ftell (rcoH.fp);

    if (rco->tblImage && rco->tblImage->numSubentries) {
      header.pImgData = pos;
      pos += header.lImgData;
    }
    if (rco->tblSound && rco->tblSound->numSubentries) {
      header.pSoundData = pos;
      pos += header.lSoundData;
    }
    if (rco->tblModel && rco->tblModel->numSubentries) {
      header.pModelData = pos;
      pos += header.lModelData;
    }
    // copy contents of fTmp across (uses a simple buffered copy)
    uint32_t len = header.lImgData + header.lSoundData + header.lModelData;
    uint8_t buffer[65536];

    while (len) {
      uint32_t readAmt = (len > 65536 ? 65536 : len);

      fileread (fTmp, buffer, readAmt);
      filewrite (rcoH.fp, buffer, readAmt);
      len -= readAmt;
    }

    fclose (fTmp);		// this deletes our temp file
  }
  // fix header
  if (rco->tblVSMX)
    header.pVSMXTable = rco->tblVSMX->offset;
  if (rco->tblText)
    header.pTextTable = rco->tblText->offset;
  if (rco->tblSound)
    header.pSoundTable = rco->tblSound->offset;
  if (rco->tblModel)
    header.pModelTable = rco->tblModel->offset;
  if (rco->tblImage)
    header.pImgTable = rco->tblImage->offset;
  if (rco->tblFont)
    header.pFontTable = rco->tblFont->offset;
  if (rco->tblObj)
    header.pObjTable = rco->tblObj->offset;
  if (rco->tblAnim)
    header.pAnimTable = rco->tblAnim->offset;

  rewind (rcoH.fp);
  if (rco->eSwap)
    es_rcoHeader (&header);
  filewrite (rcoH.fp, &header, sizeof (header));

  // TODO: fix resource pointers?
  // TODO: tie things up etc??

  fclose (rcoH.fp);

  return TRUE;
}
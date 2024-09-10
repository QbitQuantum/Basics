  /** 
   * Get the size of a given run 
   * 
   * @param in       Input stream 
   * @param runNo    Run number to search for 
   * @param mc       True for simulations 
   * @param minSize  Least size 
   * 
   * @return true on success 
   */
  Bool_t GetSize(std::istream& in, ULong_t runNo, 
		 Bool_t mc, ULong_t minSize=100000)
  {
    TString line;
    TString tgt2(mc ? "table_row_right" : "ESDs size");
    Int_t   cnt = 0;
    do {
      line.ReadLine(in);
      if (!line.Contains(tgt2)) continue;
      cnt++;
      if (mc && cnt < 3) continue;
      if (!mc) line.ReadLine(in);
      if (fDebug) Info("", line);

      TString ssiz;
      if (mc) { 
	Int_t first       = line.Index(">");
	Int_t last        = line.Index("<",first+1);
	if (first == kNPOS || last == kNPOS) { 
	  Error("GetDir", "Failed to get directory from %s", line.Data());
	  return false;
	}
	ssiz = line(first+1, last-first-1);
      }
      else {
	for (Int_t i = 0; i < line.Length(); i++) { 
	  if (line[i] == '<') break;
	  if (line[i] == ' ' || line[i] == '\t' || line[i] == ',') continue;
	  ssiz.Append(line[i]);
	}
      }
      Long_t size = ssiz.Atoll();
      if (fDebug) Info("", "Got run %lu %lu" , runNo, size);
      if (size < 0) {
	Error("GetSize", "Failed to extract size for run %lu", runNo);
	return false;
      }
      if (ULong_t(size) < minSize) {
	Warning("GetSize","Run %lu does not have enough events %lu",runNo,size);
	return false;
      }
      break;
    } while (!in.eof());
    return true;
  }
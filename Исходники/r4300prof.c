/* main */
int main(int argc, void *argv[])
{
  long lOpStart, lOpEnd;
  int flength, oplistlength, totaltime, proflistlength;
  int samp_unknown, samp_blockend, samp_notcompiled, samp_wrappers, samp_flush;
  int i, j;
  FILE *pfIn;
  r4300op *pOpAddrTable;
  profilehit *pProfTable;
  char *pch, *pchSampleData;

  /* check arguments */
  if (argc < 3)
  {
    printf("Usage: r4300prof r4300addr.dat x86profile.txt\n\n");
    printf("r4300addr.dat  - binary table of r4300 opcodes and corresponding x86 starting addresses\n");
    printf("x86profile.txt - text file containing a list of profile sample counts by x86 address on the heap\n\n");
    return 1;
  }

  /* open r4300 opcode/x86 address table generated from emulator run */
  printf("Loading %s...\n", argv[1]);
  pfIn = fopen(argv[1], "rb");
  if (pfIn == NULL)
  {
    printf("Couldn't open input file: %s\n", argv[1]);
    return 2;
  }

  /* get file length and calculate number of r4300op table entries */
  fseek(pfIn, 0L, SEEK_END);
  flength = (int) ftell(pfIn);
  fseek(pfIn, 0L, SEEK_SET);
  oplistlength = flength / sizeof(r4300op);
  
  /* read the file */
  pOpAddrTable = (r4300op *) malloc(flength);
  if (pOpAddrTable == NULL)
  {
    printf("Failed to allocate %i bytes for OpAddrTable!\n", flength);
    fclose(pfIn);
    return 3;
  }
  fread(pOpAddrTable, 1, flength, pfIn);
  fclose(pfIn);
  printf("%i r4300 instruction locations read.\n", oplistlength);

  /* sort the opcode/address table according to x86addr */
  qsort(pOpAddrTable, oplistlength, sizeof(r4300op), AddrCompare);

  /* remove any 0-length r4300 instructions */
  i = 0;
  j = 0;
  while (i < oplistlength)
  {
    pOpAddrTable[j].mipsop = pOpAddrTable[i].mipsop;
    pOpAddrTable[j].x86addr = pOpAddrTable[i].x86addr;
    i++;
    if (pOpAddrTable[j].x86addr != pOpAddrTable[i].x86addr)
      j++;
  }
  oplistlength = j;
  printf("%i non-empty MIPS instructions.\n", oplistlength);

  /* convert each r4300 opcode to an instruction type index */
  for (i = 0; i < oplistlength; i++)
    if (pOpAddrTable[i].mipsop > 0 || pOpAddrTable[i].mipsop < -16)
      pOpAddrTable[i].mipsop = GetInstrType(pOpAddrTable[i].mipsop);

  /* open the profiling sample data file */
  printf("Loading %s...\n", argv[2]);
  pfIn = fopen(argv[2], "rb");
  if (pfIn == NULL)
  {
    printf("Couldn't open input file: %s\n", argv[2]);
    free(pOpAddrTable);
    return 4;
  }

  /* load it */
  fseek(pfIn, 0L, SEEK_END);
  flength = (int) ftell(pfIn);
  fseek(pfIn, 0L, SEEK_SET);
  pchSampleData = (char *) malloc(flength + 16);
  if (pchSampleData == NULL)
  {
    printf("Failed to allocate %i bytes for pchSampleData!\n", flength + 16);
    fclose(pfIn);
    free(pOpAddrTable);
    return 5;
  }
  fread(pchSampleData, 1, flength, pfIn);
  pchSampleData[flength] = 0;
  fclose(pfIn);
  
  /* count the number of newlines in the ascii-formatted sample data file */
  proflistlength = 1;
  pch = pchSampleData;
  while (pch = strchr(pch, '\n'))
  {
    proflistlength++;
    pch++;
  }
  printf("%i lines in sample data file.\n", proflistlength);
  
  /* extract text data into binary table */
  pProfTable = (profilehit *) malloc(proflistlength * sizeof(profilehit));
  if (pProfTable == NULL)
  {
    printf("Failed to allocate %i bytes for pProfTable!\n", proflistlength * sizeof(profilehit));
    free(pOpAddrTable);
    free(pchSampleData);
    return 6;
  }
  pch = pchSampleData;
  j = 0;
  long long llOffset = 0;
  while (j < proflistlength)
  {
    long lAddress;
    int iSamples;
    float fPercentage;
    char *pchNext = strchr(pch, '\n');
    if (pchNext != NULL) *pchNext++ = 0; // null-terminate this line
    if (strstr(pch, "range:0x") != NULL) // search for offset change
    {
      pch = strstr(pch, "range:0x") + 8; // extract hex value and update our offset
      char *pch2 = pch;
      while (isHex(*pch2)) pch2++;
      *pch2 = 0;
      llOffset = strtoll(pch, NULL, 16);
    }
    else // parse line for sample point
    {
      int rval = ParseProfLine(pch, &lAddress, &iSamples, &fPercentage);
      if (rval != 0)
      {
        pProfTable[j].x86addr = (unsigned long) (lAddress + llOffset);
        pProfTable[j].samples = iSamples;
        j++;
      }
    }
    pch = pchNext;
    if (pch == NULL) break;
  }
  free(pchSampleData);
  proflistlength = j;
  printf("Found %i profile hits.\n", proflistlength);

  /* clear r4300 instruction sample data table */
  for (i = 0; i < 132; i++)
    instr_samples[i] = 0;
    
  /* calculate r4300 instruction profiling data by merging the tables */
  samp_unknown  = 0;
  samp_blockend = 0;
  samp_notcompiled = 0;
  samp_wrappers = 0;
  samp_flush = 0;
  i = 0; // i == OpAddrTable index
  lOpStart = pOpAddrTable[0].x86addr;
  lOpEnd   = pOpAddrTable[1].x86addr;
  for (j = 0; j < proflistlength; j++) // j == pProfTable index
  {
    long lOpx86addr = pProfTable[j].x86addr;
    if (lOpx86addr >= lOpStart && lOpx86addr <= lOpEnd) /* these profile samples lie within current r4300 instruction */
    {
      int instr = pOpAddrTable[i].mipsop;
      if (instr == -1) printf("%lx sample point lies between %i/%lx and %i/%lx\n", lOpx86addr, instr, lOpStart, pOpAddrTable[i+1].mipsop, lOpEnd);

      if (instr == -1)
        samp_unknown += pProfTable[j].samples;
      else if (instr == -2)
        samp_notcompiled += pProfTable[j].samples;
      else if (instr == -3)
        samp_blockend += pProfTable[j].samples;
      else if (instr == -4)
        samp_wrappers += pProfTable[j].samples;
      else if (instr == -5)
        samp_flush += pProfTable[j].samples;
      else
        instr_samples[instr] += pProfTable[j].samples;
      continue;
    }
    if (lOpx86addr < pOpAddrTable[0].x86addr || lOpx86addr >= pOpAddrTable[oplistlength-1].x86addr)
    { /* outside the range of all recompiled instructions */
      samp_unknown += pProfTable[j].samples;
      continue;
    } 
    if (lOpx86addr < lOpStart) /* discontinuity in profile list, go back to start */
    {
      i = 0;
      lOpStart = pOpAddrTable[0].x86addr;
      lOpEnd   = pOpAddrTable[1].x86addr;
      j--;
      continue;
    }
    /* this profile point is ahead of current r4300 instruction */
    do  /* race ahead in r4300 opcode list until we hit this profile sample point */
    {
      i++;
    } while (i+1 < oplistlength && lOpx86addr > pOpAddrTable[i+1].x86addr);
    lOpStart = pOpAddrTable[i].x86addr;
    lOpEnd   = pOpAddrTable[i+1].x86addr;
    if (lOpx86addr < lOpStart || lOpx86addr > lOpEnd)
    {
      printf("Error: lOpx86addr = %lx but lOpStart, lOpEnd = %lx, %lx\n", lOpx86addr, lOpStart, lOpEnd);
      return 7;
    }
    /* we have found the correct r4300 instruction corresponding to this profile point */
    j--;
  }

  /* print the results */
  unsigned int iTypeCount[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  printf("\nInstruction time (samples):\n");
  totaltime = 0;
  for (i = 0; i < 131; i++)
  {
    printf("%8s: %08i  ", instr_name[i], instr_samples[i]);
    if (i % 5 == 4) printf("\n");
    iTypeCount[instr_type[i]] += instr_samples[i];
    totaltime += instr_samples[i];
  }
  int special = samp_flush + samp_wrappers + samp_notcompiled + samp_blockend;
  printf("\n\nSpecial code samples:\n");
  printf("  Regcache flushing: %i\n", samp_flush);
  printf("  Jump wrappers: %i\n", samp_wrappers);
  printf("  NOTCOMPILED: %i\n", samp_notcompiled);
  printf("  block postfix & link samples: %i\n", samp_blockend);

  printf("\nUnaccounted samples: %i\n", samp_unknown);
  printf("Total accounted instruction samples: %i\n", totaltime + special);
  for (i = 0; i < 11; i++)
  {
    printf("%20s: %04.1f%% (%i)\n", instr_typename[i], (float) iTypeCount[i] * 100.0 / totaltime, iTypeCount[i]);
  }

  free(pOpAddrTable);
  free(pProfTable);
  return 0;
}
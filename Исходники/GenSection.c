STATUS
GenSectionCommonLeafSection (
  char    **InputFileName,
  int     InputFileNum,
  UINTN   SectionType,
  FILE    *OutFile
  )
/*++
        
Routine Description:
           
  Generate a leaf section of type other than EFI_SECTION_VERSION
  and EFI_SECTION_USER_INTERFACE. Input file must be well formed.
  The function won't validate the input file's contents. For
  common leaf sections, the input file may be a binary file.
  The utility will add section header to the file.
            
Arguments:
               
  InputFileName  - Name of the input file.
                
  InputFileNum   - Number of input files. Should be 1 for leaf section.

  SectionType    - A valid section type string

  OutFile        - Output file handle

Returns:
                       
  STATUS_ERROR            - can't continue
  STATUS_SUCCESS          - successful return

--*/
{
  UINT64                    InputFileLength;
  FILE                      *InFile;
  UINT8                     *Buffer;
  INTN                      TotalLength;
  EFI_COMMON_SECTION_HEADER CommonSect;
  STATUS                    Status;

  if (InputFileNum > 1) {
    Error (NULL, 0, 0, "invalid parameter", "more than one input file specified");
    return STATUS_ERROR;
  } else if (InputFileNum < 1) {
    Error (NULL, 0, 0, "no input file specified", NULL);
    return STATUS_ERROR;
  }
  //
  // Open the input file
  //
  InFile = fopen (InputFileName[0], "rb");
  if (InFile == NULL) {
    Error (NULL, 0, 0, InputFileName[0], "failed to open input file");
    return STATUS_ERROR;
  }

  Status  = STATUS_ERROR;
  Buffer  = NULL;
  //
  // Seek to the end of the input file so we can determine its size
  //
  fseek (InFile, 0, SEEK_END);
  fgetpos (InFile, &InputFileLength);
  fseek (InFile, 0, SEEK_SET);
  //
  // Fill in the fields in the local section header structure
  //
  CommonSect.Type = (EFI_SECTION_TYPE) SectionType;
  TotalLength     = sizeof (CommonSect) + (INTN) InputFileLength;
  //
  // Size must fit in 3 bytes
  //
  if (TotalLength >= MAX_SECTION_SIZE) {
    Error (NULL, 0, 0, InputFileName[0], "file size (0x%X) exceeds section size limit(%dM).", TotalLength, MAX_SECTION_SIZE>>20);
    goto Done;
  }
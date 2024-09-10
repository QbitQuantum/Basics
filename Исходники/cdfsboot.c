ARC_STATUS
CdfsOpen (
    IN PCHAR FileName,
    IN OPEN_MODE OpenMode,
    IN PULONG FileId
    )

/*++

Routine Description:

    This routine searches the root directory for a file matching FileName.
    If a match is found the dirent for the file is saved and the file is
    opened.

Arguments:

    FileName - Supplies a pointer to a zero terminated file name.

    OpenMode - Supplies the mode of the open.

    FileId - Supplies a pointer to a variable that specifies the file
        table entry that is to be filled in if the open is successful.

Return Value:

    ESUCCESS is returned if the open operation is successful. Otherwise,
    an unsuccessful status is returned that describes the reason for failure.

--*/

{
    ARC_STATUS Status;

    ULONG DeviceId;

    STRING PathName;

    STRING Name;
    BOOLEAN IsDirectory;
    BOOLEAN SearchSucceeded;

    //
    //  Save the address of the file table entry, context area, and the device
    //  id in use.
    //

    CdfsFileTableEntry = &BlFileTable[*FileId];
    CdfsStructureContext = (PCDFS_STRUCTURE_CONTEXT)CdfsFileTableEntry->StructureContext;

    DeviceId = CdfsFileTableEntry->DeviceId;

    //
    // Construct a file name descriptor from the input file name.
    //

    RtlInitString( &PathName, FileName );

    //
    //  Set the starting directory to be the root directory.
    //

    CdfsStructureContext->DirSectorOffset = CdfsStructureContext->RootDirSectorOffset;
    CdfsStructureContext->DirDiskOffset = CdfsStructureContext->RootDirDiskOffset;
    CdfsStructureContext->DirSize = CdfsStructureContext->RootDirSize;

    //
    //  While the path name has some characters in it we'll go through our
    //  loop which extracts the first part of the path name and searches
    //  the current fnode (which must be a directory) for an the entry.
    //  If what we find is a directory then we have a new directory fnode
    //  and simply continue back to the top of the loop.
    //

    IsDirectory = TRUE;
    SearchSucceeded = TRUE;

    while (PathName.Length > 0
           && IsDirectory) {

        //
        //  Extract the first component.
        //

        CdfsFirstComponent( &PathName, &Name );

        //
        //  Copy the name into the filename buffer.
        //

        CdfsFileTableEntry->FileNameLength = (UCHAR) Name.Length;
        RtlMoveMemory( CdfsFileTableEntry->FileName,
                       Name.Buffer,
                       Name.Length );

        //
        //  Look to see if the file exists.
        //

        Status = CdfsSearchDirectory( &Name,
                                      &IsDirectory );

        if (Status == ENOENT) {

            SearchSucceeded = FALSE;
            break;
        }

        if (Status != ESUCCESS) {

            return Status;
        }

    }

    //
    //  If the path name length is not zero then we were trying to crack a path
    //  with an nonexistent (or non directory) name in it.  For example, we tried
    //  to crack a\b\c\d and b is not a directory or does not exist (then the path
    //  name will still contain c\d).
    //

    if (PathName.Length != 0) {

        return ENOTDIR;
    }

    //
    //  At this point we've cracked the name up to (an maybe including the last
    //  component).  We located the last component if the SearchSucceeded flag is
    //  true, otherwise the last component does not exist.  If we located the last
    //  component then this is like an open or a supersede, but not a create.
    //

    if (SearchSucceeded) {

        //
        //  Check if the last component is a directory
        //

        if (IsDirectory) {

            //
            //  For an existing directory the only valid open mode is OpenDirectory
            //  all other modes return an error
            //

            switch (OpenMode) {

            case ArcOpenReadOnly:
            case ArcOpenWriteOnly:
            case ArcOpenReadWrite:
            case ArcCreateWriteOnly:
            case ArcCreateReadWrite:
            case ArcSupersedeWriteOnly:
            case ArcSupersedeReadWrite:

                //
                //  If we reach here then the caller got a directory but didn't
                //  want to open a directory
                //

                return EISDIR;

            case ArcOpenDirectory:

                //
                //  If we reach here then the caller got a directory and wanted
                //  to open a directory.
                //

                CdfsFileTableEntry->u.CdfsFileContext.FileSize = CdfsStructureContext->DirSize;
                CdfsFileTableEntry->u.CdfsFileContext.DiskOffset = CdfsStructureContext->DirDiskOffset;
                CdfsFileTableEntry->u.CdfsFileContext.IsDirectory = TRUE;

                CdfsFileTableEntry->Flags.Open = 1;
                CdfsFileTableEntry->Flags.Read = 1;
                CdfsFileTableEntry->Position.LowPart = 0;
                CdfsFileTableEntry->Position.HighPart = 0;

                return ESUCCESS;

            case ArcCreateDirectory:

                //
                //  If we reach here then the caller got a directory and wanted
                //  to create a new directory
                //

                return EACCES;
            }
        }

        //
        //  If we get there then we have an existing file that is being opened.
        //  We can open existing files only read only.
        //

        switch (OpenMode) {

        case ArcOpenReadOnly:

            //
            //  If we reach here then the user got a file and wanted to open the
            //  file read only
            //

            CdfsFileTableEntry->u.CdfsFileContext.FileSize = CdfsStructureContext->DirSize;
            CdfsFileTableEntry->u.CdfsFileContext.DiskOffset = CdfsStructureContext->DirDiskOffset;
            CdfsFileTableEntry->u.CdfsFileContext.IsDirectory = FALSE;

            CdfsFileTableEntry->Flags.Open = 1;
            CdfsFileTableEntry->Flags.Read = 1;
            CdfsFileTableEntry->Position.LowPart = 0;
            CdfsFileTableEntry->Position.HighPart = 0;

            return ESUCCESS;

        case ArcOpenWriteOnly:
        case ArcOpenReadWrite:
        case ArcCreateWriteOnly:
        case ArcCreateReadWrite:
        case ArcSupersedeWriteOnly:
        case ArcSupersedeReadWrite:

            //
            //  If we reach here then we are trying to open a read only
            //  device for write.
            //

            return EROFS;

        case ArcOpenDirectory:
        case ArcCreateDirectory:

            //
            //  If we reach here then the user got a file and wanted a directory
            //

            return ENOTDIR;
        }
    }

    //
    //  If we get here the last component does not exist so we are trying to create
    //  either a new file or a directory.
    //

    switch (OpenMode) {

    case ArcOpenReadOnly:
    case ArcOpenWriteOnly:
    case ArcOpenReadWrite:
    case ArcOpenDirectory:

        //
        //  If we reach here then the user did not get a file but wanted a file
        //

        return ENOENT;

    case ArcCreateWriteOnly:
    case ArcSupersedeWriteOnly:
    case ArcCreateReadWrite:
    case ArcSupersedeReadWrite:
    case ArcCreateDirectory:

        //
        //  If we get hre the user wants to create something.
        //

        return EROFS;
    }

    //
    //  If we reach here then the path name is exhausted and we didn't
    //  reach a file so return an error to our caller
    //

    return ENOENT;
}
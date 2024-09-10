/* __CFWriteBytesToFileWithAtomicity is a "safe save" facility. Write the bytes using the specified mode on the file to the provided URL. If the atomic flag is true, try to do it in a fashion that will enable a safe save.
 */
static Boolean __CFWriteBytesToFileWithAtomicity(CFURLRef url, const void *bytes, int length, SInt32 mode, Boolean atomic) {
    int fd = -1;
    char auxPath[CFMaxPathSize + 16];
    char cpath[CFMaxPathSize];
    uid_t owner = getuid();
    gid_t group = getgid();
    Boolean writingFileAsRoot = ((getuid() != geteuid()) && (geteuid() == 0));
    
    if (!CFURLGetFileSystemRepresentation(url, true, (uint8_t *)cpath, CFMaxPathSize)) {
        return false;
    }
    
    if (-1 == mode || writingFileAsRoot) {
        struct stat statBuf;
        if (0 == stat(cpath, &statBuf)) {
            mode = statBuf.st_mode;
            owner = statBuf.st_uid;
            group = statBuf.st_gid;
        } else {
            mode = 0664;
            if (writingFileAsRoot && (0 == strncmp(cpath, "/Library/Preferences", 20))) {
                owner = geteuid();
                group = 80;
            }
        }
    }
    
    if (atomic) {
        CFURLRef dir = CFURLCreateCopyDeletingLastPathComponent(kCFAllocatorSystemDefault, url);
        CFURLRef tempFile = CFURLCreateCopyAppendingPathComponent(kCFAllocatorSystemDefault, dir, CFSTR("cf#XXXXX"), false);
        CFRelease(dir);
        if (!CFURLGetFileSystemRepresentation(tempFile, true, (uint8_t *)auxPath, CFMaxPathSize)) {
            CFRelease(tempFile);
            return false;
        }
        CFRelease(tempFile);
        fd = mkstemp(auxPath);
    } else {
        fd = open(cpath, O_WRONLY|O_CREAT|O_TRUNC, mode);
    }
    
    if (fd < 0) return false;
    
    if (length && (write(fd, bytes, length) != length || fsync(fd) < 0)) {
        int saveerr = thread_errno();
        close(fd);
        if (atomic)
            unlink(auxPath);
        thread_set_errno(saveerr);
        return false;
    }
    
    close(fd);
    
    if (atomic) {
        // preserve the mode as passed in originally
        chmod(auxPath, mode);
                
        if (0 != rename(auxPath, cpath)) {
            unlink(auxPath);
            return false;
        }
        
        // If the file was renamed successfully and we wrote it as root we need to reset the owner & group as they were.
        if (writingFileAsRoot) {
            chown(cpath, owner, group);
        }
    }
    return true;
}
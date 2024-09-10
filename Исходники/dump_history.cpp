// Given an offset count that points to a delimiter, this function returns the 
// previous delimiter offset position.
// If clusterId and procId is specified, it will not return the immediately
// previous delimiter, but the nearest previous delimiter that matches
static long findPrevDelimiter(FILE *fd, char* filename, long currOffset)
{
    MyString buf;
    char *owner;
    long prevOffset = -1, completionDate = -1;
    int clusterId = -1, procId = -1;
  
    fseek(fd, currOffset, SEEK_SET);
    buf.readLine(fd);
  
    owner = (char *) malloc(buf.Length() * sizeof(char)); 

    // Current format of the delimiter:
    // *** ProcId = a ClusterId = b Owner = "cde" CompletionDate = f
    // For the moment, owner and completionDate are just parsed in, reserved for future functionalities. 

    sscanf(buf.Value(), "%*s %*s %*s %ld %*s %*s %d %*s %*s %d %*s %*s %s %*s %*s %ld", 
           &prevOffset, &clusterId, &procId, owner, &completionDate);

    if (prevOffset == -1 && clusterId == -1 && procId == -1) {
        fprintf(stderr, 
                "Error: (%s) is an incompatible history file, please run condor_convert_history.\n",
                filename);
        free(owner);
        exit(1);
    }

    // If clusterId.procId is specified
    if (cluster != -1 || proc != -1) {

        // Ok if only clusterId specified
        while (clusterId != cluster || (proc != -1 && procId != proc)) {
	  
            if (prevOffset == 0) { // no match
                free(owner);
                return -1;
            }

            // Find previous delimiter + summary
            fseek(fd, prevOffset, SEEK_SET);
            buf.readLine(fd);
            
            owner = (char *) realloc (owner, buf.Length() * sizeof(char));
      
            sscanf(buf.Value(), "%*s %*s %*s %ld %*s %*s %d %*s %*s %d %*s %*s %s %*s %*s %ld", 
                   &prevOffset, &clusterId, &procId, owner, &completionDate);
        }
    }
 
    free(owner);
		 
    return prevOffset;
} 
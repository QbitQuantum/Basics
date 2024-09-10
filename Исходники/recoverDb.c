/* PrintDumpLabel
 *	print out the tape (dump) label.
 */
void
PrintDumpLabel(struct butm_tapeLabel *labelptr)
{
    char tapeName[BU_MAXTAPELEN + 32];
    time_t t;

    printf("Dump label\n");
    printf("----------\n");
    TAPENAME(tapeName, labelptr->pName, labelptr->dumpid);
    printf("permanent tape name = %s\n", tapeName);
    TAPENAME(tapeName, labelptr->AFSName, labelptr->dumpid);
    printf("AFS tape name = %s\n", tapeName);
    t = labelptr->creationTime;
    printf("creationTime = %s", ctime(&t));
    if (labelptr->expirationDate) {
        t = labelptr->expirationDate;
        printf("expirationDate = %s", cTIME(&t));
    }
    printf("cell = %s\n", labelptr->cell);
    printf("size = %u Kbytes\n", labelptr->size);
    printf("dump path = %s\n", labelptr->dumpPath);

    if (labelptr->structVersion >= TAPE_VERSION_3) {
        printf("dump id = %u\n", labelptr->dumpid);
        printf("useCount = %d\n", labelptr->useCount);
    }
    printf("-- End of dump label --\n\n");
}
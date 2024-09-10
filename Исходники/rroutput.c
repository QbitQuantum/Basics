/*
 * Destroy a Output at shutdown
 */
void
RROutputDestroy(RROutputPtr output)
{
    FreeResource(output->id, 0);
}
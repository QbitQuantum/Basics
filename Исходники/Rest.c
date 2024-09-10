static RIFFIOSuccess
cbRestEnd(NIFFIOChunkContext *pctxChunk, niffRest *p)
{
    VPRINTF(" (tuplet ID = %d|%d)",
            symbol_current->symbol.note.stem->tuplet,
            symbol_current->symbol.note.tuplet);

    return cbChunkEnd(pctxChunk);
}
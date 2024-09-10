static void		    
rewindLast	(pANTLR3_INT_STREAM is)
{
    is->rewind(is, is->lastMarker);
}
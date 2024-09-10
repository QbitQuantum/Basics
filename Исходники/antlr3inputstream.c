/** \brief Rewind the lexer input to the state specified by the last produced mark.
 * 
 * \param[in] input Input stream context pointer
 *
 * \remark
 * Assumes ASCII (or at least, 8 Bit) input stream.
 */
static void
antlr3AsciiRewindLast	(pANTLR3_INT_STREAM is)
{
    is->rewind(is, is->lastMarker);
}
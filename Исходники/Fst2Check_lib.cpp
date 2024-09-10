/**
 * Returns 1 if the given tag does not match anything in the text.
 *
 */
static int matches_E(Fst2* fst2,int tag_number) {
if (tag_number<0) {
	return 0;
}
if (tag_number==0) {
	return 1;
}
Fst2Tag tag=fst2->tags[tag_number];
switch (tag->type) {
/* WARNING: this is important not to use a default clause here!
 *          By enumerating all values instead, we make sure that there will
 *          be a compiler warning if one day a new value is added to the enum tag_type
 *          that is not taken into account here.
 */
case UNDEFINED_TAG: // used at initialization of a tag
case META_TAG:      // <MOT>, <MIN>, etc.
case PATTERN_TAG:   // <be.V>
case PATTERN_NUMBER_TAG: // used when patterns have been numbered
case TOKEN_LIST_TAG: break;  // used when the tag matches a list of tokens. This will
/* The following matches E */
case BEGIN_VAR_TAG: // $a(
case END_VAR_TAG:   // $a)
case BEGIN_OUTPUT_VAR_TAG: // $|a(
case END_OUTPUT_VAR_TAG:   // $|a)
case BEGIN_POSITIVE_CONTEXT_TAG: // $[
case BEGIN_NEGATIVE_CONTEXT_TAG: // $![
case END_CONTEXT_TAG:            // $]
case LEFT_CONTEXT_TAG:           // $*
case BEGIN_MORPHO_TAG: // $<
case END_MORPHO_TAG:    // $>
case TEXT_START_TAG: // {^}
case TEXT_END_TAG: return 1;   // {$}
}
/* Finally, we test if we have a <E> transition with an output */
if (!u_strcmp(tag->input,"<E>")) {
	return 1;
}
return 0;
}
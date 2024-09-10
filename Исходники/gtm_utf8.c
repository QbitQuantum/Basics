/* Returns the display column width of a character given its code point. This function
 * returns -1 for control characters and 0 for non-spacing (combining) characters.
 *
 * NOTEs:
 * We are not using libc's wcwidth() due to its inconsistent behavior across different
 * platforms and its incorrect behavior for several characters (even on Linux).
 *
 * ICU does not provide a direct API for display width, however, it does provide API
 * for the property "East Asian Width" specified in the "Unicode Standard Annex #11"
 * which provides guidelines to determine the width for the entire Unicode repertoire.
 *
 * Using "East Asian Width" and "General Category" properties. gtm_wcwidth() determines
 * the column width as below:
 * 	- SOFT-HYPHEN is a special format control character with a width of 1.
 *	- Non-spacing combining marks and Enclosing combining marks (Unicode general
 *	  category codes 'Mn' and 'Me') have a column width of 0. Note that Combing spacing
 *	  marks (General Category 'Mc') occupy a column width of 1.
 *	- Conjoining Hangul Jamos (i.e. vowels and trailing consonants between U+1160 -
 *	  U+11FF) have a column with of 0. They are like the combining marks in that they
 *	  attach to their previous characters (although they categorized as letters).
 *	- All wide characters (East Asian Width - Wide (W) and Full-Width (F)) have a
 *	  column width of 2 and all narrow characters (East Asian Width - Narrow (Na)
 *	  and Half-Width (H)) have a column width of 1.
 *	- All characters (with East Asian Width - Neutral (N) and Ambiguous (A)) have a
 *	  column width of 1.
 * 	- All other non-printable (control characters) and unassigned code points (empty blocks)
 * 	  have a width -1.
 */
int gtm_wcwidth(wint_t code)
{
	UCharCategory		gc;	/* General category as defined by the Unicode standard */
	UEastAsianWidth		ea;
	UHangulSyllableType	hst;

	assert(gtm_utf8_mode);
	if (0x00ad == code) /* SOFT-HYPHEN, a special format control character */
		return 1;
	gc = (UCharCategory)u_getIntPropertyValue((UChar32)code, UCHAR_GENERAL_CATEGORY);
	if (U_NON_SPACING_MARK == gc || U_ENCLOSING_MARK == gc || /* combining marks (Mn, Me) */
		U_FORMAT_CHAR == gc || /* all other format control (Cf) characters */
		U_HST_VOWEL_JAMO == (hst = (UHangulSyllableType)u_getIntPropertyValue((UChar32)code,
			UCHAR_HANGUL_SYLLABLE_TYPE)) ||
		U_HST_TRAILING_JAMO == hst) /* conjoining hangul jamos (in Korean) */
	{
		return 0;
	}
	if (U_ISPRINT((UChar32)code))
	{
		ea = (UEastAsianWidth)u_getIntPropertyValue((UChar32)code, UCHAR_EAST_ASIAN_WIDTH);
		return (U_EA_FULLWIDTH == ea || U_EA_WIDE == ea) ? 2 : 1;
	}
	return -1;
}
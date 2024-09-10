/**
 * Converts an RGB colour expressed in form 0x00rrggbb to a CSS/SVG representation of that colour.
 * The result is valid even in SVG Tiny or non-SVG CSS.
 */
static void rgb24_to_css(char *const buf, unsigned const rgb24)
{
    assert(rgb24 < (1u << 24));

    /* SVG 1.1 Full allows additional colour names not supported by SVG Tiny, but we don't bother
     * with them: it's good for these colours to be copyable to non-SVG CSS stylesheets and for
     * documents to be more viewable in SVG Tiny/Basic viewers; and some of the SVG Full names are
     * less meaningful than hex equivalents anyway.  And it's easier for a person to map from the
     * restricted set because the only component values are {00,80,ff}, other than silver 0xc0c0c0.
     */

    char const *src = NULL;
    switch (rgb24) {
        /* Extracted mechanically from the table at
         * http://www.w3.org/TR/REC-html40/types.html#h-6.5 .*/
        case 0x000000: src = "black"; break;
        case 0xc0c0c0: src = "silver"; break;
        case 0x808080: src = "gray"; break;
        case 0xffffff: src = "white"; break;
        case 0x800000: src = "maroon"; break;
        case 0xff0000: src = "red"; break;
        case 0x800080: src = "purple"; break;
        case 0xff00ff: src = "fuchsia"; break;
        case 0x008000: src = "green"; break;
        case 0x00ff00: src = "lime"; break;
        case 0x808000: src = "olive"; break;
        case 0xffff00: src = "yellow"; break;
        case 0x000080: src = "navy"; break;
        case 0x0000ff: src = "blue"; break;
        case 0x008080: src = "teal"; break;
        case 0x00ffff: src = "aqua"; break;

        default: {
            if ((rgb24 & 0xf0f0f) * 0x11 == rgb24) {
                /* Can use the shorter three-digit form #rgb instead of #rrggbb. */
                sprintf(buf, "#%x%x%x",
                        (rgb24 >> 16) & 0xf,
                        (rgb24 >> 8) & 0xf,
                        rgb24 & 0xf);
            } else {
                sprintf(buf, "#%06x", rgb24);
            }
            break;
        }
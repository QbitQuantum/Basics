static void shape_text(text_line & line,
                       text_itemizer & itemizer,
                       std::map<unsigned,double> & width_map,
                       face_manager_freetype & font_manager,
                       double scale_factor )
{
    unsigned start = line.first_char();
    unsigned end = line.last_char();
    mapnik::value_unicode_string const& text = itemizer.text();
    size_t length = end - start;
    if (!length) return;
    line.reserve(length);
    std::list<text_item> const& list = itemizer.itemize(start, end);

    UErrorCode err = U_ZERO_ERROR;
    mapnik::value_unicode_string shaped;
    mapnik::value_unicode_string reordered;

    for (auto const& text_item : list)
    {
        face_set_ptr face_set = font_manager.get_face_set(text_item.format->face_name, text_item.format->fontset);
        double size = text_item.format->text_size * scale_factor;
        face_set->set_unscaled_character_sizes();
        for (auto const& face : *face_set)
        {
            UBiDi *bidi = ubidi_openSized(length, 0, &err);
            ubidi_setPara(bidi, text.getBuffer(), length, UBIDI_DEFAULT_LTR, 0, &err);
            ubidi_writeReordered(bidi, reordered.getBuffer(length),
                                 length, UBIDI_DO_MIRRORING, &err);
            ubidi_close(bidi);
            reordered.releaseBuffer(length);

            int32_t num_char = u_shapeArabic(reordered.getBuffer(), length,
                                             shaped.getBuffer(length), length,
                                             U_SHAPE_LETTERS_SHAPE | U_SHAPE_LENGTH_FIXED_SPACES_NEAR |
                                             U_SHAPE_TEXT_DIRECTION_VISUAL_LTR, &err);
            if (num_char < 0)
            {
                MAPNIK_LOG_ERROR(icu_shaper) << " u_shapeArabic returned negative num_char " << num_char;
            }
            std::size_t num_chars = static_cast<std::size_t>(num_char);
            shaped.releaseBuffer(length);
            bool shaped_status = true;
            if (U_SUCCESS(err) && (num_chars == length))
            {
                U_NAMESPACE_QUALIFIER StringCharacterIterator iter(shaped);
                unsigned i = 0;
                for (iter.setToStart(); iter.hasNext();)
                {
                    UChar ch = iter.nextPostInc();
                    glyph_info tmp;
                    tmp.offset.clear();
                    tmp.char_index = i;
                    tmp.glyph_index = FT_Get_Char_Index(face->get_face(), ch);
                    if (tmp.glyph_index == 0)
                    {
                        shaped_status = false;
                        break;
                    }
                    tmp.face = face;
                    tmp.format = text_item.format;
                    face->glyph_dimensions(tmp);
                    tmp.scale_multiplier = size / face->get_face()->units_per_EM;
                    width_map[i] += tmp.advance();
                    line.add_glyph(std::move(tmp), scale_factor);
                    ++i;
                }
            }
            if (!shaped_status) continue;
            line.update_max_char_height(face->get_char_height(size));
            return;
        }
    }
}
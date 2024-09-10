void
write_cuesheet(std::string file_name,
               KaxChapters &chapters,
               KaxTags &tags,
               int64_t tuid,
               mm_io_c &out) {
  if (chapters.ListSize() == 0)
    return;

  if (g_no_variable_data)
    file_name = "no-variable-data";

  out.write_bom("UTF-8");

  print_if_global("CATALOG",        "CATALOG %1%\n"); // until 0.9.6
  print_if_global("CATALOG_NUMBER", "CATALOG %1%\n"); // 0.9.7 and newer
  print_if_global("ARTIST",         "PERFORMER \"%1%\"\n");
  print_if_global("TITLE",          "TITLE \"%1%\"\n");
  print_if_global("DATE",           "REM DATE \"%1%\"\n"); // until 0.9.6
  print_if_global("DATE_RELEASED",  "REM DATE \"%1%\"\n"); // 0.9.7 and newer
  print_if_global("DISCID",         "REM DISCID %1%\n");

  KaxTag *tag = find_tag_for_track(-1, tuid, 0, tags);
  if (NULL != tag)
    print_comments("", *tag, out);

  out.puts(boost::format("FILE \"%1%\" WAVE\n") % file_name);

  size_t i;
  for (i = 0; i < chapters.ListSize(); i++) {
    KaxChapterAtom &atom =  *static_cast<KaxChapterAtom *>(chapters[i]);

    out.puts(boost::format("  TRACK %|1$02d| AUDIO\n") % (i + 1));
    tag = find_tag_for_track(i + 1, tuid, get_chapter_uid(atom), tags);
    if (NULL == tag)
      continue;

    print_if_available("TITLE",               "    TITLE \"%1%\"\n");
    print_if_available("ARTIST",              "    PERFORMER \"%1%\"\n");
    print_if_available("ISRC",                "    ISRC %1%\n");
    print_if_available("CDAUDIO_TRACK_FLAGS", "    FLAGS %1%\n");

    int k;
    for (k = 0; 100 > k; ++k) {
      int64_t temp_index = get_chapter_index(k, atom);
      if (-1 == temp_index)
        continue;

      out.puts(boost::format("    INDEX %|1$02d| %|2$02d|:%|3$02d|:%|4$02d|\n")
               % k
               % (temp_index / 1000000 / 1000 / 60)
               % ((temp_index / 1000000 / 1000) % 60)
               % irnd((double)(temp_index % 1000000000ll) * 75.0 / 1000000000.0));
    }

    print_if_available("DATE",          "    REM DATE \"%1%\"\n"); // until 0.9.6
    // 0.9.7 and newer:
    print_if_available("DATE_RELEASED", "    REM DATE \"%1%\"\n");
    print_if_available("GENRE",         "    REM GENRE \"%1%\"\n");
    print_comments("    ", *tag, out);
  }
}
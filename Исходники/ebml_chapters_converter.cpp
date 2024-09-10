void
ebml_chapters_converter_c::write_xml(KaxChapters &chapters,
                                     mm_io_c &out) {
  document_cptr doc(new pugi::xml_document);

  doc->append_child(pugi::node_comment).set_value(" <!DOCTYPE Chapters SYSTEM \"matroskachapters.dtd\"> ");

  ebml_chapters_converter_c converter;
  converter.to_xml(chapters, doc);

  std::stringstream out_stream;
  doc->save(out_stream, "  ", pugi::format_default | pugi::format_write_bom);
  out.puts(out_stream.str());
}
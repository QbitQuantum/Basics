void rdi2html::transform()
{
  XalanTransformer transformer;

  istringstream xsl_stream(STYLESHEET);
  const XSLTInputSource stylesheet_input_source(xsl_stream);
  const XalanCompiledStylesheet* stylesheet = 0;
  if(transformer.compileStylesheet(stylesheet_input_source, stylesheet) != 0)
    {
    throw logic_error(
      string("An error occurred compiling the stylesheet: ") +
      string(transformer.getLastError())
      );
    }

  xml_schema::dom::auto_ptr< xercesc::DOMDocument> domdoc = m_rdiReader->parse_to_DOMDocument();
  domdoc->normalize();

  XercesParserLiaison parser_liaison;
  XercesDOMSupport DOM_support(parser_liaison);

  const XercesDOMWrapperParsedSource parsed_source(
    domdoc.get(),
    parser_liaison,
    DOM_support
  );

  if(transformer.transform(parsed_source, stylesheet, m_out_filepath.c_str()) != 0)
    {
    throw logic_error(
      string("An error occurred compiling the stylesheet: ") +
      string(transformer.getLastError())
      );
    }
}
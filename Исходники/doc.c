Lisp_Object
read_doc_string (Lisp_Object filepos)
{
  Lisp_Object string = get_doc_string (filepos);

  if (!STRINGP (string))
    invalid_state ("loading bytecode failed to return string", string);
  return Fread (string);
}
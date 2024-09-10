//
// invoke_ex
//
int IDLTextEditor_Impl::
invoke_ex (GAME::Mga::Project project,
           GAME::Mga::FCO_in focus,
           std::vector <GAME::Mga::FCO> & selected,
           long flags)
{
  if (selected.empty ())
  {
    // Make sure there is at least one object is selected.
    ::AfxMessageBox ("Please select a File element first.", MB_OK | MB_ICONWARNING);
  }
  else if (selected.size () > 1)
  {
    // Make sure only one object is selected.
    ::AfxMessageBox ("Please select only one File element.", MB_OK | MB_ICONWARNING);
  }
  else
  {
    try
    {
      // Create a new document for the model element.
      DSL_DocTemplate doc_template;
      DSL_Document * dsl_doc = new DSL_Document (selected.front ());

      // Configure the document serializer and deserializer.
      IDL_File_Serializer idl_file_serializer;
      IDL_File_Deserializer idl_file_deserializer;
      dsl_doc->configure (&idl_file_serializer, &idl_file_deserializer);

      // Create a new frame for the document. We are going to use
      // the new document for the initial view.
      CWnd * mainwnd = ::AfxGetMainWnd ();
      CFrameWnd * frame = doc_template.CreateNewFrame (mainwnd, dsl_doc, 0);

      if (0 != frame)
      {
        do
        {
          // Perform the initial update to the frame.
          GAME::Mga::Transaction t (project, TRANSACTION_READ_ONLY);
          frame->InitialUpdateFrame (dsl_doc, true);
        } while (0);

        // Extract the editor and run the modal loop.
        DSL_TextEditor * editor = dynamic_cast <DSL_TextEditor *> (frame);

        if (0 != editor->DoModal ())
          ::AfxMessageBox ("Failed to create TextEditor", MB_OK | MB_ICONERROR);

        // Destroy the frame before continuing.
        frame->DestroyWindow ();
      }
      else
        ::AfxMessageBox ("Failed to create window", MB_OK | MB_ICONERROR);
    }
    catch (const GAME::Mga::Failed_Result & ex)
    {
      long v = ex.value ();
    }
    catch (const GAME::Mga::Exception &)
    {

    }
  }


  return 0;
}
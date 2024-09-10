bool szHelpController::AddBook(const wxString& book)
{
    bool retval = wxHtmlHelpControllerEx::AddBook(book); 

    if (retval) 
	return InitializeContext(book.BeforeLast('.') + _T(".map"));
    return FALSE;
}
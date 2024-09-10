void Report::AddProportionalColumn (int widthPercentage, std::string const & title, ColAlignment align, bool hasImage)
{
    ClientRect rect (H ());
    // Revisit: check if total number of items is less then items/per page
    // and if this is not the case substract from list view client rectangle
    // width the system width of vertical scroll bar
	Report::Column column;
	column.Width ((widthPercentage * rect.Width ()) / 100);
	column.Align (align);
	if (!title.empty ())
		column.Title (title);
	column.SubItem (_cColumn);
	if (hasImage)
		column.HasImages ();
    if (ListView_InsertColumn (H (), _cColumn, &column) == -1)
        throw Win::Exception ("Internal error: Cannot insert column.");
    _cColumn++;
}
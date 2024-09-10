void FiltersDialog::SetStaticData()
{
	UpdateData();
	wchar_t str[255] = {0};
	CountFriquencyValues();
	_high_bound_static.SetWindowText( _itow(_high_bound_value, str, 10) ) ;
	_low_bound_static.SetWindowText( _itow(_low_bound_value, str, 10) ) ;
	_weight_static.SetWindowText( _itow(_weight_value, str, 10) ) ;
}
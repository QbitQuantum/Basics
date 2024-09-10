void
MSCalibrationForm::handle_value_changed( const QModelIndex& index )
{
    QStandardItemModel& model = *pModel_;
	int row = index.row();
    if ( index.column() == c_formula ) {
        adcontrols::MSReference ref;
        std::wstring text = model.index( row, c_formula ).data( Qt::EditRole ).toString().toStdWString();
        if ( parse_formula( text, ref ) ) {
            model.setData( model.index( row, c_formula ),     qtwrapper::qstring::copy( ref.formula() ) );
            model.setData( model.index( row, c_exact_mass ),  ref.exact_mass() );
            model.setData( model.index( row, c_enable ),      ref.enable() );
            QStandardItem * chk = model.itemFromIndex( model.index( row, c_enable ) );
            if ( chk ) {
                chk->setFlags( Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
                chk->setEditable( true );
                model.setData( model.index( row, c_enable ),  ref.enable() ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole );
            }
            model.setData( model.index( row, c_charge ),      ref.charge_count() );
        }
    }
	if ( row == model.rowCount() - 1 )
		model.insertRow( row + 1);
}
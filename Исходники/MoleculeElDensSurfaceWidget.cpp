//------------------------------------------------------------------------------
void MoleculeElDensSurfaceWidget::UpdateGUI( bool updateTable, bool updateBBox )
{
    table_->setEnabled( false );
    if( mol_ == 0 ) return;
    densityMatrixCheckBox_->setEnabled( mol_->CanComputeElectronDensity() );
    ResourceHandler< bool > rh( updatingGUI_, true, false );
    if( updateTable && mol_->GetNumberOfOrbitals() )
    {
        // update orbitals
        const int orbitals = mol_->GetNumberOfOrbitals();
        table_->setRowCount( orbitals );
        QStringList verticalHeaders;
        for( int i = 0;	 i != orbitals; ++i )
        {
            QTableWidgetItem *eigenValueItem = new QTableWidgetItem;
            eigenValueItem->setFlags(  Qt::ItemIsSelectable | Qt::ItemIsEnabled );
            eigenValueItem->setText( QString( "%1" ).arg( mol_->GetOrbitalEigenValue( i  ) ) );
            QTableWidgetItem *occupationItem = new QTableWidgetItem;
            occupationItem->setFlags(  Qt::ItemIsSelectable | Qt::ItemIsEnabled );
            occupationItem->setText( QString( "%1" ).arg( mol_->GetOrbitalOccupation( i ) ) );
            QTableWidgetItem *typeItem = new QTableWidgetItem;
            typeItem->setText( QString( "%1" ).arg( mol_->GetOrbitalType( i ) ) );
            QTableWidgetItem *generatedItem = new QTableWidgetItem;
            generatedItem->setFlags(  Qt::ItemIsSelectable | Qt::ItemIsEnabled );
            // Removed check box, not sure it's a good idea, user
            // will want to check the checkbox and then click on generate
            // to have multiple orbital surfaces generated at once.
            if( mol_->HasOrbitalSurface( i ) )
            {

                //generatedItem->setCheckState( Qt::Checked );
                generatedItem->setText( tr( "Yes" ) );
            }
            else
            {
                //generatedItem->setCheckState( Qt::Unchecked );
                generatedItem->setText( tr( "No" ) );
            }
            table_->setItem( i, 0, generatedItem );
            table_->setItem( i, 1, eigenValueItem );
            table_->setItem( i, 2, occupationItem );
            table_->setItem( i, 3, typeItem );

            //TEMPORARY DISABLED
            //if( mol_->IsAlphaOrbital( i ) )
            //{
            //    verticalHeaders << QString( "%1 (%2)" ).arg( i + 1 ).arg( tr( "alpha" ) );
            //}
            //else if( mol_->IsBetaOrbital( i ) )
            //{
            //    verticalHeaders << QString( "%1 (%2)" ).arg( i + 1 ).arg( tr( "beta" ) );
            //}
        }
        table_->setVerticalHeaderLabels( verticalHeaders );
        table_->resizeColumnsToContents();
        /// @todo do we need the following to make sure everything is unselected ?
        /// table_->setRangeSelected( QTableWidgetSelectionRange( 0, 0, table_->rowCount() - 1, 3 ), false );
    }
    if( updateBBox )
    {
        double dx = 0.;
        double dy = 0.;
        double dz = 0.;
        mol_->GetIsoBoundingBoxSize( dx, dy, dz );
#ifdef PERSISTENT_ISOBBOX
        QSettings s;
        if( s.contains( BBOX_DX_KEY ) ) dx = s.value( BBOX_DX_KEY ).toDouble();
        if( s.contains( BBOX_DY_KEY ) ) dy = s.value( BBOX_DY_KEY ).toDouble(); 
        if( s.contains( BBOX_DZ_KEY ) ) dz = s.value( BBOX_DZ_KEY ).toDouble();
#endif 
        dxSpinBox_->setValue( dx );
        dySpinBox_->setValue( dy );
        dzSpinBox_->setValue( dz );
        ComputeSteps();
    }
    
    double cx = 0.;
    double cy = 0.;
    double cz = 0.;
    double dx = 0.;
    double dy = 0.;
    double dz = 0.;
    mol_->GetIsoBoundingBoxSize( dx, dy, dz );
    mol_->GetIsoBoundingBoxCenter( cx, cy, cz );
    xSpinBox_->setValue( cx );
    ySpinBox_->setValue( cy );
    zSpinBox_->setValue( cz );
    xSpinBox_->setSingleStep( 0.05 * dx );
    ySpinBox_->setSingleStep( 0.05 * dy );
    zSpinBox_->setSingleStep( 0.05 * dz );
    xSpinBox_->setMinimum( cx - dx );
    xSpinBox_->setMaximum( cx + dx );
    ySpinBox_->setMinimum( cy - dy );
    ySpinBox_->setMaximum( cy + dy );
    zSpinBox_->setMinimum( cz - dz );
    zSpinBox_->setMaximum( cz + dz );
    dxSpinBox_->setSingleStep( 0.05 * dx );
    dySpinBox_->setSingleStep( 0.05 * dy );
    dzSpinBox_->setSingleStep( 0.05 * dz );
    table_->setEnabled( true );

}
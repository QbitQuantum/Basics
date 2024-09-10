void FmFileDialogPrivate::createBottomWidget()
{
    if( mArgs.mDialogMode == GetDirMode ) {
        return;
    }
    HbWidget *bottomWidget = new HbWidget( mContentWidget );
    bottomWidget->setObjectName( "bottomWidget" );
    mContentLayout->addItem( bottomWidget );

    QGraphicsLinearLayout *bottomLayout = new QGraphicsLinearLayout;
    bottomLayout->setOrientation( Qt::Horizontal );

    mFileNameTitleLabel = new HbLabel( mFileDialog->tr( "file name:" ), bottomWidget );
    mFileNameTitleLabel->setObjectName( "fileNameTitleLabel" );
    bottomLayout->addItem( mFileNameTitleLabel );

    mFileNameLineEdit = new HbLineEdit( bottomWidget );
    mFileNameLineEdit->setObjectName( "fileNameLineEdit" );
    bottomLayout->addItem( mFileNameLineEdit );    

    bottomWidget->setLayout( bottomLayout );

}
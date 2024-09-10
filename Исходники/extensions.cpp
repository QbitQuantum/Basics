QWidget* ExtensionDialog::CreateWidget( extension_widget_t *p_widget )
{
    QLabel *label = NULL;
    QPushButton *button = NULL;
    QTextBrowser *textArea = NULL;
    QLineEdit *textInput = NULL;
    QCheckBox *checkBox = NULL;
    QComboBox *comboBox = NULL;
    QListWidget *list = NULL;
    struct extension_widget_t::extension_widget_value_t *p_value = NULL;

    assert( p_widget->p_sys_intf == NULL );

    switch( p_widget->type )
    {
        case EXTENSION_WIDGET_LABEL:
            label = new QLabel( qfu( p_widget->psz_text ), this );
            p_widget->p_sys_intf = label;
            label->setTextFormat( Qt::RichText );
            label->setOpenExternalLinks( true );
            return label;

        case EXTENSION_WIDGET_BUTTON:
            button = new QPushButton( qfu( p_widget->psz_text ), this );
            clickMapper->setMapping( button, new WidgetMapper( p_widget ) );
            CONNECT( button, clicked(), clickMapper, map() );
            p_widget->p_sys_intf = button;
            return button;

        case EXTENSION_WIDGET_IMAGE:
            label = new QLabel( this );
            label->setPixmap( QPixmap( qfu( p_widget->psz_text ) ) );
            if( p_widget->i_width > 0 )
                label->setMaximumWidth( p_widget->i_width );
            if( p_widget->i_height > 0 )
                label->setMaximumHeight( p_widget->i_height );
            label->setScaledContents( true );
            p_widget->p_sys_intf = label;
            return label;

        case EXTENSION_WIDGET_HTML:
            textArea = new QTextBrowser( this );
            textArea->setOpenExternalLinks( true );
            textArea->setHtml( qfu( p_widget->psz_text ) );
            p_widget->p_sys_intf = textArea;
            return textArea;

        case EXTENSION_WIDGET_TEXT_FIELD:
            textInput = new QLineEdit( this );
            textInput->setText( qfu( p_widget->psz_text ) );
            textInput->setReadOnly( false );
            textInput->setEchoMode( QLineEdit::Normal );
            inputMapper->setMapping( textInput, new WidgetMapper( p_widget ) );
            /// @note: maybe it would be wiser to use textEdited here?
            CONNECT( textInput, textChanged(const QString &),
                     inputMapper, map() );
            p_widget->p_sys_intf = textInput;
            return textInput;

        case EXTENSION_WIDGET_PASSWORD:
            textInput = new QLineEdit( this );
            textInput->setText( qfu( p_widget->psz_text ) );
            textInput->setReadOnly( false );
            textInput->setEchoMode( QLineEdit::Password );
            inputMapper->setMapping( textInput, new WidgetMapper( p_widget ) );
            /// @note: maybe it would be wiser to use textEdited here?
            CONNECT( textInput, textChanged(const QString &),
                     inputMapper, map() );
            p_widget->p_sys_intf = textInput;
            return textInput;

        case EXTENSION_WIDGET_CHECK_BOX:
            checkBox = new QCheckBox( this );
            checkBox->setText( qfu( p_widget->psz_text ) );
            checkBox->setChecked( p_widget->b_checked );
            clickMapper->setMapping( checkBox, new WidgetMapper( p_widget ) );
            CONNECT( checkBox, stateChanged( int ), clickMapper, map() );
            p_widget->p_sys_intf = checkBox;
            return checkBox;

        case EXTENSION_WIDGET_DROPDOWN:
            comboBox = new QComboBox( this );
            comboBox->setEditable( false );
            for( p_value = p_widget->p_values;
                 p_value != NULL;
                 p_value = p_value->p_next )
            {
                comboBox->addItem( qfu( p_value->psz_text ), p_value->i_id );
            }
            /* Set current item */
            if( p_widget->psz_text )
            {
                int idx = comboBox->findText( qfu( p_widget->psz_text ) );
                if( idx >= 0 )
                    comboBox->setCurrentIndex( idx );
            }
            selectMapper->setMapping( comboBox, new WidgetMapper( p_widget ) );
            CONNECT( comboBox, currentIndexChanged( const QString& ),
                     selectMapper, map() );
            return comboBox;

        case EXTENSION_WIDGET_LIST:
            list = new QListWidget( this );
            list->setSelectionMode( QAbstractItemView::ExtendedSelection );
            for( p_value = p_widget->p_values;
                 p_value != NULL;
                 p_value = p_value->p_next )
            {
                QListWidgetItem *item =
                    new QListWidgetItem( qfu( p_value->psz_text ) );
                item->setData( Qt::UserRole, p_value->i_id );
                list->addItem( item );
            }
            selectMapper->setMapping( list, new WidgetMapper( p_widget ) );
            CONNECT( list, itemSelectionChanged(),
                     selectMapper, map() );
            return list;

        default:
            msg_Err( p_intf, "Widget type %d unknown", p_widget->type );
            return NULL;
    }
}
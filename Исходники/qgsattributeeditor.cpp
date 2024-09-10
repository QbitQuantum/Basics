QWidget *QgsAttributeEditor::createAttributeEditor( QWidget *parent, QWidget *editor, QgsVectorLayer *vl, int idx, const QVariant &value, QMap<int, QWidget*> &proxyWidgets )
{
  if ( !vl )
    return 0;

  QWidget *myWidget = 0;
  QgsVectorLayer::EditType editType = vl->editType( idx );
  const QgsField &field = vl->pendingFields()[idx];
  QVariant::Type myFieldType = field.type();

  bool synchronized = false;

  switch ( editType )
  {
    case QgsVectorLayer::UniqueValues:
    {
      QList<QVariant> values;
      vl->dataProvider()->uniqueValues( idx, values );

      QComboBox *cb = comboBox( editor, parent );
      if ( cb )
      {
        cb->setEditable( false );

        for ( QList<QVariant>::iterator it = values.begin(); it != values.end(); it++ )
          cb->addItem( it->toString(), it->toString() );

        myWidget = cb;
      }

    }
    break;

    case QgsVectorLayer::Enumeration:
    {
      QStringList enumValues;
      vl->dataProvider()->enumValues( idx, enumValues );

      QComboBox *cb = comboBox( editor, parent );
      if ( cb )
      {
        QStringList::const_iterator s_it = enumValues.constBegin();
        for ( ; s_it != enumValues.constEnd(); ++s_it )
        {
          cb->addItem( *s_it, *s_it );
        }

        myWidget = cb;
      }
    }
    break;

    case QgsVectorLayer::ValueMap:
    {
      const QMap<QString, QVariant> &map = vl->valueMap( idx );

      QComboBox *cb = comboBox( editor, parent );
      if ( cb )
      {
        for ( QMap<QString, QVariant>::const_iterator it = map.begin(); it != map.end(); it++ )
        {
          cb->addItem( it.key(), it.value() );
        }

        myWidget = cb;
      }
    }
    break;

    case QgsVectorLayer::ValueRelation:
    {
      const QgsVectorLayer::ValueRelationData &data = vl->valueRelation( idx );

      QgsVectorLayer *layer = qobject_cast<QgsVectorLayer*>( QgsMapLayerRegistry::instance()->mapLayer( data.mLayer ) );
      QMap< QString, QString > map;

      int fi = -1;
      if ( layer )
      {
        int ki = layer->fieldNameIndex( data.mOrderByValue ? data.mValue : data.mKey );
        int vi = layer->fieldNameIndex( data.mOrderByValue ? data.mKey : data.mValue );

        if ( !data.mFilterAttributeColumn.isNull() )
          fi = layer->fieldNameIndex( data.mFilterAttributeColumn );

        if ( ki >= 0 && vi >= 0 )
        {
          QgsAttributeList attributes;
          attributes << ki;
          attributes << vi;
          if ( fi >= 0 )
            attributes << fi;
          layer->select( attributes, QgsRectangle(), false );
          QgsFeature f;
          while ( layer->nextFeature( f ) )
          {
            if ( fi >= 0 && f.attributeMap()[ fi ].toString() != data.mFilterAttributeValue )
              continue;

            map.insert( f.attributeMap()[ ki ].toString(), f.attributeMap()[ vi ].toString() );
          }
        }
      }

      if ( !data.mAllowMulti )
      {
        QComboBox *cb = comboBox( editor, parent );
        if ( cb )
        {
          if ( data.mAllowNull )
          {
            QSettings settings;
            cb->addItem( tr( "(no selection)" ), settings.value( "qgis/nullValue", "NULL" ).toString() );
          }

          for ( QMap< QString, QString >::const_iterator it = map.begin(); it != map.end(); it++ )
          {
            if ( data.mOrderByValue )
              cb->addItem( it.key(), it.value() );
            else
              cb->addItem( it.value(), it.key() );
          }

          myWidget = cb;
        }
      }
      else
      {
        QListWidget *lw = listWidget( editor, parent );
        if ( lw )
        {
          QStringList checkList = value.toString().remove( QChar( '{' ) ).remove( QChar( '}' ) ).split( "," );

          for ( QMap< QString, QString >::const_iterator it = map.begin(); it != map.end(); it++ )
          {
            QListWidgetItem *item;
            if ( data.mOrderByValue )
            {
              item = new QListWidgetItem( it.key() );
              item->setData( Qt::UserRole, it.value() );
              item->setCheckState( checkList.contains( it.value() ) ? Qt::Checked : Qt::Unchecked );
            }
            else
            {
              item = new QListWidgetItem( it.value() );
              item->setData( Qt::UserRole, it.key() );
              item->setCheckState( checkList.contains( it.key() ) ? Qt::Checked : Qt::Unchecked );
            }
            lw->addItem( item );
          }

          myWidget = lw;
        }
      }
    }
    break;

    case QgsVectorLayer::Classification:
    {
      QMap<QString, QString> classes;

      const QgsUniqueValueRenderer *uvr = dynamic_cast<const QgsUniqueValueRenderer *>( vl->renderer() );
      if ( uvr )
      {
        const QList<QgsSymbol *> symbols = uvr->symbols();

        for ( int i = 0; i < symbols.size(); i++ )
        {
          QString label = symbols[i]->label();
          QString name = symbols[i]->lowerValue();

          if ( label == "" )
            label = name;

          classes.insert( name, label );
        }
      }

      const QgsCategorizedSymbolRendererV2 *csr = dynamic_cast<const QgsCategorizedSymbolRendererV2 *>( vl->rendererV2() );
      if ( csr )
      {
        const QgsCategoryList &categories = (( QgsCategorizedSymbolRendererV2 * )csr )->categories(); // FIXME: QgsCategorizedSymbolRendererV2::categories() should be const
        for ( int i = 0; i < categories.size(); i++ )
        {
          QString label = categories[i].label();
          QString value = categories[i].value().toString();
          if ( label.isEmpty() )
            label = value;
          classes.insert( value, label );
        }
      }

      QComboBox *cb = comboBox( editor, parent );
      if ( cb )
      {
        for ( QMap<QString, QString>::const_iterator it = classes.begin(); it != classes.end(); it++ )
        {
          cb->addItem( it.value(), it.key() );
        }

        myWidget = cb;
      }
    }
    break;

    case QgsVectorLayer::DialRange:
    case QgsVectorLayer::SliderRange:
    case QgsVectorLayer::EditRange:
    {
      if ( myFieldType == QVariant::Int )
      {
        int min = vl->range( idx ).mMin.toInt();
        int max = vl->range( idx ).mMax.toInt();
        int step = vl->range( idx ).mStep.toInt();

        if ( editType == QgsVectorLayer::EditRange )
        {
          QSpinBox *sb = 0;

          if ( editor )
            sb = qobject_cast<QSpinBox *>( editor );
          else
            sb = new QSpinBox( parent );

          if ( sb )
          {
            sb->setRange( min, max );
            sb->setSingleStep( step );

            myWidget = sb;
          }
        }
        else
        {
          QAbstractSlider *sl = 0;

          if ( editor )
          {
            sl = qobject_cast<QAbstractSlider*>( editor );
          }
          else if ( editType == QgsVectorLayer::DialRange )
          {
            sl = new QDial( parent );
          }
          else
          {
            sl = new QSlider( Qt::Horizontal, parent );
          }

          if ( sl )
          {
            sl->setRange( min, max );
            sl->setSingleStep( step );

            myWidget = sl;
          }
        }
        break;
      }
      else if ( myFieldType == QVariant::Double )
      {
        QDoubleSpinBox *dsb = 0;
        if ( editor )
          dsb = qobject_cast<QDoubleSpinBox*>( editor );
        else
          dsb = new QDoubleSpinBox( parent );

        if ( dsb )
        {
          double min = vl->range( idx ).mMin.toDouble();
          double max = vl->range( idx ).mMax.toDouble();
          double step = vl->range( idx ).mStep.toDouble();

          dsb->setRange( min, max );
          dsb->setSingleStep( step );

          myWidget = dsb;
        }
        break;
      }
    }

    case QgsVectorLayer::CheckBox:
    {
      QCheckBox *cb = 0;
      if ( editor )
        cb = qobject_cast<QCheckBox*>( editor );
      else
        cb = new QCheckBox( parent );

      if ( cb )
      {
        myWidget = cb;
        break;
      }
    }

    // fall-through

    case QgsVectorLayer::LineEdit:
    case QgsVectorLayer::TextEdit:
    case QgsVectorLayer::UuidGenerator:
    case QgsVectorLayer::UniqueValuesEditable:
    case QgsVectorLayer::Immutable:
    {
      QLineEdit *le = 0;
      QTextEdit *te = 0;
      QPlainTextEdit *pte = 0;
      QComboBox * cb = 0;

      if ( editor )
      {
        le = qobject_cast<QLineEdit *>( editor );
        te = qobject_cast<QTextEdit *>( editor );
        pte = qobject_cast<QPlainTextEdit *>( editor );
        cb = qobject_cast<QComboBox *>( editor );
      }
      else if ( editType == QgsVectorLayer::TextEdit )
      {
        pte = new QPlainTextEdit( parent );
      }
      else
      {
        le = new QLineEdit( parent );
      }

      if ( le )
      {
        if ( editType == QgsVectorLayer::UniqueValuesEditable )
        {
          QList<QVariant> values;
          vl->dataProvider()->uniqueValues( idx, values );

          QStringList svalues;
          for ( QList<QVariant>::const_iterator it = values.begin(); it != values.end(); it++ )
            svalues << it->toString();

          QCompleter *c = new QCompleter( svalues );
          c->setCompletionMode( QCompleter::PopupCompletion );
          le->setCompleter( c );
        }

        if ( editType == QgsVectorLayer::UuidGenerator )
        {
          le->setReadOnly( true );
        }

        le->setValidator( new QgsFieldValidator( le, field ) );

        myWidget = le;
      }

      if ( te )
      {
        te->setAcceptRichText( true );
        myWidget = te;
      }

      if ( pte )
      {
        myWidget = pte;
      }

      if ( cb )
      {
        myWidget = cb;
      }

      if ( myWidget )
      {
        myWidget->setDisabled( editType == QgsVectorLayer::Immutable );

        QgsStringRelay* relay = NULL;

        QMap<int, QWidget*>::const_iterator it = proxyWidgets.find( idx );
        if ( it != proxyWidgets.end() )
        {
          QObject* obj = qvariant_cast<QObject*>( (*it)->property( "QgisAttrEditProxy" ) );
          relay = qobject_cast<QgsStringRelay*>( obj );
        }
        else
        {
          relay = new QgsStringRelay( myWidget );
        }

        if ( cb && cb->isEditable() )
        {
          synchronized =  connect( relay, SIGNAL( textChanged( QString ) ), myWidget, SLOT( setEditText( QString ) ) );
          synchronized &= connect( myWidget, SIGNAL( editTextChanged( QString ) ), relay, SLOT( changeText( QString ) ) );
        }
        else
        {
          synchronized =  connect( relay, SIGNAL( textChanged( QString ) ), myWidget, SLOT( setText( QString ) ) );
          synchronized &= connect( myWidget, SIGNAL( textChanged( QString ) ), relay, SLOT( changeText( QString ) ) );
        }

        if ( !cb || cb->isEditable() )
        {
          myWidget->setProperty( "QgisAttrEditProxy", QVariant( QMetaType::QObjectStar, &relay ) );
        }
      }
    }
    break;

    case QgsVectorLayer::Hidden:
      myWidget = 0;
      break;

    case QgsVectorLayer::FileName:
    case QgsVectorLayer::Calendar:
    {
      QPushButton *pb = 0;
      QLineEdit *le = qobject_cast<QLineEdit *>( editor );
      if ( le )
      {
        if ( le )
          myWidget = le;

        if ( editor->parent() )
        {
          pb = editor->parent()->findChild<QPushButton *>();
        }
      }
      else
      {
        le = new QLineEdit();

        pb = new QPushButton( tr( "..." ) );

        QHBoxLayout *hbl = new QHBoxLayout();
        hbl->addWidget( le );
        hbl->addWidget( pb );

        myWidget = new QWidget( parent );
        myWidget->setBackgroundRole( QPalette::Window );
        myWidget->setAutoFillBackground( true );
        myWidget->setLayout( hbl );
      }

      if ( pb )
      {
        if ( editType == QgsVectorLayer::FileName )
          connect( pb, SIGNAL( clicked() ), new QgsAttributeEditor( pb ), SLOT( selectFileName() ) );
        if ( editType == QgsVectorLayer::Calendar )
          connect( pb, SIGNAL( clicked() ), new QgsAttributeEditor( pb ), SLOT( selectDate() ) );
      }
    }
    break;
  }

  QMap<int, QWidget*>::const_iterator it = proxyWidgets.find( idx );
  if ( it != proxyWidgets.end() )
  {
    if ( !synchronized )
    {
      myWidget->setEnabled( false );
    }
  }
  else
  {
    proxyWidgets.insert( idx, myWidget );
  }

  setValue( myWidget, vl, idx, value );

  return myWidget;
}
   ConvolutionFilterCodeDialog::ConvolutionFilterCodeDialog( String mode, const Filter& _filter ) : Dialog(), filter( _filter )
   {
      // ### TextBox
      FilterCode_TextBox.SetScaledMinSize( 700, 300 );
      FilterCode_TextBox.OnCaretPositionUpdated( (TextBox::caret_event_handler)&ConvolutionFilterCodeDialog::__TextBox_CaretPosition, *this );

      if ( mode == "Edit" )
      {
         FilterCode_TextBox.SetReadWrite();
         FilterCode_TextBox.SetText( filter.ToSource() );
      }

      tableRow = 0;
      String s;
      String html( "<html style=\"white-space:pre;text-align:right;\">"
                     "<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\">" );

      StringList cols;
      UpdateTableColors();

      if ( mode == "View" )
      {
         FilterCode_TextBox.SetReadOnly();
         if ( filter.IsSeparable() )
         {
            SeparableFilter fs( filter.Separable() );
            float element;

            // Rows
            for ( int i = 0; i < fs.Size(); ++i )
            {
               // Cols
               for ( int j = 0; j < fs.Size(); ++j )
               {
                  // Calculus of each coefficient of the separable filter
                  element = Round( fs.ColFilter()[i] * fs.RowFilter()[j], 6 );
                  cols.Add( String().Format( "%10.6f", element ) );


               }
               html += TR( cols );
               cols.Clear();
            }
         }
         else
         {
            KernelFilter k( filter.Kernel() );

            for ( int i = 0; i < k.Size(); ++i )
            {
               for ( int j = 0; j < k.Size(); ++j )
               {
                  float element = Round( k.Coefficients()[i][j], 6 );
                  // The elements of the KernelFilter can be accessed directly God thanks and the [] operator.
                  cols.Add( String().Format( "%10.6f", element ) );
               }
               html += TR( cols );
               cols.Clear();
            }
         }
         html += "</table></html>";
         // We got it!! we set the TextBox text by passing the composed String s.
         FilterCode_TextBox.SetText( html );
         UpdateTableColors();
      }

      if ( mode == "View" )
         LineCol_Label.Hide();
      else
         LineCol_Label.Show();

      LineCol_Sizer.SetSpacing( 4 );
      LineCol_Sizer.Add( LineCol_Label );
      LineCol_Sizer.AddStretch();

      // ### Save PushButton
      Save_PushButton.SetText( "Save" );
      Save_PushButton.SetCursor( StdCursor::Checkmark );
      Save_PushButton.OnClick( (Button::click_event_handler)&ConvolutionFilterCodeDialog::__Button_Click, *this );
      if ( mode == "View" )
         Save_PushButton.Hide();
      else
         Save_PushButton.SetDefault();

      if ( mode == "View" )
      {
         Cancel_PushButton.SetText( "Close" );
         Cancel_PushButton.SetCursor( StdCursor::Checkmark );
         Cancel_PushButton.SetDefault();
      }
      else
      {
         Cancel_PushButton.SetText( "Cancel" );
         Cancel_PushButton.SetCursor( StdCursor::Crossmark );
      }
      Cancel_PushButton.OnClick( (Button::click_event_handler)&ConvolutionFilterCodeDialog::__Button_Click, *this );

      DialogButtons_Sizer.SetSpacing( 8 );
      DialogButtons_Sizer.AddStretch();
      DialogButtons_Sizer.Add( Save_PushButton );
      DialogButtons_Sizer.Add( Cancel_PushButton );
      DialogButtons_Sizer.AddStretch();

      Global_Sizer.SetMargin( 4 );
      Global_Sizer.SetSpacing( 4 );
      Global_Sizer.Add( FilterCode_TextBox );
      Global_Sizer.Add( LineCol_Sizer );
      Global_Sizer.Add( DialogButtons_Sizer );

      SetSizer( Global_Sizer );
      EnableUserResizing();
      AdjustToContents();
      BringToFront();
      //SetFixedSize();

      if ( mode == "View" )
         SetWindowTitle( '\"' + filter.Name() + '\"' + " filter elements" );
      else if ( mode == "Edit" )
         SetWindowTitle( '\"' + filter.Name() + '\"' + " edit" );
      else if ( mode == "New" )
         SetWindowTitle( "New filter" );
      else
         throw Error( "Internal error: Invalid dialog operation mode in ConvolutionFilterCodeDialog" );
   }
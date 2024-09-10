    /////////////////////////////////////////////////////////////////////////////////////////
    // ThemedSkin::draw const
    //! Draws a standard checkbox control
    //! 
    //! \param[in,out] &chk - CheckBox to be drawn
    //! \param[in,out] &dc - Output device context
    //! \param[in] const &rc - Drawing rectangle
    /////////////////////////////////////////////////////////////////////////////////////////
    void draw(CheckBox<ENC>& chk, DeviceContext& dc, const RectL& rc) const override
    {
      Theme theme(chk.handle(), L"Button");
        
      // Determine state
      CHECKBOXSTATES state = CBS_UNCHECKEDNORMAL;
      if (!chk.Enabled)
        state = CBS_UNCHECKEDDISABLED;
      else if (chk.Check == ButtonState::Checked)    //else if (args.State && OwnerDrawState::Selected)
        state = CBS_UNCHECKEDPRESSED;
      else if (chk.isMouseOver())
        state = CBS_UNCHECKEDHOT;
      
      //if (chk.Checked == ButtonState::Checked)  //if (args.State && OwnerDrawState::Checked)
      //  state += (CBS_CHECKEDNORMAL-1);
      //if (chk.State && ButtonState::Checked)  
      //  state += (CBS_CHECKEDNORMAL-1);
      //else if (chk.Checked == ButtonState::Indeterminate)
      //  state += (CBS_MIXEDNORMAL-1);

      // Query content rect
      RectL rcContent = theme.content(dc, BP_CHECKBOX, state, rc);

      // Draw background
      dc.fill(rc, StockBrush::ButtonFace);

      // Calculate checkbox / text rectangles
      SizeL szCheckBox = theme.measure(dc, BP_CHECKBOX, state);
      RectL rcCheckBox = rcContent.arrange(szCheckBox, {RectL::FromLeft,Metrics::WindowEdge.Width}, RectL::Centre);
      
      // Draw checkbox
      theme.fill(dc, BP_CHECKBOX, state, rcCheckBox);

      // Draw text
      rcContent.Left = rcCheckBox.Right + Metrics::WindowEdge.Width;
      theme.write(dc, BP_CHECKBOX, state, chk.Text(), rcContent, DrawTextFlags::Left|DrawTextFlags::VCentre|DrawTextFlags::SingleLine);
      
      // [FOCUS] Draw focus rectangle
      if (chk.Focus)    //if (args.State && OwnerDrawState::Focus)
      {
        RectL rcText = theme.measure(dc, BP_CHECKBOX, state, chk.Text(), rcContent, DrawTextFlags::Left|DrawTextFlags::VCentre|DrawTextFlags::SingleLine);
        dc.focus(rcText);
      }
    }
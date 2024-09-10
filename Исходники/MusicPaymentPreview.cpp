void MusicPaymentPreview::PreLayoutManagement()
{
  nux::Geometry const& geo = GetGeometry();
  GetLayout()->SetGeometry(geo);

  previews::Style& style = dash::previews::Style::Instance();

  int content_width = geo.width - style.GetPanelSplitWidth().CP(scale) - style.GetDetailsLeftMargin().CP(scale) - style.GetDetailsRightMargin().CP(scale);
  int width = std::max<int>(0, content_width);

  if(full_data_layout_) { full_data_layout_->SetMaximumWidth(width); }
  if(header_layout_) { header_layout_->SetMaximumWidth(width); }
  if(intro_) { intro_->SetMaximumWidth(width); }
  if(form_layout_) { form_layout_->SetMaximumWidth(width); }
  if(footer_layout_) { footer_layout_->SetMaximumWidth(width); }

  // set the tab ordering
  SetFirstInTabOrder(password_entry_->text_entry());
  SetLastInTabOrder(buttons_map_[MusicPaymentPreview::CANCEL_PURCHASE_ACTION].GetPointer());
  SetLastInTabOrder(buttons_map_[MusicPaymentPreview::PURCHASE_ALBUM_ACTION].GetPointer());
  SetLastInTabOrder(buttons_map_[MusicPaymentPreview::CHANGE_PAYMENT_ACTION].GetPointer());
  SetLastInTabOrder(buttons_map_[MusicPaymentPreview::FORGOT_PASSWORD_ACTION].GetPointer());

  Preview::PreLayoutManagement();
}
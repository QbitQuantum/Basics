void SpriteImportDialog::onFileChange(wxFileDirPickerEvent& event) {
    m_hasfile = 1;

    // Attempt to load
    sd_vga_image_free(&m_img);
    int ret = sd_vga_image_from_png(&m_img, (char*)event.GetPath().mb_str().data());
    if(ret != SD_SUCCESS) {
        sd_vga_image_create(&m_img, 320, 200);
        wxMessageDialog md(
            this, 
            wxString::Format("Error while attempting to load image. Make sure the image is a 8bit paletted PNG file smaller than 320x200 pixels."), 
            _("Error"), 
            wxICON_ERROR|wxOK);
        md.ShowModal();
        return;
    }

    updateImage();
}
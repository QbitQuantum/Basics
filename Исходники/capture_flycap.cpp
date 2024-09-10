void CaptureFlycap::writeParameterValues(VarList * item) {
  if (!is_connected) {
    mutex.lock();
  }

  Error error;
  string item_name = item->getName();
  if (item_name == "Camera Parameters") {
    vector<VarType *> children = item->getChildren();
    for (unsigned int i=0;i<children.size();i++) {
      bool is_property=false;
      Property prop;

      string param_name = children[i]->getName();
      if (param_name == "Video Mode") {
        if (is_connected && !is_capturing) {
          Mode mode = videoModeFromString(v_videomode->getString());
          error = camera->SetGigEImagingMode(mode);
          if (error != PGRERROR_OK) {
            error.PrintErrorTrace();
            mutex.unlock();
            return;
          }
        }
      } else if (param_name == "Brightness") {
        is_property = true;
        prop.type = FlyCapture2::BRIGHTNESS;
      } else if (param_name == "Shutter") {
        is_property = true;
        prop.type = FlyCapture2::SHUTTER;
      }
      else if (param_name == "Gain") {
        is_property = true;
        prop.type = FlyCapture2::GAIN;
      }
      else if (param_name == "Gamma") {
        is_property = true;
        prop.type = FlyCapture2::GAMMA;
      }
      else if (param_name == "Frame Rate") {
        is_property = true;
        prop.type = FlyCapture2::FRAME_RATE;
      }
      else if (param_name == "White Balance") {
        is_property = true;
        prop.type = FlyCapture2::WHITE_BALANCE;
      }
      if (is_property) {
        prop.onePush = false;
        prop.onOff = true;
        prop.autoManualMode = false;
        prop.absControl = true;

        if (is_connected) {
          if (param_name == "White Balance")  {
            vector<VarType *> grandchildren = children[i]->getChildren();
            VarBool* vOnOff = (VarBool*)grandchildren[0];
            VarInt* vRed = (VarInt*)grandchildren[1];
            VarInt* vBlue = (VarInt*)grandchildren[2];
            prop.onOff = vOnOff->getBool();
            prop.valueA = vRed->getInt();
            prop.valueB = vBlue->getInt();
          }
          else {
            VarDouble* current_double = (VarDouble *)children[i];
            double absvalue = current_double->getDouble();
            prop.absValue = (float)absvalue;
          }

          error = camera->SetProperty(&prop);
          if (error != PGRERROR_OK) {
            mutex.unlock();
            error.PrintErrorTrace();
            return;
          }
        }
      }
    }
  }

  if (settings_changed) {
    if (is_connected) {
      GigEImageSettings imageSettings;
      imageSettings.offsetX = v_xoffset->getInt();
      imageSettings.offsetY = v_yoffset->getInt();
      imageSettings.height = v_height->getInt();
      imageSettings.width = v_width->getInt();
      imageSettings.pixelFormat = colorFormatToPixelFormat(Colors::stringToColorFormat(v_colormode->getString().c_str()));

      error = camera->SetGigEImageSettings(&imageSettings);
      if (error != PGRERROR_OK) {
        error.PrintErrorTrace();
        mutex.unlock();
        return;
      }

      settings_changed = false;
    }
  }

  if(!is_connected){
    mutex.unlock();
  }
}
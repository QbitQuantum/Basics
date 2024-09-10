void 
RangeSensorWidget::setRobot(const QString& _robot)
{
  QString error;
  bool ok = true;
  
  // build the lookup string for the naming service
  CosNaming::Name name;
  name.length(1);
  name[0].id = CORBA::string_dup(_robot.latin1());
  
  // try binding the robots naming context
  try {
    CosNaming::NamingContext_var namingContext =
      client_.resolveName<CosNaming::NamingContext>(name);
  }
  catch(const CORBA::Exception& e) {
    std::ostringstream sstr;
    sstr << "Robot " << _robot << endl
	 << "Communication Failed." << endl
	 << "CORBA exception: " << e << flush;
    
    error = sstr.str().c_str();
    ok = false;
  }
  
  if (ok) {
    if (timer_) {
      killTimer(timer_);
      timer_ = 0;
    }
    menuFile_->setItemEnabled(groupIndex_, false);

    robotName_ = _robot;
    sensor_ = Miro::RangeSensor::_nil();
    scan_ = NULL;
    scanDescription_ = NULL;
    setSensor(sensorName_);
  }
  else {
    calcCaption();
    QMessageBox::warning(this, "Couln't set robot:", error);
  }
}
int PIZStage::Initialize()
{
   MM::Device* device = GetDevice(controllerName_.c_str());
   if (device == NULL)
	   return ERR_GCS_PI_NO_CONTROLLER_FOUND;

   int ret = device->Initialize();
   if (ret != DEVICE_OK)
	   return ret;

   ctrl_ = PIController::GetByLabel(controllerName_);
   if (ctrl_ == NULL)
	   return ERR_GCS_PI_NO_CONTROLLER_FOUND;

   std::string  sBuffer;
   ctrl_->qIDN(sBuffer);
   LogMessage(std::string("Connected to: ") + sBuffer);

   ret = ctrl_->InitStage(axisName_, stageType_);
   if (ret != DEVICE_OK)
   {
	   LogMessage("Cannot init axis");
	   return ret;
   }

     // axis limits (assumed symmetrical)
   CPropertyAction* pAct = new CPropertyAction (this, &PIZStage::OnHoming);
   CreateProperty("HOMING", "", MM::String, false, pAct);

   pAct = new CPropertyAction (this, &PIZStage::OnVelocity);
   CreateProperty("Velocity", "", MM::Float, false, pAct);

   initialized_ = true;
   return DEVICE_OK;
}
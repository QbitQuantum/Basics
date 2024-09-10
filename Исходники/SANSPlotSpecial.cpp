Mantid::API::MatrixWorkspace_sptr SANSPlotSpecial::runIQTransform() {
  // Run the IQTransform algorithm for the current settings on the GUI
  Mantid::API::IAlgorithm_sptr iqt =
      Mantid::API::AlgorithmManager::Instance().create("IQTransform");
  iqt->initialize();
  try {
    iqt->setPropertyValue("InputWorkspace",
                          m_uiForm.wsInput->currentText().toStdString());
  } catch (std::invalid_argument &) {
    m_uiForm.lbPlotOptionsError->setText(
        "Selected input workspace is not appropriate for the IQTransform "
        "algorithm. Please refer to the documentation for guidelines.");
    return Mantid::API::MatrixWorkspace_sptr();
  }
  iqt->setPropertyValue("OutputWorkspace", "__sans_isis_display_iqt");
  iqt->setPropertyValue("TransformType",
                        m_uiForm.cbPlotType->currentText().toStdString());

  if (m_uiForm.cbBackground->currentText() == "Value") {
    iqt->setProperty<double>("BackgroundValue", m_uiForm.dsBackground->value());
  } else {
    iqt->setPropertyValue("BackgroundWorkspace",
                          m_uiForm.wsBackground->currentText().toStdString());
  }

  if (m_uiForm.cbPlotType->currentText() == "General") {
    std::vector<double> constants =
        m_transforms["General"]->functionConstants();
    iqt->setProperty("GeneralFunctionConstants", constants);
  }

  iqt->execute();

  Mantid::API::MatrixWorkspace_sptr result =
      boost::dynamic_pointer_cast<Mantid::API::MatrixWorkspace>(
          Mantid::API::AnalysisDataService::Instance().retrieve(
              "__sans_isis_display_iqt"));
  return result;
}
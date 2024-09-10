/**
 * Runs the moments algorithm with preview properties.
 */
void IndirectMoments::updatePreviewPlot(QString workspaceName)
{
    if(workspaceName.isEmpty())
        workspaceName = m_uiForm.dsInput->getCurrentDataName();

    QString outputName = workspaceName.left(workspaceName.length() - 4);
    double scale = m_uiForm.spScale->value();
    double eMin = m_dblManager->value(m_properties["EMin"]);
    double eMax = m_dblManager->value(m_properties["EMax"]);

    std::string outputWorkspaceName = outputName.toStdString() + "_Moments";

    IAlgorithm_sptr momentsAlg = AlgorithmManager::Instance().create("SofQWMoments");
    momentsAlg->initialize();
    momentsAlg->setProperty("Sample", workspaceName.toStdString());
    momentsAlg->setProperty("EnergyMin", eMin);
    momentsAlg->setProperty("EnergyMax", eMax);
    momentsAlg->setProperty("Plot", false);
    momentsAlg->setProperty("Save", false);
    momentsAlg->setProperty("OutputWorkspace", outputWorkspaceName);

    if(m_uiForm.ckScale->isChecked())
        momentsAlg->setProperty("Scale", scale);

    // Make sure there are no other algorithms in the queue.
    // It seems to be possible to have the selctionChangedLazy signal fire multiple times
    // if the renage selector is moved in a certain way.
    if(m_batchAlgoRunner->queueLength() == 0)
        runAlgorithm(momentsAlg);
}
void QInstallPage::initializePage()
{

    wizard()->button(QWizard::FinishButton)->setEnabled(false);

    screen->clear(); progressBar->reset(); progressBar->hide();

    createDirs(); installButton->setEnabled(true);

    createLogFile(installationDir);
}
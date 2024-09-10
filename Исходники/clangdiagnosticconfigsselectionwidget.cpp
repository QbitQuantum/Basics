void ClangDiagnosticConfigsSelectionWidget::connectToClangDiagnosticConfigsDialog(QPushButton *button)
{
    connect(button, &QPushButton::clicked, [this]() {
        ClangDiagnosticConfigsWidget *widget = new ClangDiagnosticConfigsWidget(currentConfigId());
        widget->layout()->setMargin(0);
        QDialog dialog;
        dialog.setWindowTitle(ClangDiagnosticConfigsWidget::tr("Diagnostic Configurations"));
        dialog.setLayout(new QVBoxLayout);
        dialog.layout()->addWidget(widget);
        auto *buttonsBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        dialog.layout()->addWidget(buttonsBox);
        connect(buttonsBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(buttonsBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        const bool previousEnableLowerClazyLevels = codeModelSettings()->enableLowerClazyLevels();
        connect(&dialog, &QDialog::accepted, [widget, previousEnableLowerClazyLevels]() {
            QSharedPointer<CppCodeModelSettings> settings = codeModelSettings();
            const ClangDiagnosticConfigs oldDiagnosticConfigs
                    = settings->clangCustomDiagnosticConfigs();
            const ClangDiagnosticConfigs currentDiagnosticConfigs = widget->customConfigs();
            if (oldDiagnosticConfigs != currentDiagnosticConfigs
                 || previousEnableLowerClazyLevels != codeModelSettings()->enableLowerClazyLevels()) {
                const ClangDiagnosticConfigsModel configsModel(currentDiagnosticConfigs);
                if (!configsModel.hasConfigWithId(settings->clangDiagnosticConfigId()))
                    settings->resetClangDiagnosticConfigId();
                settings->setClangCustomDiagnosticConfigs(currentDiagnosticConfigs);
                settings->toSettings(Core::ICore::settings());
            }
        });
        dialog.exec();
    });
}
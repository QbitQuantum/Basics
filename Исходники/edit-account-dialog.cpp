void EditAccountDialog::accept()
{
    if (!d->widget) {
        kWarning() << "missing d->widget, not saving parameters";
        return;
    }

    QVariantMap setParameters = d->widget->parametersSet();
    QStringList unsetParameters = d->widget->parametersUnset();

    // Check all pages of parameters pass validation.
    if (!d->widget->validateParameterValues()) {
        kDebug() << "A widget failed parameter validation. Not accepting wizard.";
        return;
    }

    //remove password from setParameters as this is now stored by kwallet instead
    setParameters.remove(QLatin1String("password"));
    unsetParameters.append(QLatin1String("password")); //remove the password from mission control

    Tp::PendingStringList *psl = d->account->updateParameters(setParameters, unsetParameters);

    kDebug() << "Set parameters:" << setParameters;
    kDebug() << "Unset parameters:" << unsetParameters;

    connect(psl,
            SIGNAL(finished(Tp::PendingOperation*)),
            SLOT(onParametersUpdated(Tp::PendingOperation*)));
}
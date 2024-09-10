void MOParametersDlg::pushedOk()
{
    _orgParameters->cloneFromOtherVector(_widget->localParameters());
    accept();
}
/**
\param bcont
**/
int BcBulmaCont_closeEvent ( BcBulmaCont *bcont )
{
    BcCompany *company = bcont->company();
    QFile file ( g_confpr->value( CONF_DIR_USER ) + "pluginbc_corrector_" + company->dbName() + ".cfn" );
    if ( !viewCorrector->isChecked() ) {
        file.remove();
    } else {
        file.open ( QIODevice::WriteOnly );
        file.close();
    } // end if
    return 0;
}
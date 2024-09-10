void easygx_set_quit_()
{
	QApplication *app = (QApplication *)easygx_application_get();
	app->exit(0);
}
TaskLoader::TaskLoader()
{
	registerHelper(new TaskMTRTable_TaskLoaderHelper());
	registerHelper(new TaskGroup_TaskLoaderHelper());
	registerHelper(new TaskQuestion_TaskLoaderHelper());
}
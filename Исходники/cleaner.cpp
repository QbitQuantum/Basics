// Removes object from disk and memory
bool Cleaner::RemoveFile(QString filepath)
{

	// use client0::RemoveFile
	return DeleteFileA(filepath.toAscii().constData());

// 	if(removed)
// 	{
// 		WorkLog::GetLog().printmain(QString("object was successfully removed: ") + filepath);
// 	} else 
// 	{
// 		WorkLog::GetLog().printmain(QString("warning! Object was not removed: ") + filepath);
// 	}

}
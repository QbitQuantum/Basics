int main(int argc, char **argv)
#endif
{
	// Create application object
	Application app;

	try {
		app.Initialize();
	}
	catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox(nullptr, (wchar_t*)e.getFullDescription().c_str(), L"An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		fprintf(stderr, "An exception has occured: %s\n",
			e.getFullDescription().c_str());
#endif
	}

	return 0;
}
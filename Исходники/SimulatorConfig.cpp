const string ProjectConfig::makeCommandLine(unsigned int mask /* = kProjectConfigAll */)
{
    stringstream buff;

    if (mask & kProjectConfigQuickRootPath)
    {
        const string path = SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath();
        if (path.length())
        {
            buff << " -quick ";
            buff << path;
        }
    }

    if (mask & kProjectConfigProjectDir)
    {
		const string path = getProjectDir();
		if (path.length())
		{
			buff << " -workdir ";
			buff << path;
		}
    }

    if (mask & kProjectConfigScriptFile)
    {
		const string path = getScriptFileRealPath();
		if (path.length())
		{
			buff << " -file ";
			buff << path;
		}
    }

    if (mask & kProjectConfigWritablePath)
    {
		const string path = getWritableRealPath();
		if (path.length())
		{
			buff << " -writable ";
			buff << path;
		}
    }

    if (mask & kProjectConfigPackagePath)
    {
        const string packagePath = getPackagePath();
        if (packagePath.length())
        {
            buff << " -package.path ";
            buff << packagePath;
        }
    }

    if (mask & kProjectConfigFrameSize)
    {
        buff << " -size ";
        buff << (int)getFrameSize().width;
        buff << "x";
        buff << (int)getFrameSize().height;
    }

    if (mask & kProjectConfigFrameScale)
    {
        if (getFrameScale() < 1.0f)
        {
            buff << " -scale ";
            buff.precision(2);
            buff << getFrameScale();
        }
    }

    if (mask & kProjectConfigWriteDebugLogToFile)
    {
        if (isWriteDebugLogToFile())
        {
            buff << " -write-debug-log";
        }
        else
        {
            buff << " -disable-write-debug-log";
        }
    }

    if (mask & kProjectConfigShowConsole)
    {
        if (isShowConsole())
        {
            buff << " -console";
        }
        else
        {
            buff << " -disable-console";
        }
    }

    if (mask & kProjectConfigLoadPrecompiledFramework)
    {
        if (isLoadPrecompiledFramework())
        {
            buff << " -load-framework";
        }
        else
        {
            buff << " -disable-load-framework";
        }
    }

    if (mask & kProjectConfigWindowOffset)
    {
        if (m_windowOffset.x != 0 && m_windowOffset.y != 0)
        {
            buff << " -offset {";
            buff << (int)m_windowOffset.x;
            buff << ",";
            buff << (int)m_windowOffset.y;
            buff << "}";
        }
    }

    if (mask & kProjectConfigDebugger)
    {
        switch (getDebuggerType())
        {
            case kCCLuaDebuggerLDT:
                buff << " -debugger-ldt";
                break;
            case kCCLuaDebuggerNone:
            default:
                buff << " -disable-debugger";
        }
    }

    return buff.str();
}
void CommandDir::exec(VirtualDiskNode* vfs)
{
    if (!vfs)
    {
        assert(0);
        return;
    }
    
    if (m_pathes.isEmpty())
    {
        m_pathes.append(vfs->pwd());
    }

    for (int i = 0; i < m_pathes.size(); ++i)
    {
        MyString path = m_pathes[i];
        if (!isNormalizedPath(path))
        {
            path = vfs->pathNormalize(path);
        }
        path = path.toLower();
        if (!vfs->isExist(path))
        {
            throw CommandException(_T("系统找不到指定路径\n"));
        }
        if (vfs->isFile(path))
        {
            FileHandler file_handler = vfs->openFile(path);
            state s = file_handler.stat();
            displayState(s, false);
            _tprintf(_T("%15d 个文件%14d 字节\n"), 1, s.size);
            _tprintf(_T("%15d 个目录\n"), 0);
        }
        if (vfs->isDir(path))
        {
            if (m_recursive)
            {
                listDirRecursive(path, vfs, m_only_dir);
            }
            else
            {
                listDir(path, vfs, m_only_dir);
            }
        }
    }
    return;
}
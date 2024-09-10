FileHandler VirtualDiskNode::createFile(MyString path)
{
    if (!isNormalizedPath(path))
    {
        assert(0);
        return FileHandler(nullptr);
    }
    MyString dir_path = dirname(path).toLower();
    DirNode* parent = getDirNode(dir_path);
    if (!parent)
        return FileHandler(nullptr);
    // 文件名创建时保留大小写
    MyString file_name = basename(path);
    if (parent->findFile(file_name) != -1)
    {
        return FileHandler(nullptr);
    }

    FileNode* nfile = parent->addFile();
    assert(nfile);
    nfile->set_name(file_name);
    nfile->set_path(path.toLower());
    return FileHandler(nfile);
}
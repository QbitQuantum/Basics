void TexturesSubFolder::rename() {
    std::string name;
    auto dia = new EnterTextDialog(name,this);
    dia->setLabel("Please enter the new name");
    dia->setModal(true);
    int returnCode = dia->exec();
    delete dia;

    if(returnCode == 255) {
        int index = dir_.substr(0, dir_.size()-1).find_last_of('/');
        std::string newPath = dir_.substr(0, index);

        QDir dir;
        dir.rename(dir_.c_str(), (newPath+"/"+name).c_str());
        heading_->setText(name.c_str());
        name_ = name;
        dir_ = newPath+"/"+name+"/";
    }
}
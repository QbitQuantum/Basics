bool TextureDefinitionList::setData(const QModelIndex & idx, const QVariant & value, int role)
{
    if(role == Qt::EditRole)
    {
        if(level && idx.row() >= 0 && idx.row() < level->textureDefinitions.getNumTextureDefinitions())
        {
            TextureDefinition temp;
            if(level->textureDefinitions.getTextureDefinition(idx.row(),&temp))
            {
                if(enforceValidData)
                {
                    QMessageBox msgbox;
                    msgbox.setIcon(QMessageBox::Warning);
                    int ret;

                    switch(idx.column())
                    {
                        case 0:
                            ret = level->textureDefinitions.findTextureDefByName(value.toString().toLocal8Bit().data());
                            if(ret != -1 && ret != idx.row())
                            {
                                msgbox.setText(tr("<b>Texture name already used by another entry!</b>"));
                                msgbox.setInformativeText(tr("Please enter a unique texture name. Name was taken by entry: ")+QString::number(ret));
                                msgbox.exec();
                                return false;
                            }
                            break;
                        case 1:
                            if(value.toInt() < 0 || value.toInt() >= level->textures.getNumTextures())
                            {
                                msgbox.setText(tr("<b>Texture idx is not valid!</b>"));
                                msgbox.setInformativeText(tr("Index must be between 0 and ")+QString::number(level->textures.getNumTextures())+".");
                                msgbox.exec();
                                return false;
                            }
                            break;
                    }
                }
                switch(idx.column())
                {
                    case 0:
                        temp.setName(value.toString().toLocal8Bit().data());
                        break;
                    case 1:
                        temp.texture = value.toInt();
                        break;
                    case 2:
                        temp.x = value.toInt();
                        break;
                    case 3:
                        temp.y = value.toInt();
                        break;
                    case 4:
                        temp.w = value.toInt();
                        break;
                    case 5:
                        temp.h = value.toInt();
                        break;
                }

                if(enforceValidData)
                {
                    if(temp.getX()+temp.getW() > 255)
                    temp.setW(255-temp.getX());
                    if(temp.getY()+temp.getH() > 255)
                    temp.setH(255-temp.getY());
                }

                level->textureDefinitions.setTextureDefinition(idx.row(),temp);
                int position = idx.row();
                if(resortOnChange)
                {
                    position = level->textureDefinitions.getSortedPosition(idx.row());
                    if(position != idx.row())
                    {
                        emit beginMoveRows(idx,idx.row(),idx.row(),idx,position);
                        level->textureDefinitions.resortTextureDefinition(idx.row());
                        emit endMoveRows();
                    }
                }
                emit dataChanged(index(position,idx.column()),index(position,idx.column()));
                return true;
            }
        }
    }
    return false;
};
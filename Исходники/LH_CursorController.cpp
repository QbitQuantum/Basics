void LH_CursorController::updateLocation(int xMod, int yMod, bool absolute)
{
    QStringList boundsList = setup_boundry_->value().split(',');
    QStringList badPoints = setup_invalid_coordinates_->value().split(';');

    bool moved = false;

    int newX = cursor_data_.x;
    int newY = cursor_data_.y;

    if (boundsList.length()>=4)
    {
        cursor_data_.range.x = (minmax){boundsList.at(0).toInt(), boundsList.at(2).toInt()};
        cursor_data_.range.y = (minmax){boundsList.at(1).toInt(), boundsList.at(3).toInt()};

        if (absolute)
        {
            if(xMod >= cursor_data_.range.x.min &&
               xMod <= cursor_data_.range.x.max &&
               yMod >= cursor_data_.range.y.min &&
               yMod <= cursor_data_.range.y.max
               )
            {
                newX = xMod;
                newY = yMod;
                QString point = QString::number(newX) + "," + QString::number(newY);
                if(!badPoints.contains(point)) moved = true;
            }
        } else
        if(xMod!=0 || yMod!=0)
        {
            int loops = 0;
            while (loops<=1 && !moved)
            {
                loops++;
                while(!moved &&
                      newX+xMod >= cursor_data_.range.x.min &&
                      newX+xMod <= cursor_data_.range.x.max &&
                      newY+yMod >= cursor_data_.range.y.min &&
                      newY+yMod <= cursor_data_.range.y.max
                      )
                {
                    newX += xMod;
                    newY += yMod;
                    QString point = QString::number(newX) + "," + QString::number(newY);
                    if(!badPoints.contains(point)) moved = true;
                    if(!setup_jump_invalid_->value()) break;


                }
                if(!setup_boundry_loop_->value()) break;
                else if(!moved)
                {
                    if(xMod==1)  newX = cursor_data_.range.x.min - xMod;
                    if(xMod==-1) newX = cursor_data_.range.x.max - xMod;
                    if(yMod==1)  newY = cursor_data_.range.y.min - yMod;
                    if(yMod==-1) newY = cursor_data_.range.y.max - yMod;
                }
            }
        }
    }

    if(moved) {
        cursor_data_.x = newX;
        cursor_data_.y = newY;
        if(setup_mode_->value()!=-1)
            if(cursorModes[setup_mode_->value()].select==smNone) doSelect("",0,0);
    }

    persistSelection();
    updateLinkData();

    setup_coordinate_->setValue(QString("%1,%2").arg(cursor_data_.x).arg(cursor_data_.y));
}
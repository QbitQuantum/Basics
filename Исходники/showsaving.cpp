void showsaving::timerEvent(QTimerEvent *event)
{
    char tmp[64];
    sprintf(tmp,"%d",step);
    QString t =tmp;
    QString s = path1 +t+ ".jpg";    //还有这里
    QString s2 = path2 +t+ ".jpg";   //第二张图的路径
    QImage* img=new QImage;
    QImage* img2 = new QImage;
    if(img->load(s)){
        ui->label->setPixmap(QPixmap::fromImage(*img));
        img2->load(s2);
        ui->label_4->setPixmap(QPixmap::fromImage(*img2));
        val += jmp;
        ui -> progressBar -> setValue(val);
        step++;
    }
    else killTimer(id);
}
int file_transform::dotransform_marker(V3DPluginCallback2 &callback, QWidget *parent)
{
    //input file name
    QString fileOpenName;
    fileOpenName = QFileDialog::getOpenFileName(0, QObject::tr("Open marker File"),
            "",
            QObject::tr("Supported file (*.marker)"
                ";;Marker file	(*.marker)"
                ));
    if(fileOpenName.isEmpty())
        return 0;
    QList <ImageMarker> inmarker;
    if (fileOpenName.toUpper().endsWith(".MARKER"))
    {
         inmarker = readMarker_file(fileOpenName);
    }

    QString fileMatName = QFileDialog::getOpenFileName(0, QObject::tr("Open Affine Matrix File"),
            "",
            QObject::tr("Supported file (*.txt)"
                ";;Affine Matrix    (*.txt)"
                ));
    if(fileMatName.isEmpty()) return 0;

    double afmatrix[16]={0};
    if (!readAmat(fileMatName.toStdString().c_str(),afmatrix))
    {
        v3d_msg("error read affine transform matrix.");
        return 0;
    }

    //marker affine
    double x,y,z;
    for(V3DLONG i=0; i<inmarker.size() ; i++)
    {
        ImageMarker* tp = &(inmarker[i]);
        x = afmatrix[0] * tp->x + afmatrix[1] * tp->y + afmatrix[2] * tp->z + afmatrix[3];
        y = afmatrix[4] * tp->x + afmatrix[5] * tp->y + afmatrix[6] * tp->z + afmatrix[7];
        z = afmatrix[8] * tp->x + afmatrix[9] * tp->y + afmatrix[10] * tp->z + afmatrix[11];

        //now update
        tp->x = x;	tp->y = y; tp->z = z;
    }

    QString fileDefaultName = fileOpenName+QString("_affine.marker");
    //write new marker to file
    QString fileSaveName = QFileDialog::getSaveFileName(0, QObject::tr("Save File"),
            fileDefaultName,
            QObject::tr("Supported file (*.marker)"
                ";;Marker	(*.marker)"
                ));
    if(fileSaveName.isEmpty())
        return 0;
    if (!writeMarker_file(fileSaveName, inmarker))
    {
        v3d_msg("fail to write the output marker file.");
        return 0;
    }

    return 1;
}
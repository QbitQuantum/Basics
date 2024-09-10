QImage Triangledetection::detect(const QImage &source, const QImage &imageBase)
{
    //QImage binary = detectionContour(extraireRouge(source));
    QImage binary = detectionContour(source);
    QImage detection = binary.convertToFormat(QImage::Format_RGB888);

    QVector<QPoint> ligne = hough(detection);
    std::cout << "-> Nombre de ligne detecté : " << ligne.size() << std::endl;

    QVector<QPoint> ligne_angle0,ligne_angle60,ligne_angle120;
    QPoint inter1,inter2,inter3;
    int l1,l2,l3;



    //Avoir les lignes avec des angles pouvant appartenir à un panneau (+ ou - 1°)
    avoirLigneAngle(ligne,ligne_angle0,90,1);
    avoirLigneAngle(ligne,ligne_angle0,270,1);

    avoirLigneAngle(ligne,ligne_angle60,150,1);
    avoirLigneAngle(ligne,ligne_angle60,330,1);

    avoirLigneAngle(ligne,ligne_angle120,210,1);
    avoirLigneAngle(ligne,ligne_angle120,30,1);

    //On determine les intersections et les longueurs des segments
    for(int i=0;i<ligne_angle0.size();i++)
    {
        for(int j=0;j<ligne_angle60.size();j++)
        {
            for(int k=0;k<ligne_angle120.size();k++)
            {

                inter1 = intersection(ligne_angle0[i],ligne_angle60[j]);
                inter2 = intersection(ligne_angle60[j],ligne_angle120[k]);
                inter3 = intersection(ligne_angle120[k],ligne_angle0[i]);

                l1 = distance(inter1,inter2);
                l2 = distance(inter2,inter3);
                l3 = distance(inter3,inter1);

                //Si les distance sont les mêmes et que tous les points sont dans l'image => on a un triangle
                if(l1 == l2 && l2 == l3 && l1 > 30 && l1 < 100 && estPointImage(detection,inter1) && estPointImage(detection,inter2) && estPointImage(detection,inter3))
                {
                    Triangle a;
                    a.p1 = inter1;
                    a.p2 = inter2;
                    a.p3 = inter3;
                    liste_triangle.push_back(a);
                }
            }
        }
    }

    std::cout<<"-> Nombre de triangle detectés avant élimination des doublons : " << liste_triangle.size() << std::endl;

    //On supprime les triangle doublons
    supprimerDoublon();

    //Dessiner les triangles à l'écran
    for(int i=0;i<liste_triangle.size();i++)
        dessiner(detection,liste_triangle[i],qRgb(0,255,127));


    //Generer les images avec les cercles reconnus
    for(int i=0;i<liste_triangle.size();i++)
    {
        int minX = liste_triangle[i].p1.x();
        int minY = liste_triangle[i].p1.y();
        int maxX = liste_triangle[i].p1.x();
        int maxY = liste_triangle[i].p1.y();
        if (liste_triangle[i].p2.x()<minX) minX = liste_triangle[i].p2.x();
        if (liste_triangle[i].p2.y()<minY) minY = liste_triangle[i].p2.y();
        if (liste_triangle[i].p2.x()>maxX) maxX = liste_triangle[i].p2.x();
        if (liste_triangle[i].p2.y()>maxY) maxY = liste_triangle[i].p2.y();
        if (liste_triangle[i].p3.x()<minX) minX = liste_triangle[i].p3.x();
        if (liste_triangle[i].p3.y()<minY) minY = liste_triangle[i].p3.y();
        if (liste_triangle[i].p3.x()>maxX) maxX = liste_triangle[i].p3.x();
        if (liste_triangle[i].p3.y()>maxY) maxY = liste_triangle[i].p3.y();


        QImage BlueRoadSigns = QImage(maxX-minX, maxY-minY, QImage::Format_RGB32);

        for(int row = 0;row<maxY-minY;row++)
        {
            for (int col=0;col<maxX-minX;col++)
            {
                QColor clrCurrent(imageBase.pixel(col+minX,row+minY));

                int red = clrCurrent.red();
                int green = clrCurrent.green();
                int blue = clrCurrent.blue();

                BlueRoadSigns.setPixel(col, row, qRgb(red,green,blue));
            }
        }

        liste_TrianglesReconnu.push_back(BlueRoadSigns);
    }

    std::cout<<"-> Nombre de triangle detectés : " << liste_triangle.size() << std::endl;

    return detection;
}
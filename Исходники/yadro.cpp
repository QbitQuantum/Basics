void Yadro::fly(GLfloat sferaV[80][3][3]/*, int flag*/, Sfera &sfera)
{
    const GLfloat pi=3.141593, k=pi/180;


    GLfloat x21 = sferaV[pli+plifinish][0][0]; GLfloat x22 = sferaV[pli+plifinish][1][0];  GLfloat x23 = sferaV[pli+plifinish][2][0];
    GLfloat y21 = sferaV[pli+plifinish][0][1]; GLfloat y22 = sferaV[pli+plifinish][1][1];  GLfloat y23 = sferaV[pli+plifinish][2][1];
    GLfloat z21 = sferaV[pli+plifinish][0][2]; GLfloat z22 = sferaV[pli+plifinish][1][2];  GLfloat z23 = sferaV[pli+plifinish][2][2];

    GLfloat x2 = (x21+x22+x23)/3;
    GLfloat y2 = (y21+y22+y23)/3;
    GLfloat z2 = (z21+z22+z23)/3;

    GLfloat r2      = sqrt(x2*x2 + y2*y2 + z2*z2);
    GLfloat theta2  = acos(z2/r2);
    GLfloat phi2    = atan2(y2,x2);


    for (int i = 0; i < 6; i++) {
        // Расчеты координат движущегося ядра
        GLfloat x1 = VertexArrayYadro[i][0];
        GLfloat y1 = VertexArrayYadro[i][1];
        GLfloat z1 = VertexArrayYadro[i][2];

        GLfloat r1 = sqrt(x1*x1 + y1*y1 + z1*z1);
        GLfloat theta1 = acos(z1/r1);
        GLfloat phi1 = atan2(y1,x1);

        if (delta1 == 0.0f) {
            // установка начальных параметров запуска
            delta1 = 1.0f;
            shag   = 50;
            deltaR = 0.05f;
            deltaTh = fabs(theta2 - theta1);
            deltaPh = fabs( phi2  -  phi1 );
            deltaTh = deltaTh / (GLfloat)shag;
            deltaPh = deltaPh / (GLfloat)shag;
            if ( theta1 < theta2) {
                signTh  = 1;
            } else {
                signTh  = 0;
            }

            if (  phi1  <  phi2 ) {
                signPh  = 1;
            } else {
                signPh  = 0;
            }
        }

        // По флагам усанавливаем стороны вращения
        if ( signTh  == 1 ) {
            theta1+=deltaTh;
        } else {
            theta1-=deltaTh;
        }

        if ( signPh  == 1 ) {
            phi1+=deltaPh;
        } else {
            phi1-=deltaPh;
        }

        if ( shag > 25) {
            r1+= deltaR;
        } else {
            r1-= deltaR;
        }


        if (shag > 0) {
            VertexArrayYadro[i][0]=r1*sin(theta1)*cos(phi1);
            VertexArrayYadro[i][1]=r1*sin(theta1)*sin(phi1);
            VertexArrayYadro[i][2]=r1*cos(theta1);
            int h = 43;
            if ( i == 5 ) {
                shag--;
            }
            doletelo = 0;
        }
        if (shag == 0 && pli < 80) {
            // Признак сработал. Ракета прилетела
            sfera.fail(pli+plifinish);
            doletelo = 1;
        }
    }
}
main()
{
    int driver = DETECT, mode;
    char c;
    int k1[] = { 0, 0, 20, 0, 20, 60, 30, 60, 30, 100, 0, 100, 0, 0 };
    int k2[] = { 40, 0, 50, 0, 50, 60, 60, 60, 60, 100, 30, 100, 30, 60, 40, 60, 40, 0 };
    int k3[] = { 70, 0, 90, 0, 90, 100, 60, 100, 60, 60, 70, 60, 70, 0 };
    int k4[] = { 90, 0, 110, 0, 110, 60, 120, 60, 120, 100, 90, 100, 90, 0 };
    int k5[] = { 130, 0, 140, 0, 140, 60, 150, 60, 150, 100, 120, 100, 120, 60, 130, 60, 130, 0 };
    int k6[] = { 160, 0, 170, 0, 170, 60, 180, 60, 180, 100, 150, 100, 150, 60, 160, 60, 160, 0 };
    int k7[] = { 190, 0, 210, 0, 210, 100, 180, 100, 180, 60, 190, 60, 190, 0 };
    int k8[] = { 210, 0, 230, 0, 230, 60, 240, 60, 240, 100, 210, 100, 210, 0 };
    int k9[] = { 250, 0, 260, 0, 260, 60, 270, 60, 270, 100, 240, 100, 240, 60, 250, 60, 250, 0 };
    int k10[] = { 280, 0, 300, 0, 300, 100, 270, 100, 270, 60, 280, 60, 280, 0 };
    int k11[] = { 300, 0, 330, 0, 330, 100, 300, 100, 300, 0 };
    int k12[] = { 330, 0, 360, 0, 360, 100, 330, 100, 330, 0 };
    initgraph(&driver, &mode, "");
    int maxx = getmaxx();
    int maxy = getmaxy();
    for (long j = 0; j <= 300; j++) {
        putpixel(random(maxx), random(maxy), 4);
        delay(1);
    }
    setfillstyle(SOLID_FILL, BLACK);
    bar(89, 39, 571, 261);
    setlinestyle(SOLID_LINE, 3, 3);
    line(90, 50, 90, 250); //outline
    line(100, 40, 540, 40);
    line(100, 260, 540, 260);
    line(550, 250, 550, 50);
    arc(100, 50, 90, 180, 10);
    arc(100, 250, 180, 270, 10);
    arc(540, 250, 270, 360, 10);
    arc(540, 50, 0, 90, 10);
    circle(200, 90, 35);
    setfillstyle(SOLID_FILL, 9);
    floodfill(200, 90, WHITE);
    circle(482, 95, 42);
    setfillstyle(SOLID_FILL, 3);
    floodfill(482, 95, WHITE);
    setlinestyle(SOLID_LINE, 1, 1);
    rectangle(270, 60, 370, 130);
    setfillstyle(SOLID_FILL, 14);
    floodfill(290, 80, WHITE);
    rectangle(270, 130, 295, 140);
    setfillstyle(SOLID_FILL, 5);
    floodfill(280, 135, WHITE);
    rectangle(295, 130, 320, 140);
    setfillstyle(SOLID_FILL, 5);
    floodfill(300, 135, WHITE);
    rectangle(320, 130, 345, 140);
    setfillstyle(SOLID_FILL, 5);
    floodfill(330, 135, WHITE);
    rectangle(345, 130, 370, 140);
    setfillstyle(SOLID_FILL, 5);
    floodfill(350, 135, WHITE);
    rectangle(120, 60, 145, 70);
    setfillstyle(SOLID_FILL, 1);
    floodfill(130, 65, WHITE);
    rectangle(120, 90, 145, 100);
    setfillstyle(SOLID_FILL, 1);
    floodfill(130, 95, WHITE);
    ellipse(132, 125, 0, 360, 11, 8);
    setfillstyle(SOLID_FILL, RED);
    floodfill(132, 125, WHITE);
    circle(230, 130, 5);
    setfillstyle(SOLID_FILL, RED);
    floodfill(230, 130, WHITE);
    rectangle(387, 60, 427, 75);
    setfillstyle(SOLID_FILL, 10);
    floodfill(395, 70, WHITE);
    rectangle(385, 90, 403, 110);
    setfillstyle(SOLID_FILL, 6);
    floodfill(390, 100, WHITE);
    rectangle(411, 90, 430, 110);
    setfillstyle(SOLID_FILL, 6);
    floodfill(420, 100, WHITE);
    rectangle(387, 120, 427, 135);
    setfillstyle(SOLID_FILL, 10);
    floodfill(395, 130, WHITE);
    rectangle(150, 260, 510, 250);
    setfillstyle(SOLID_FILL, 8);
    floodfill(180, 255, WHITE);
    circle(500, 120, 6);
    setfillstyle(SOLID_FILL, 8);
    floodfill(500, 120, WHITE);
    setviewport(225, 300, 530, 410, 1);
    int poly1[] = { 0, 2, 12, 60, 22, 54, 18, 28, 35, 2, 0, 2 };
    int poly2[] = { 10, 10, 23, 10, 14, 20, 10, 10 };
    int poly3[] = { 50, 0, 60, 2, 60, 45, 50, 42, 50, 0 };
    int poly4[] = { 71, 70, 83, 13, 105, 74, 87, 53, 71, 70 };
    int poly5[] = { 85, 30, 90, 45, 83, 43, 85, 30 };
    int poly6[] = { 110, 53, 120, 2, 130, 57, 148, 0, 135, 84, 132, 84, 118, 29, 110, 53 };
    int poly7[] = { 177, 2, 200, 35, 180, 85, 160, 33, 177, 2 };
    int poly8[] = { 178, 20, 190, 35, 179, 70, 166, 34, 178, 20 };
    drawpoly(6, poly1);
    setfillstyle(SOLID_FILL, RED);
    fillpoly(6, poly1);
    drawpoly(4, poly2);
    setfillstyle(SOLID_FILL, BLACK);
    fillpoly(4, poly2);
    drawpoly(5, poly3);
    setfillstyle(SOLID_FILL, RED);
    fillpoly(5, poly3);
    drawpoly(5, poly4);
    setfillstyle(SOLID_FILL, RED);
    fillpoly(5, poly4);
    drawpoly(4, poly5);
    setfillstyle(SOLID_FILL, BLACK);
    fillpoly(4, poly5);
    drawpoly(8, poly6);
    setfillstyle(SOLID_FILL, RED);
    fillpoly(8, poly6);
    drawpoly(5, poly7);
    setfillstyle(SOLID_FILL, RED);
    fillpoly(5, poly7);
    drawpoly(5, poly8);
    setfillstyle(SOLID_FILL, BLACK);
    fillpoly(5, poly8);
    setviewport(150, 150, 510, 250, 1);
    pnobody();
    c = getch();
    do {
        switch (c) {
        case 'q': {
            setfillstyle(SOLID_FILL, GREEN);
            fillpoly(7, k1);
            pno(261);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(7, k1);
            break;
        }
        case 'w': {
            setfillstyle(SOLID_FILL, RED);
            fillpoly(9, k2);
            pno(293);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(9, k2);
            pnobody();
            break;
        }
        case 'e': {
            setfillstyle(SOLID_FILL, GREEN);
            fillpoly(7, k3);
            pno(329);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(7, k3);
            pnobody();
            break;
        }
        case 'r': {
            setfillstyle(SOLID_FILL, RED);
            fillpoly(7, k4);
            pno(350);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(7, k4);
            pnobody();
            break;
        }
        case 't': {
            setfillstyle(SOLID_FILL, GREEN);
            fillpoly(9, k5);
            pno(392);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(9, k5);
            pnobody();
            break;
        }
        case 'y': {
            setfillstyle(SOLID_FILL, RED);
            fillpoly(9, k6);
            pno(440);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(9, k6);
            pnobody();
            break;
        }
        case 'u': {
            setfillstyle(SOLID_FILL, GREEN);
            fillpoly(7, k7);
            pno(493);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(7, k7);
            pnobody();
            break;
        }
        case 'i': {
            setfillstyle(SOLID_FILL, RED);
            fillpoly(7, k8);
            pno(523);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(7, k8);
            pnobody();
            break;
        }
        case 'o': {
            setfillstyle(SOLID_FILL, GREEN);
            fillpoly(9, k9);
            pno(587);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(9, k9);
            pnobody();
            break;
        }
        case 'p': {
            setfillstyle(SOLID_FILL, RED);
            fillpoly(7, k10);
            pno(659);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(7, k10);
            pnobody();
            break;
        }
        case '[': {
            setfillstyle(SOLID_FILL, GREEN);
            fillpoly(5, k11);
            pno(698);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(5, k11);
            pnobody();
            break;
        }
        case ']': {
            setfillstyle(SOLID_FILL, RED);
            fillpoly(5, k12);
            pno(784);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(5, k12);
            pnobody();
            break;
        }
        case '1': {
            setfillstyle(SOLID_FILL, YELLOW);
            bar(20, 0, 40, 60);
            pno(311);
            setfillstyle(SOLID_FILL, BLACK);
            bar(20, 0, 40, 60);
            pnobody();
            break;
        }
        case '2': {
            setfillstyle(SOLID_FILL, WHITE);
            bar(50, 0, 70, 60);
            pno(370);
            setfillstyle(SOLID_FILL, BLACK);
            bar(50, 0, 70, 60);
            pnobody();
            break;
        }
        case '4': {
            setfillstyle(SOLID_FILL, YELLOW);
            bar(110, 0, 130, 60);
            pno(415);
            setfillstyle(SOLID_FILL, BLACK);
            bar(110, 0, 130, 60);
            pnobody();
            break;
        }
        case '5': {
            setfillstyle(SOLID_FILL, WHITE);
            bar(140, 0, 160, 60);
            pno(466);
            setfillstyle(SOLID_FILL, BLACK);
            bar(140, 0, 160, 60);
            pnobody();
            break;
        }
        case '6': {
            setfillstyle(SOLID_FILL, YELLOW);
            bar(170, 0, 190, 60);
            pno(554);
            setfillstyle(SOLID_FILL, BLACK);
            bar(170, 0, 190, 60);
            pnobody();
            break;
        }
        case '8': {
            setfillstyle(SOLID_FILL, WHITE);
            bar(230, 0, 250, 60);
            pno(662);
            setfillstyle(SOLID_FILL, BLACK);
            bar(230, 0, 250, 60);
            pnobody();
            break;
        }
        case '9': {
            setfillstyle(SOLID_FILL, YELLOW);
            bar(260, 0, 280, 60);
            pno(740);
            setfillstyle(SOLID_FILL, BLACK);
            bar(260, 0, 280, 60);
            pnobody();
            break;
        }
        case 'Q': {
            setfillstyle(SOLID_FILL, GREEN);
            fillpoly(7, k1);
            pno(261);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(7, k1);
            break;
        }
        case 'W': {
            setfillstyle(SOLID_FILL, RED);
            fillpoly(9, k2);
            pno(293);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(9, k2);
            pnobody();
            break;
        }
        case 'E': {
            setfillstyle(SOLID_FILL, GREEN);
            fillpoly(7, k3);
            pno(329);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(7, k3);
            pnobody();
            break;
        }
        case 'R': {
            setfillstyle(SOLID_FILL, RED);
            fillpoly(7, k4);
            pno(350);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(7, k4);
            pnobody();
            break;
        }
        case 'T': {
            setfillstyle(SOLID_FILL, GREEN);
            fillpoly(9, k5);
            pno(392);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(9, k5);
            pnobody();
            break;
        }
        case 'Y': {
            setfillstyle(SOLID_FILL, RED);
            fillpoly(9, k6);
            pno(440);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(9, k6);
            pnobody();
            break;
        }
        case 'U': {
            setfillstyle(SOLID_FILL, GREEN);
            fillpoly(7, k7);
            pno(493);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(7, k7);
            pnobody();
            break;
        }
        case 'I': {
            setfillstyle(SOLID_FILL, RED);
            fillpoly(7, k8);
            pno(523);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(7, k8);
            pnobody();
            break;
        }
        case 'O': {
            setfillstyle(SOLID_FILL, GREEN);
            fillpoly(9, k9);
            pno(587);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(9, k9);
            pnobody();
            break;
        }
        case 'P': {
            setfillstyle(SOLID_FILL, RED);
            fillpoly(7, k10);
            pno(659);
            setfillstyle(SOLID_FILL, BLUE);
            fillpoly(7, k10);
            pnobody();
            break;
        }
        case ' ': {
            break;
        }
        }
        c = getch();
    } while (c != ' ');
    setviewport(0, 0, maxx, maxy, 1);
    cleardevice();
    for (j = 0; j <= 1100; j++) {
        putpixel(random(maxx), random(maxy), 4);
        delay(1);
    }
    setcolor(4);
    outtextxy(270, 150, "C R E D I T S");
    for (int i = 0; i <= 3; i++) {
        outtextxy(260, 155 + i, "_______________");
    }
    delay(600);
    outtextxy(150, 200, " #Suvojit Manna:Concept & Design,Core Programing");
    outtextxy(160, 205, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ ");
    delay(600);
    outtextxy(165, 250, " #Prangshu Shyam:Graphical Assisstance");
    outtextxy(180, 255, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ ");
    delay(600);
    outtextxy(200, 300, " #Sourav Kundu:Final Compilation");
    outtextxy(210, 305, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ ");
    getch();
    return 0;
}
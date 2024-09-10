//fungsi rekursif hilbert dengan pola-pola tertentu
void drawHilbert(int *x, int *y, int lengthX, int lengthY, int lvl){
    if(lvl>0){
        drawHilbert (x, y,  lengthY,  lengthX, lvl-1);
        lineForward (x, y,  lengthX, -lengthY, BLACK);
        drawHilbert (x, y,  lengthX,  lengthY, lvl-1);
        lineForward (x, y,  lengthY, -lengthX, BLACK);
        drawHilbert (x, y,  lengthX,  lengthY, lvl-1);
        lineForward (x, y, -lengthX,  lengthY, BLACK);
        drawHilbert (x, y, -lengthY, -lengthX, lvl-1);
    }
}
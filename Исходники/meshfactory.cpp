Mesh MeshFactory::rectangleComplexe ( int precision, double longueur, double largeur)
{
    Mesh rectangle;

    Mesh faceTete = MeshFactory::planComplexe(precision);
    rectangle += faceTete;

    Mesh faceQueue = faceTete.copie();
    faceQueue.translation(0,0,1);
    rectangle += faceQueue;

    Mesh facetop = faceTete.copie();
    facetop.rotation(0,90);
    rectangle += facetop;

    Mesh facetop2 = faceTete.copie();
    facetop2.rotation(0,90);
    facetop2.translation(0,1,0);
    rectangle += facetop2;

    Mesh faceCote = faceTete.copie();
    faceCote.rotation(1,-90);
    rectangle += faceCote;

    Mesh faceCote2 = faceCote.copie();
    faceCote2.translation(1,0,0);
    rectangle += faceCote2;

    rectangle.redimensionner(largeur, largeur, longueur);
    return rectangle;
}
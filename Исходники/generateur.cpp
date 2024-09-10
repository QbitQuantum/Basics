MeshBase::Mesh Generateur::generateurTemple ( double taille )
{

    MeshBase::Mesh temple = Generateur::generateurBaseColonnes(taille);
    //temple.translation(taille/2, taille/2,0);
    std::cout <<"colonesBases passée"<<std::endl;


    MeshBase::Mesh meshToiture = generateurDalle(taille);
    meshToiture.redimensionner(1,1,0.1);
    double valTranslate = - temple.getMaxZ() ;
    meshToiture.translation(0,0, valTranslate );
    temple += meshToiture;
    std::cout <<"oiture passée"<<std::endl;
    MeshBase::Mesh pentadre = Generateur::pentaedrePyramidal();
    pentadre.translation(-0.5,-0.5,0);
    pentadre.rotation(0,180);
    pentadre.redimensionner(taille/10, taille, taille/10 );
    pentadre.translation(taille/20,taille/2, valTranslate );
    temple += pentadre;

    std::cout <<"pentaedre passée"<<std::endl;

    double angle =9.4;

    MeshBase::Mesh tuiles = Generateur::generateurPlanOnduleeTuile();
    tuiles.rotation(0,180);
    tuiles.redimensionner(taille, taille/2,1);
    MeshBase::Mesh tuile2 = tuiles;
    tuile2.rotation(0,angle);
    tuile2.translation(0, 2* ( taille/2 ) + 0.035  ,-temple.getMaxZ() +  0.5);
    tuile2.redimensionner(0.8, 1,1);
    tuile2.translation(taille/10, 0,0);
    temple += tuile2;

    std::cout <<"tuiles passée"<<std::endl;

    MeshBase::Mesh cylindreArrond = MeshBase::MeshFactory::cylindre(taille*0.99,taille/45, 32);
    cylindreArrond.rotation(1,90);
    cylindreArrond.translation(0.005,taille/2 , - temple.getMaxZ()+ taille/85);
    temple += cylindreArrond;
    std::cout <<"cylindre passée"<<std::endl;



    MeshBase::Mesh cylindreArrondBord = MeshBase::MeshFactory::cylindre(taille,taille/45, 32);
    cylindreArrondBord.rotation(1,90);
    cylindreArrondBord.translation(0,0 , - taille/2);
    temple += cylindreArrondBord;
    cylindreArrondBord.translation(0,taille, 0);
    temple += cylindreArrondBord;

    tuiles.rotation(0,-angle);
    tuiles.translation(0, taille/2  + 0.035,-temple.getMaxZ() + 0.087 );
    tuiles.redimensionner(0.8, 1,1);
    tuiles.translation(taille/10, 0,0);
    temple += tuiles;


    pentadre.translation(taille -taille/10,0, 0 );
    temple += pentadre;

    return temple;
}
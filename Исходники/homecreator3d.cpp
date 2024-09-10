/* Méthode qui permet de créer les connexions entre les différents objets */
void HomeCreator3D::createConnection()
{
    QObject::connect(&window, SIGNAL(itemSelected(QString)), this, SLOT(itemSelected(QString)));
    QObject::connect(window.getUi()->widget, SIGNAL(constructionOK()), this, SLOT(enable3D()));
    QObject::connect(window.getUi()->widget, SIGNAL(objectChangePosition(double, double, double)), this, SLOT(objectMove(double, double, double)));
    QObject::connect(window.getUi()->widget, SIGNAL(objectChangeRotation()), this, SLOT(objectRotate()));
    QObject::connect(window.getUi()->widget, SIGNAL(selection(int)), this, SLOT(selection(int)));
    QObject::connect(window.getUi()->widget, SIGNAL(deleteObject()), this, SLOT(deleteObject()));

    QObject::connect(&window, SIGNAL(newHouse()), this, SLOT(reInit()));
    QObject::connect(&window, SIGNAL(loadHouse(QString)), this, SLOT(loadMaison(QString)));
    QObject::connect(&window, SIGNAL(saveHouse(QString)), this, SLOT(saveMaison(QString)));
}
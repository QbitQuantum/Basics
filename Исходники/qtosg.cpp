int main(int argc, char** argv)
{
//    QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    SetProcessDPIAware();

    QApplication qapp(argc, argv);

    int x = QApplication::desktop()->physicalDpiX();
    int y = QApplication::desktop()->physicalDpiY();
    double scaleX = 284.0/double(x);
    double scaleY = 285.0/double(y);

    std::cout << x << " " << y << std::endl;
    std::cout << QApplication::desktop()->logicalDpiX() << " " << QApplication::desktop()->logicalDpiY() << std::endl;



    QMainWindow window;
    QtOSGWidget* widget = new QtOSGWidget(1, 1, &window);
    window.setCentralWidget(widget);
    window.show();

    std::cout << scaleX << " " << scaleY << std::endl;
//    std::cout << pr << " " << ps << std::endl;

    return qapp.exec();
}
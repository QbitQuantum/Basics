int main(){
    Point *a = new Point(2, 3);
    Point *b = new Point (3, 7);

std::cout << *a << std::endl;

    std::cout << a->distance(*b) << std::endl;
    std::cout << a->distance(*b) << std::endl;

    a->setY(5.4);
    a->setX(0.5);

    if ( a!=b ) {
    std::cout << *b << std::endl;
    }

std::cout << *a << std::endl;



    delete a;
    delete b;
    
    return 0;
}
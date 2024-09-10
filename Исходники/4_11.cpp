int main(){
	Rectangle rect;
	rect.set(10,2,25,20);
	cout << rect.getH() << " , " << rect.getW() << endl;
	Point * p = rect.getLoc();
	cout << p->getX() << " , " << p->getY() << endl;
}
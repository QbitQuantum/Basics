ImageClass::ImageClass(const ImageClass& anImageClassObject)
{
	//copy the image object from anImageClassObject into myImage
	myImage = CopyImage(anImageClassObject.myImage);

	//set the name of myImage
	name = anImageClassObject.name + "-Copy";

	//print out constructor identification
	cout << "Constructor: Copy - " << name << std::endl;
}
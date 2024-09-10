/**
 * Constructor for a leaf (number) node
 */
Expression::Expression(Number num)
{
	// Initilize the pointers to null
	this->left = nullptr;
	this->right = nullptr;
	
	// Initilize the operation to the null operatoon
	this->op = Operator();
	
	// Initlize the number to num
	this->num = num;
}
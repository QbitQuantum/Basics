///Evaluates the gradient at the point pX, pY
Vector2F BaseExpression::gradient(F32 pX, F32 pY)
{
	BaseExpression* t = derivative(XVAR);
    return Vector2F(
                    derivative(XVAR)->evaluate(pX, pY), 
                    derivative(YVAR)->evaluate(pX, pY)
                    );
}
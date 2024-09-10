/*! \brief Calculate angle between two vectors

 Dependancies: Vector3D definitions and routines
*/
double Routines::CalcAngle(Base::Vector3f a,Base::Vector3f  b,Base::Vector3f c)
{
    Base::Vector3f First = a - b;
    Base::Vector3f Second = c - b;
    Base::Vector3f Third = c - a;
    //double test1 = First.Length(), test2 = Second.Length(), test3 = Third.Length();
    double UpperTerm = (First.Length() * First.Length()) + (Second.Length() *Second.Length()) - (Third.Length() * Third.Length() );
    double LowerTerm = 2 * First.Length() * Second.Length() ;
    double ang = acos( UpperTerm / LowerTerm );
    return ang;
}
void PositionStateComplete::setTran(const transf &t)
{
	getVariable("Tx")->setValue( t.translation().x() );
	getVariable("Ty")->setValue( t.translation().y() );
	getVariable("Tz")->setValue( t.translation().z() );
	getVariable("Qw")->setValue( t.rotation().w );
	getVariable("Qx")->setValue( t.rotation().x );
	getVariable("Qy")->setValue( t.rotation().y );
	getVariable("Qz")->setValue( t.rotation().z );
}
void Scene::LightLookAtMatrix( int i )
{
	Point lightPos( light[i]->GetCurrentPos() );
	Point at( camera->GetAt() );
	Vector view = at-lightPos;
	view.Normalize();
	Vector perp = abs( view.Dot( Vector::YAxis() ) ) < 0.95 ? view.Cross( Vector::YAxis() ) : view.Cross( Vector::XAxis() );
	perp.Normalize();
	Vector up = perp.Cross( view );
	gluLookAt( lightPos.X(), lightPos.Y(), lightPos.Z(), 
		       at.X(), at.Y(), at.Z(), 
			   up.X(), up.Y(), up.Z() );
}
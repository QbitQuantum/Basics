/*!
  Takes pointers to the two bodies in contact, and the set of contacts returned
  from the collision detection system, and adds a contact to each body for each
  contact in the set.
 */
void
addContacts(Body *body1, Body *body2, ContactReport &contactSet, bool softContactsOn )
{
	ContactReport::iterator cp;
	Contact *c1,*c2;
	int i;

	if ( softContactsOn && ( body1->isElastic() || body2->isElastic() ) ) {
		findSoftNeighborhoods( body1, body2, contactSet);
		DBGP("Before merge: " << contactSet.size());
		mergeSoftNeighborhoods( body1, body2, contactSet);
		DBGP("After merge: " << contactSet.size());
	}

	for (i=0,cp=contactSet.begin();cp!=contactSet.end();cp++,i++) {

		DBGP( body1->getName().latin1() << " - " << body2->getName().latin1() << " contact: " <<
		cp->b1_pos << " " <<  cp->b1_normal );

		//this is an attempt to check if the contact normals point in the right direction
		//based on the distance between the bodies. It is meant to help with bad geometry with ill-defined
		//normals. Can be removed completely - should never come up for good geometry
		if (! checkContactNormals(body1, body2, &(*cp)) ) {
			DBGP("Wrong normals detected!");
		}
		if ( softContactsOn && ( body1->isElastic() || body2->isElastic() ) ) {
			c1 = new SoftContact( body1, body2, cp->b1_pos, cp->b1_normal, &(cp->nghbd1) );
			c2 = new SoftContact( body2, body1, cp->b2_pos, cp->b2_normal, &(cp->nghbd2) );
			c1->setMate(c2);
			c2->setMate(c1);

			((SoftContact *)c1)->setUpFrictionEdges();
			((SoftContact *)c2)->setUpFrictionEdges();
		} else {
			c1 = new PointContact(body1,body2,cp->b1_pos,cp->b1_normal);
			c2 = new PointContact(body2,body1,cp->b2_pos,cp->b2_normal);
			c1->setMate(c2);
			c2->setMate(c1);
		}

		body1->addContact(c1);
		body2->addContact(c2);

		//check if the new contacts inherit two contacts from previous time step
		//if so, remove ancestors so nobody else inherits them
		Contact *ancestor = body1->checkContactInheritance(c1);
		if (ancestor) {
			c1->inherit(ancestor);
			if (!ancestor->getMate()) 
				fprintf(stderr,"No mate for inherited contact!!\n");
			else
				c2->inherit(ancestor->getMate());
			//careful: this also deletes the removed contact so remove the mate first
			if (ancestor->getMate()) body2->removePrevContact( ancestor->getMate() );
			body1->removePrevContact( ancestor );
		} else {
			ancestor = body2->checkContactInheritance(c2);
			if (ancestor){
				if (!ancestor->getMate())
					fprintf(stderr,"No mate for inherited contact!!\n");
				else		
					c1->inherit(ancestor->getMate());
				c2->inherit(ancestor);
				if (ancestor->getMate()) body1->removePrevContact( ancestor->getMate() );
				body2->removePrevContact( ancestor );
			} else {
//				fprintf(stderr,"New contact between %s and %s\n",body1->getName().latin1(), body2->getName().latin1() );
			}
		}
	}
}
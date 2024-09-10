		void ContactManifold::update(float dt)
		{
			float maxsep = mSimulator->getMaxContactSeparation();

			bool update = false;
			Quaternion qa = Quaternion::IDENTITY;
			Quaternion qb = Quaternion::IDENTITY;

			RigidBody *ra = mA->getBody();
			RigidBody *rb = mB->getBody();

			if (ra)
			{
				Vector3 aa = ra->getAngularVelocity();
				float aalen = aa.normalise();
				if (aalen > 0.0f)
				{
					qa = Quaternion(aa, aalen * dt);
					qa.normalise();
					update = true;
				}
			}
			if (rb)
			{
				Vector3 ab = rb->getAngularVelocity();
				float ablen = ab.normalise();
				if (ablen > 0.0f)
				{
					qb = Quaternion(ab, ablen * dt);
					qb.normalise();
					update = true;
				}
			}

			if (update)
			{
				float minp = 99999999.f;
				int mini = 0;
				int cntc = 0;

				for (int i = -1; ++i < 5;)
				{
					Contact *c = mContacts[i];
					if (!c) continue;

					Quaternion rcpq1 = qa * Quaternion(0, c->mRcp1.x, c->mRcp1.y, c->mRcp1.z) * qa.conjugate();
					Quaternion rcpq2 = qb * Quaternion(0, c->mRcp2.x, c->mRcp2.y, c->mRcp2.z) * qb.conjugate();

					c->mRcp1 = Vector3(rcpq1.x, rcpq1.y, rcpq1.z);
					c->mRcp2 = Vector3(rcpq2.x, rcpq2.y, rcpq2.z);

					Vector3 ba = (c->mRcp1 + mA->getTransform()->getTranslation()) - (c->mRcp2 + mB->getTransform()->getTranslation());
					c->mPenetration = ba.dot(c->mNormal);

					if (c->mPenetration < -maxsep || ((c->mNormal * c->mPenetration) - ba).length() > maxsep)
					{
						delete c;
						mContacts[i] = 0;
						continue;
					}

					cntc++;
					if (c->mPenetration < minp)
					{
						minp = c->mPenetration;
						mini = i;
					}
				}

				if (cntc > 4)
				{
					delete mContacts[mini];
					mContacts[mini] = 0;
				}
			}
		}
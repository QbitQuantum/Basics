void CPieceProjectile::Draw()
{
	if (flags & PF_NoCEGTrail) {
		if (flags & PF_Smoke) {
			// this piece leaves a default (non-CEG) smoketrail
			inArray = true;
			float age2 = (age & 7) + globalRendering->timeOffset;
			float color = 0.5f;
			unsigned char col[4];

			float3 dir = speed;
			dir.Normalize();

			int numParts = age & 7;
			va->EnlargeArrays(4+4*numParts,0,VA_SIZE_TC);
			if (drawTrail) {
				// draw the trail as a single quad if camera close enough
				const float3 dif  = (drawPos - camera->pos).Normalize();
				const float3 dir1 = (dif.cross(dir)).Normalize();
				const float3 dif2 = (oldSmokePos - camera->pos).Normalize();
				const float3 dir2 = (dif2.cross(oldSmokeDir)).Normalize();

				float a1 = ((1 - 0.0f / (Smoke_Time)) * 255) * (0.7f + fabs(dif.dot(dir)));
				float alpha = std::min(255.0f, std::max(0.f, a1));
				col[0] = (unsigned char) (color * alpha);
				col[1] = (unsigned char) (color * alpha);
				col[2] = (unsigned char) (color * alpha);
				col[3] = (unsigned char) (alpha);

				unsigned char col2[4];
				float a2 = ((1 - float(age2) / (Smoke_Time)) * 255) * (0.7f + fabs(dif2.dot(oldSmokeDir)));

				if (age < 8)
					a2 = 0;

				alpha = std::min(255.0f, std::max(0.f, a2));
				col2[0] = (unsigned char) (color * alpha);
				col2[1] = (unsigned char) (color * alpha);
				col2[2] = (unsigned char) (color * alpha);
				col2[3] = (unsigned char) (alpha);

				const float size = 1.0f;
				const float size2 = 1 + (age2 * (1 / Smoke_Time)) * 14;
				const float txs =
					projectileDrawer->smoketrailtex->xstart -
					(projectileDrawer->smoketrailtex->xend - projectileDrawer->smoketrailtex->xstart) *
					(age2 / 8.0f);

				va->AddVertexQTC(drawPos - dir1 * size, txs, projectileDrawer->smoketrailtex->ystart, col);
				va->AddVertexQTC(drawPos + dir1 * size, txs, projectileDrawer->smoketrailtex->yend,   col);
				va->AddVertexQTC(oldSmokePos + dir2 * size2, projectileDrawer->smoketrailtex->xend, projectileDrawer->smoketrailtex->yend,   col2);
				va->AddVertexQTC(oldSmokePos - dir2 * size2, projectileDrawer->smoketrailtex->xend, projectileDrawer->smoketrailtex->ystart, col2);
			} else {
				// draw the trail as particles
				const float dist = pos.distance(oldSmokePos);
				const float3 dirpos1 = pos - dir * dist * 0.33f;
				const float3 dirpos2 = oldSmokePos + oldSmokeDir * dist * 0.33f;

				for (int a = 0; a < numParts; ++a) { //! CAUTION: loop count must match EnlargeArrays above
					float alpha = 255.0f;
					col[0] = (unsigned char) (color * alpha);
					col[1] = (unsigned char) (color * alpha);
					col[2] = (unsigned char) (color * alpha);
					col[3] = (unsigned char) (alpha);

					const float size = 1.0f + ((a) * (1.0f / Smoke_Time)) * 14.0f;
					const float3 pos1 = CalcBeizer(float(a) / (numParts), pos, dirpos1, dirpos2, oldSmokePos);

					#define st projectileDrawer->smoketex[0]
					va->AddVertexQTC(pos1 + ( camera->up+camera->right) * size, st->xstart, st->ystart, col);
					va->AddVertexQTC(pos1 + ( camera->up-camera->right) * size, st->xend,   st->ystart, col);
					va->AddVertexQTC(pos1 + (-camera->up-camera->right) * size, st->xend,   st->ystart, col);
					va->AddVertexQTC(pos1 + (-camera->up+camera->right) * size, st->xstart, st->ystart, col);
					#undef st
				}
			}
		}
	}

	DrawCallback();
}
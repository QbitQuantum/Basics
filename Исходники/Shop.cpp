Mesh* Shop::ShopInteraction(double dt, Camera5 camera, Mesh** meshList)
{

	float range = 20;
	float offset = 0.5;

	for (Vector3 temp = camera.view.Normalized(); temp.Length() <= range; temp += camera.view.Normalized())
	{
			if (meshList[SP2::GEO_STORE]->min != nullptr || meshList[SP2::GEO_STORE]->max != nullptr)
			{
				if ((temp.x + camera.position.x <= meshList[SP2::GEO_STORE]->max->x + meshList[SP2::GEO_STORE]->position.x + offset && temp.x + camera.position.x >= meshList[SP2::GEO_STORE]->min->x + meshList[SP2::GEO_STORE]->position.x - offset) //Check min and max for x
					&& (temp.y + camera.position.y <= meshList[SP2::GEO_STORE]->max->y + meshList[SP2::GEO_STORE]->position.y + offset && temp.y + camera.position.y >= meshList[SP2::GEO_STORE]->min->y + meshList[SP2::GEO_STORE]->position.y - offset) //Check min and max for y
					&& (temp.z + camera.position.z <= meshList[SP2::GEO_STORE]->max->z + meshList[SP2::GEO_STORE]->position.z + offset && temp.z + camera.position.z >= meshList[SP2::GEO_STORE]->min->z + meshList[SP2::GEO_STORE]->position.z - offset)) //Check min and max for z
				{
					if (meshList[SP2::GEO_STORE]->lookAtShop == false)
					{
						return nullptr;
						break;
					}
					else
					{
						return meshList[SP2::GEO_STORE];
						break;
					}
			}
		}
	}
	return nullptr;
}
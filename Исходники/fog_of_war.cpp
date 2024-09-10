void fog_of_war::Render(Controller * ctrl, ScreenUniformData * u_data, glm::vec2 position, GameObject *g_obj)
{

	this->GetFOW(g_obj,glm::ivec2(position));

	


	for (int j = g_obj->GetScroller()->GetBeginLimit().y; j < g_obj->GetScroller()->GetEndLimit().y; j++)
	{



		for (int i = g_obj->GetScroller()->GetBeginLimit().x; i < g_obj->GetScroller()->GetEndLimit().x; i++)
		{



			if (this->s_map[i][j] == DARK)
			{


				u_data->SetAmbientLight(glm::vec4(1.f, 1.f, 1.f, 0.8f));
				u_data->ApplyMatrix(Translation(glm::vec2(i * 32, j * 32))*Scale(glm::vec2(32, 32)));
				this->m_sprite->Render(NULL);



			}



		}



	}

	this->Advance(g_obj);
}
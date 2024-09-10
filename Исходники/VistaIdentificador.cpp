void VistaIdentificador::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	std::vector<VistaAtributo *>::iterator i;
	std::vector<VistaUnionEntidadRelacion *>::iterator j;
	cr->set_line_width(1);
	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(), colorDeSeleccion.get_green_p(),
				colorDeSeleccion.get_blue_p());
	}

	double x0, x1, y0, y1;

	if (this->vistasAtributo.size() == 1) {
		if (this->vistasEntidadesFuertes.empty()) {
			this->vistasAtributo[0]->setEsIdentificador(true);
			this->vistasAtributo[0]->dibujar(cr);
		} else {
			this->vistasAtributo[0]->getPuntoMedioLinea(x0, y0);
			cr->arc(x0, y0, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
			cr->fill();
			cr->move_to(x0, y0);
			for (j = this->vistasEntidadesFuertes.begin(); j != this->vistasEntidadesFuertes.end();
					j++) {
				(*j)->getPuntoMedioLinea(x1, y1);
				cr->line_to(x1, y1);
				cr->stroke();
				cr->arc(x1, y1, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
				cr->fill();
				cr->move_to(x0, y0);
			}
			cr->stroke();
		}
	} else {
		this->vistasAtributo[0]->getPuntoMedioLinea(x0, y0);
		cr->arc(x0, y0, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
		cr->fill();
		cr->move_to(x0, y0);

		for (i = (this->vistasAtributo.begin() + 1); i != this->vistasAtributo.end(); i++) {
			(*i)->getPuntoMedioLinea(x1, y1);
			cr->line_to(x1, y1);
			cr->stroke();
			cr->arc(x1, y1, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
			cr->fill();
			cr->move_to(x1, y1);
		}
		cr->stroke();
		if (!this->vistasEntidadesFuertes.empty()) {
			cr->move_to(x0, y0);
			for (j = this->vistasEntidadesFuertes.begin(); j != this->vistasEntidadesFuertes.end();
					j++) {
				(*j)->getPuntoMedioLinea(x1, y1);
				cr->line_to(x1, y1);
#if DEBUG_DIBUJAR==1
				cout << "X1=" << x1 << " Y1=" << y1 << endl;
#endif
				cr->stroke();
				cr->arc(x1, y1, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
				cr->fill();
				cr->move_to(x0, y0);
			}
			cr->stroke();
		}
	}

	/*if (this->vistaAtributos.empty()) {
	 double radio;
	 radio = 3;
	 centro_x = this->pos_ini_x + radio;
	 centro_y = this->pos_ini_y + radio;

	 this->pos_fin_x = centro_x + radio;
	 this->pos_fin_y = centro_y + radio;

	 //cr->move_to(centro_x, this->pos_ini_y);
	 cr->arc(centro_x, centro_y, radio, 0, 2 * M_PI);
	 // TODO if es parte de una clave candidata FILL
	 //cr->fill();
	 cr->stroke();
	 } else {
	 double delta_x, delta_y;
	 if (this->pos_fin_x < this->pos_ini_x || this->pos_fin_y < this->pos_ini_y) {
	 cr->get_text_extents(this->atributo->getNombre(), textExtents);
	 this->calcularDimensionesAPartirDeTexto(&textExtents);
	 }
	 // Dibujo una elipse
	 centro_x = (this->pos_ini_x + this->pos_fin_x) / 2;
	 centro_y = (this->pos_ini_y + this->pos_fin_y) / 2;
	 delta_x = centro_x - this->pos_ini_x;
	 delta_y = centro_y - this->pos_ini_y;

	 this->dibujarNombreCentrado(cr, this->atributo->getNombre());

	 cr->save();
	 cr->set_line_width(2 / MAX(delta_x, delta_y));// make (centro_x, centro_y) == (0, 0)
	 cr->translate(centro_x, centro_y);
	 cr->scale(delta_x, delta_y);
	 cr->arc(0.0, 0.0, 1.0, 0.0, 2 * M_PI);
	 cr->stroke();
	 cr->restore(); // back to opaque black
	 if (this->seleccionado) {
	 dibujarCirculosDeRedimension(cr);
	 }
	 }*/
}
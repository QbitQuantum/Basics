void Importer::doImport(bool load_symbols_only, const QString& map_path)
{
	import(load_symbols_only);
	
	// Object post processing:
	// - make sure that there is no object without symbol
	// - make sure that all area-only path objects are closed
	// - make sure that there are no special points in wrong places (e.g. curve starts inside curves)
	for (int p = 0; p < map->getNumParts(); ++p)
	{
		MapPart* part = map->getPart(p);
		for (int o = 0; o < part->getNumObjects(); ++o)
		{
			Object* object = part->getObject(o);
			if (object->getSymbol() == NULL)
			{
				addWarning(Importer::tr("Found an object without symbol."));
				if (object->getType() == Object::Point)
					object->setSymbol(map->getUndefinedPoint(), true);
				else if (object->getType() == Object::Path)
					object->setSymbol(map->getUndefinedLine(), true);
				else
				{
					// There is no undefined symbol for this type of object, delete the object
					part->deleteObject(o, false);
					--o;
					continue;
				}
			}
			
			if (object->getType() == Object::Path)
			{
				PathObject* path = object->asPath();
				Symbol::Type contained_types = path->getSymbol()->getContainedTypes();
				if (contained_types & Symbol::Area && !(contained_types & Symbol::Line))
					path->closeAllParts();
				
				for (MapCoordVector::size_type i = 0; i < path->getCoordinateCount(); ++i)
				{
					if (path->getCoordinate(i).isCurveStart())
					{
						if (i+3 >= path->getCoordinateCount())
						{
							path->getCoordinate(i).setCurveStart(false);
							continue;
						}
						
						if (path->getCoordinate(i + 1).isClosePoint() || path->getCoordinate(i + 1).isHolePoint() ||
						    path->getCoordinate(i + 2).isClosePoint() || path->getCoordinate(i + 2).isHolePoint())
						{
							path->getCoordinate(i).setCurveStart(false);
							continue;
						}
						
						path->getCoordinate(i + 1).setCurveStart(false);
						path->getCoordinate(i + 1).setDashPoint(false);
						path->getCoordinate(i + 2).setCurveStart(false);
						path->getCoordinate(i + 2).setDashPoint(false);
						i += 2;
					}
					
					if (i > 0 && path->getCoordinate(i).isHolePoint())
					{
						if (path->getCoordinate(i-1).isHolePoint())
							path->deleteCoordinate(i, false);
					}
				}
			}
		}
	}
	
	// Symbol post processing
	for (int i = 0; i < map->getNumSymbols(); ++i)
	{
		if (!map->getSymbol(i)->loadFinished(map))
			throw FileFormatException(Importer::tr("Error during symbol post-processing."));
	}
	
	// Template loading: try to find all template files
	bool have_lost_template = false;
	for (int i = 0; i < map->getNumTemplates(); ++i)
	{
		Template* temp = map->getTemplate(i);
		
		bool loaded_from_template_dir = false;
		temp->tryToFindAndReloadTemplateFile(map_path, &loaded_from_template_dir);
		if (loaded_from_template_dir)
			addWarning(Importer::tr("Template \"%1\" has been loaded from the map's directory instead of the relative location to the map file where it was previously.").arg(temp->getTemplateFilename()));
		
		if (temp->getTemplateState() != Template::Loaded)
			have_lost_template = true;
	}
	if (have_lost_template)
	{
#if defined(Q_OS_ANDROID)
		addWarning(tr("At least one template file could not be found."));
#else
		addWarning(tr("At least one template file could not be found.") + " " +
		           tr("Click the red template name(s) in the Templates -> Template setup window to locate the template file name(s)."));
#endif
	}
}
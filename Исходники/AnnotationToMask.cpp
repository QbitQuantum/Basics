void AnnotationToMask::convert(const std::shared_ptr<AnnotationList>& annotationList, const std::string& maskFile, const std::vector<unsigned long long>& dimensions, const std::vector<double>& spacing, const std::map<std::string, int> nameToLabel, const std::vector<std::string> nameOrder) const {
  bool hasGroups = !annotationList->getGroups().empty();
  std::vector<std::shared_ptr<Annotation> > annotations = annotationList->getAnnotations();
  for (auto annotation = annotations.begin(); annotation != annotations.end(); ++annotation) {
    if (!(*annotation)->isClockwise()) {
      std::vector<Point> coords = (*annotation)->getCoordinates();
      std::reverse(coords.begin(), coords.end());
      (*annotation)->setCoordinates(coords);
    }
  }
  if (!nameOrder.empty() && !nameToLabel.empty()) {
    std::vector<std::shared_ptr<Annotation> > unorderedAnnotations = annotations;
    annotations.clear();
    for (unsigned int i = 0; i < nameOrder.size(); ++i) {
      std::string currentName = nameOrder[i];
      for (std::vector<std::shared_ptr<Annotation> >::iterator it = unorderedAnnotations.begin(); it != unorderedAnnotations.end(); ++it) {
        bool matchesName = false;
        if (hasGroups) {
          if ((*it)->getGroup()) {
            if ((*it)->getGroup()->getName() == currentName) {
              matchesName = true;
            }
          }
        }
        else {
          if ((*it)->getName() == currentName) {
            matchesName = true;
          }
        }
        if (matchesName) {
          annotations.push_back((*it));
        }
      }
    }
  }
	MultiResolutionImageWriter writer;
  if (_monitor) {
    writer.setProgressMonitor(_monitor);
  }
	if (writer.openFile(maskFile) == 0) {
		writer.setColorType(pathology::Monochrome);
		writer.setCompression(pathology::LZW);
		writer.setTileSize(512);
		writer.setDataType(pathology::UChar);
		writer.setInterpolation(pathology::NearestNeighbor);
    std::vector<double> spacing_copy(spacing);
		writer.setSpacing(spacing_copy);
		writer.writeImageInformation(dimensions[0], dimensions[1]);
		unsigned char* buffer = new unsigned char[512 * 512];
		for (unsigned long long ty = 0; ty < dimensions[1]; ty += 512) {
			for (unsigned long long tx = 0; tx < dimensions[0]; tx += 512) {
				std::fill(buffer, buffer + 512 * 512, 0);
        for (std::vector<std::shared_ptr<Annotation> >::const_iterator annotation = annotations.begin(); annotation != annotations.end(); ++annotation) {
          if (!nameToLabel.empty() && !(*annotation)->getGroup() && hasGroups) {
            continue;
          }
          std::string nm = (*annotation)->getName();
          std::vector<Point> coords = (*annotation)->getCoordinates();
          std::vector<Point> bbox = (*annotation)->getImageBoundingBox();
          if (!coords.empty()) {
            coords.push_back(coords[0]);
          }
          int label = 1;
          if (!nameToLabel.empty()) {
            std::map<std::string, int>::const_iterator it;
            if (hasGroups) {
              it = nameToLabel.find((*annotation)->getGroup()->getName());
            }
            else {
              it = nameToLabel.find(nm);
            }
            if (it != nameToLabel.end()) {
              label = it->second;
            }
            else {
              label = 0;
            }
          }
          for (unsigned int y = 0; y < 512; ++y) {
            if (ty + y >= dimensions[1]) {
              break;
            }
            if (ty + y > bbox[0].getY() && ty + y < bbox[1].getY()) {
              for (unsigned int x = 0; x < 512; ++x) {
                if (tx + x > bbox[0].getX() && tx + x < bbox[1].getX()) {                  
                  if (tx + x >= dimensions[0]) {
                    break;
                  }
                  int in_poly = wn_PnPoly(Point(static_cast<float>(tx + x), static_cast<float>(ty + y)), coords) != 0 ? 1 : 0;
                  if (nameOrder.empty()) {
                    buffer[y * 512 + x] = in_poly * label > buffer[y * 512 + x] ? in_poly * label : buffer[y * 512 + x];
                  }
                  else if (in_poly) {
                    buffer[y * 512 + x] = in_poly * label;
                  }
                }
              }
            }
          }
        }
			  writer.writeBaseImagePart((void*)buffer);
			}
		}
		writer.finishImage();
		delete[] buffer;
	}
}
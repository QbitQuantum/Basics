void PathFinderOutput::Save(CFile &file) const
{
	file.printf("\"pathfinder-output\", {");

	if (this->Fast) {
		file.printf("\"fast\", ");
	}
	if (this->Length > 0) {
		file.printf("\"path\", {");
		for (int i = 0; i < this->Length; ++i) {
			file.printf("%d, ", this->Path[i]);
		}
		file.printf("},");
	}
	file.printf("\"cycles\", %d", this->Cycles);

	file.printf("},\n  ");
}
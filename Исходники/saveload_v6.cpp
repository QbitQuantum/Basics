bool SaveLoad_v6::GameHandler::save(int16 dataVar, int32 size, int32 offset) {
	uint32 varSize = SaveHandler::getVarSize(_vm);

	if (varSize == 0)
		return false;

	if (size == 0) {
		// Indicator to save all variables
		dataVar = 0;
		size = varSize;
	}

	if (((uint32) offset) < kPropsSize) {
		// Properties

		if (((uint32) (offset + size)) > kPropsSize) {
			warning("Wrong index size (%d, %d)", size, offset);
			return false;
		}

		_vm->_inter->_variables->copyTo(dataVar, _props + offset, size);

		refreshProps();

		// If that screen doesn't save any extra temp saves, write a dummy
		if (_writer && (size == 40) && (offset == 0)) {
			if (!_hasExtra) {
				SavePartMem  mem(1);
				SavePartVars vars(_vm, varSize);

				uint8 extraSaveNumber = 0;
				if (!mem.readFrom(&extraSaveNumber, 0, 1))
					return false;
				if (!vars.readFrom(0, 0, varSize))
					return false;

				if (!_writer->writePart(2, &mem))
					return false;
				if (!_writer->writePart(3, &vars))
					return false;
			}
		}

	}  else if (((uint32) offset) < kPropsSize + kIndexSize) {
		// Save index

		if (((uint32) size) != kIndexSize) {
			warning("Wrong index size (%d, %d)", size, offset);
			return false;
		}

		// Just copy the index into our buffer
		_vm->_inter->_variables->copyTo(dataVar, _index, kIndexSize);

	} else {
		// Save slot, whole variable block

		_hasExtra = false;

		uint32 slot = _slotFile->getSlot(offset);
		int slotRem = _slotFile->getSlotRemainder(offset);

		debugC(2, kDebugSaveLoad, "Saving to slot %d", slot);

		if ((slot >= kSlotCount) || (slotRem != 0) ||
		    (dataVar != 0) || (((uint32) size) != varSize)) {

			warning("Invalid saving procedure (%d, %d, %d, %d, %d)",
					dataVar, size, offset, slot, slotRem);
			return false;
		}

		if (!createWriter(slot))
			return false;

		SavePartInfo info(kSlotNameLength, (uint32) _vm->getGameType(), 0,
				_vm->getEndianness(), varSize);
		SavePartVars vars(_vm, varSize);

		// Write the description
		info.setDesc(_index + (slot * kSlotNameLength), kSlotNameLength);
		// Write all variables
		if (!vars.readFrom(0, 0, varSize))
			return false;

		if (!_writer->writePart(0, &info))
			return false;
		if (!_writer->writePart(1, &vars))
			return false;

		if (!_spriteHandler->get(_writer, 4))
			return false;
	}

	return true;
}
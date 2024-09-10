		Protein* PeptideBuilder::construct()
		{
			if (fragment_db_ == 0)
			{
				Log.warn() << "PeptideBuilder::construct(): no FragmengDB given!" << std::endl;
				return 0;
			}
			if (sequence_.empty())
			{

				Log.warn() << "PeptideBuilder::construct(): no amino acid sequence specified." << std::endl;
				return 0;
			}
			int id = 1;
			Protein *protein = new Protein(proteinname_);
			Chain *chain = new Chain(chainname_);

			// create the first residue
			Residue* residue = createResidue_(sequence_[0].getType(), id);
			chain->insert(*residue);
			Residue* residueold = residue;
			std::vector<AminoAcidDescriptor>::iterator i = sequence_.begin();
			++id;

			// consistency check for empty sequences and sequences of length < 2!!	
			// loop for the remaining residues ;
			for (++i; i != sequence_.end(); ++i)
			{
				// We have to take care of two special cases:
				// 		- the residue we are looking at is proline
				// 		- the last residue was proline
				String type = (i-1)->getType();
				type.toUpper();

				// special case: residue is a proline
				type = i->getType();
				type.toUpper();
				is_proline_ = (type == "PRO") ? true : false;

				Residue* residue2 = createResidue_(i->getType(), id);

				insert_(*residue2, *residueold);
				chain->insert(*residue2);

				// set the torsion angle 
				transform_(i->getPhi(), (i-1)->getPsi(),*residueold, *residue2);
				peptide_(*residueold,*residue2);

				// set the peptide bond angle omega
				setOmega_(*residueold, *residue2, i->getOmega());

				residueold=residue2;
				++id;
			}

			protein->insert(*chain);

			// read the names for a unique nomenclature 
			protein->apply(fragment_db_->normalize_names);

			// add missing bonds and atoms (including side chains!)
			ReconstructFragmentProcessor rfp(*fragment_db_);
			protein->apply(rfp);
			protein->apply(fragment_db_->build_bonds);

			return protein;
		}
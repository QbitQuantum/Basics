int main(int argc,char *argv[])
{
  // turn off slow sync with C-style output (we don't use it anyway).
  std::ios::sync_with_stdio(false);

  OBConversion conv;
  OBFormat *inFormat, *canFormat;
  OBMol mol;
  ifstream ifs;
  vector<OBMol> fragments;
  unsigned int fragmentCount = 0; // track how many in library -- give a running count
  map<string, int> index; // index of cansmi
  string currentCAN;
  unsigned int size;
  OBAtom *atom;
  OBBond *bond;
  bool nonRingAtoms, nonRingBonds;
  char buffer[BUFF_SIZE];

  canFormat = conv.FindFormat("can");
  conv.SetOutFormat(canFormat);

  if (argc < 2)
    {
      cout << "Usage: obfragment <file>" << endl;
      return(-1);
    }

  for (int i = 1; i < argc; i++) {
    cerr << " Reading file " << argv[i] << endl;

    inFormat = conv.FormatFromExt(argv[i]);
    if(inFormat==NULL || !conv.SetInFormat(inFormat))
      {
        cerr << " Cannot read file format for " << argv[i] << endl;
        continue; // try next file
      }
    
    ifs.open(argv[i]);
    
    if (!ifs)
      {
        cerr << "Cannot read input file: " << argv[i] << endl;
        continue;
      }
    
    
    while(ifs.peek() != EOF && ifs.good())
      {
        conv.Read(&mol, &ifs);
        if (!mol.Has3D()) continue; // invalid coordinates!
        mol.DeleteHydrogens(); // remove these before we do anything else
        
        do {
          nonRingAtoms = false;
          size = mol.NumAtoms();
          for (unsigned int i = 1; i <= size; ++i)
            {
              atom = mol.GetAtom(i);
              if (!atom->IsInRing()) {
                mol.DeleteAtom(atom);
                nonRingAtoms = true;
                break; // don't know how many atoms there are
              } 
              // Previously, we changed atoms to carbon here.
              // Now we perform this alchemy in terms of string-rewriting
              // once the canonical SMILES is generated
            }
        } while (nonRingAtoms);
        
        if (mol.NumAtoms() < 3)
          continue;
        
        if (mol.NumBonds() == 0)
          continue;
        
        do {
          nonRingBonds = false;
          size = mol.NumBonds();
          for (unsigned int i = 0; i < size; ++i)
            {
              bond = mol.GetBond(i);
              if (!bond->IsInRing()) {
                mol.DeleteBond(bond);
                nonRingBonds = true;
                break; // don't know how many bonds there are
              }
            }        
        } while (nonRingBonds);

        fragments = mol.Separate();
        for (unsigned int i = 0; i < fragments.size(); ++i)
          {
            if (fragments[i].NumAtoms() < 3) // too small to care
              continue;
              
            currentCAN = conv.WriteString(&fragments[i], true);
            currentCAN = RewriteSMILES(currentCAN); // change elements to "a/A" for compression
            if (index.find(currentCAN) != index.end()) { // already got this
              index[currentCAN] += 1; // add to the count for bookkeeping
              continue;
            }

            index[currentCAN] = 1; // don't ever write this ring fragment again

            // OK, now retrieve the canonical ordering for the fragment
            vector<string> canonical_order;
            if (fragments[i].HasData("Canonical Atom Order")) {
              OBPairData *data = (OBPairData*)fragments[i].GetData("Canonical Atom Order");
              tokenize(canonical_order, data->GetValue().c_str());
            }

            // Write out an XYZ-style file with the CANSMI as the title
            cout << fragments[i].NumAtoms() << '\n';
            cout << currentCAN << '\n'; // endl causes a flush

            vector<string>::iterator can_iter;
            unsigned int order;
            OBAtom *atom;

            fragments[i].Center();
            fragments[i].ToInertialFrame();

            for (unsigned int index = 0; index < canonical_order.size(); 
                 ++index) {
              order = atoi(canonical_order[index].c_str());
              atom = fragments[i].GetAtom(order);
              
              snprintf(buffer, BUFF_SIZE, "C%8.3f%8.3f%8.3f\n",
                       atom->x(), atom->y(), atom->z());
              cout << buffer;
            }

          }
        fragments.clear();
        if (index.size() > fragmentCount) {
          fragmentCount = index.size();
          cerr << " Fragments: " << fragmentCount << endl;
        }

      } // while reading molecules (in this file)
    ifs.close();
    ifs.clear();
  } // while reading files

  // loop through the map and output frequencies
  map<string, int>::const_iterator indexItr;
  for (indexItr = index.begin(); indexItr != index.end(); ++indexItr) {
    cerr << (*indexItr).second << " INDEX " << (*indexItr).first << "\n";
  }
    
  return(0);
}
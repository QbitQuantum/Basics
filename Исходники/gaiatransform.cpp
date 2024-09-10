/**
 * Copy all the values from the point inside the pool.
 */
void pointToPool(const gaia2::Point* p, Pool& pool, const Pool& origPool) {
  const gaia2::PointLayout& layout = p->layout();
  vector<string> alldescsv = pool.descriptorNames();
  set<string> alldescs(alldescsv.begin(), alldescsv.end());

  foreach (const QString& d, layout.descriptorNames(gaia2::RealType)) {
    string pooldesc = d.mid(1).toStdString();
    checkNotIn(pooldesc, alldescs);

    gaia2::RealDescriptor desc = p->value(d);

    if (desc.size() == 1)    pool.set(pooldesc, desc[0]);
    else if (desc.isEmpty()) pool.set(pooldesc, vector<Real>());
    else                     pool.set(pooldesc, vector<Real>(&desc[0],
                                                             &desc[0]+desc.size()));

    // in fact, if desc.size == 1 and we're not in the single pool, we'd better
    // put back the value as a list of size 1
    const std::map<std::string, Real>& srpool = origPool.getSingleRealPool();

    if ((desc.size() == 1) && (srpool.find(pooldesc) == srpool.end())) {
      pool.remove(pooldesc);
      for (int i=0; i<desc.size(); i++) pool.add(pooldesc, desc[i]);
    }

    // if desc was a vector<vector<Real> >, it will have been converted to a single
    // vector<Real>, where the first 2 values are the dimensions. Construct this matrix back.
    const PoolOf(std::vector<Real>)& vrpool = origPool.getVectorRealPool();

    if (vrpool.find(pooldesc) != vrpool.end()) {
      int rows = int(desc[0]);
      int cols = int(desc[1]);

      // assert we're not doing something potentially stupid
      if ((rows*cols + 2) != desc.size()) {
        E_WARNING("Oops, internal error in GaiaTransform::pointToPool, ignoring...");
        continue;
      }
      pool.remove(pooldesc);

      for (int i=0; i<rows; i++) {
        pool.add(pooldesc, vector<Real>(&desc[2+ i*cols],
                                        &desc[2+ i*cols] + cols));
      }
    }
  }

  // for string descs, we need to be looking at both the string and enum types in the layout
  QStringList stringDescs = layout.descriptorNames(gaia2::StringType) +
                            layout.descriptorNames(gaia2::EnumType);

  foreach (const QString& d, stringDescs) {
    string pooldesc = d.mid(1).toStdString();
    checkNotIn(pooldesc, alldescs);

    gaia2::StringDescriptor desc = p->label(d);

    // little check: see if we haven't removed the version before
    if (pooldesc == "metadata.version.essentia") {
      pool.set(pooldesc, essentia::version);
      continue;
    }

    if (desc.size() == 1) pool.set(pooldesc, desc[0].toStdString());
    else {
      for (int i=0; i<desc.size(); i++) {
        pool.add(pooldesc, desc[i].toStdString());
      }
    }
  }
int main(int argc, char *argv[]){
  // 物理定数を定義（Fe）
  material_t material = setup_material(0.4174, 1.3885, 2.845);
  // 座標長さ1における実際の長さ（格子定数）
  float length = 2.9098453;
  // float length = 2 * material.r0 / sqrt(3);
  // 座標ファイルの読み込み
  FILE *rfp = read_file();

  // ファイル一行目から総原子数を求め、atoms配列を定義
  long atoms_number;
  fscanf(rfp, "%ld", &atoms_number);
  atom_t atoms[atoms_number];

  // atomsに座標を代入（bcc_structure.h参照）
  input_structure(rfp, atoms, atoms_number);

  fclose(rfp);

  // 総原子数から構造の大きさを求める（原子間距離を原子半径の2倍と仮定）
  int structure_length = cbrt(atoms_number / 2.0);
  // float structure_size = structure_length * material.r0 * 2.0;

  // // 結合エネルギが有効数字内で変化しなくなる距離を計算し、一辺を何回ループするか決定（すべての原子が同じ物理定数を持つと仮定）
  // int loop_number = eval_loop_number(material, structure_size);

  // // 拡張したatomsを作成
  // long extended_atoms_number = atoms_number * pow(loop_number, 3);
  // atom_t extended_atoms[extended_atoms_number];

  // // 拡張したatomsに座標を定義
  // initialize_extended_structure(extended_atoms, atoms, atoms_number, structure_length, loop_number);

  // // エネルギーを計算
  // eval_energy(atoms, atoms_number, extended_atoms, extended_atoms_number, material);
  eval_energy_ex(atoms, atoms_number, material, structure_length, length);

  // 出力
  FILE *wfp = write_file();
  output_structure(wfp, atoms, atoms_number);
  fclose(wfp);

  return 0;
}
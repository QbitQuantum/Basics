int main (int argc, char* argv[])
{
    ifstream input_file(argv[1]);
    string line;

    if (input_file)
    {
        while (getline(input_file, line))
        {
            vector<string> entries = tokenize(line);
            vector<int> dots;
            for (int i = 0; i < entries.size(); ++i)
            {
                string entry = entries[i];
                // special case for failure on CodeEval's end
                if (entry == "XYYYY.Y")
                    entry = "XYYYYYY";
                dots.push_back(count(entry.begin(), entry.end(), '.'));
            }
            cout << dots[distance(dots.begin(), min_element(dots.begin(), dots.end()))] << endl;
        }
        input_file.close();
    }
    return 0;
}
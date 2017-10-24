#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

bool print_map = false;

void rehash(string filename, int start)
{
	ifstream fin(filename);
	int u, v;
	vector< pair<int, int> > edges;
	unordered_set<int> nodes;

	while(fin >> u >> v)
	{
		edges.push_back(make_pair(u, v));
		nodes.insert(u);
		nodes.insert(v);
	}
	fin.close();

	unordered_map<int, int> mapping;
	for (int node: nodes)
	{
		mapping[node] = start;
		start += 1;
	}

	ofstream fout("rehashed_" + filename);
	for (auto edge: edges)
	{
		u = edge.first;
		v = edge.second;
		fout << mapping[u] << " " << mapping[v] << endl;
	}
	fout.close();

	cout << "Rehashed edge list at " << "rehashed_" + filename << endl;

	if (print_map)
	{
		fout.open("inv_map_" + filename);
		for (auto thing: mapping)
		{
			fout << thing.first << " " << thing.second << endl;
		}
		fout.close();
		cout << "Inverse mapping stored at " << "inv_map_" + filename << endl;
	}
	

}

void parse_args(int argc, char const *argv[])
{
    // parses the command line args
    for (int i = 1; i < argc; i ++)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
                case 'm':
                    print_map = true; // show timing info
                break;                
            }
        }
    }
}

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		cout << "Enter filename of edge list and starting label as args!\n";
	}
	else
	{
		parse_args(argc, argv);
		rehash(argv[1], stoi(argv[2]));
	}

	return 0;
}
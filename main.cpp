#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

struct State;

struct Line
{
	string in;
	string out;
	string nextState;

	bool operator==(Line B)
	{
		if (B.in == in && B.nextState == nextState && B.out == out)
			return true;
		else
			return false;
	}
};

struct State
{
	vector<Line> lines;
};

bool SameState(map<string, State>::iterator A, map<string, State>::iterator B)
{
	if (A->first == B->first)return false;
	for (int i = 0; i < A->second.lines.size(); i++)
	{
		bool flag = false;
		for (int j = 0; j < B->second.lines.size(); j++)
		{
			if (A->second.lines[i] == B->second.lines[j])
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
			return flag;
	}
	return true;
}

void MergeState(map<string, State>& states, string &startState)
{
	for (auto i = states.begin(); i != states.end(); i++)
	{
		for (auto j = i;; )
		{
			j++;
			if (j == states.end())break;
			if (SameState(i, j))
			{
				for (auto k = states.begin(); k != states.end(); k++)
				{
					for (int l = 0; l < k->second.lines.size(); l++)
					{
						if (k->second.lines[l].nextState == j->first)
							k->second.lines[l].nextState = i->first;
						if (startState == j->first)
							startState = i->first;
					}
				}
				states.erase(j);
				MergeState(states, startState);
				return;
			}
		}
	}
}


void Minimize(ifstream &fin)
{
	map<string, State> states;
	int n_input, n_output, n_line = 0, n_state;
	string startState;
	string str;
	while (!fin.eof())
	{
		fin >> str;
		if (str == ".start_kiss")continue;
		else if (str == ".i")
			fin >> n_input;
		else if (str == ".o")
			fin >> n_output;
		else if (str == ".p")
			fin >> n_line;
		else if (str == ".s")
			fin >> n_state;
		else if (str == ".r")
		{
			fin >> startState;
			for (int i = 0; i < n_line; i++)
			{
				string me;
				Line temp;
				fin >> temp.in >> me >> temp.nextState >> temp.out;
				states[me].lines.push_back(temp);
			}
		}
		else if (str == ".end_kiss")
		{
			MergeState(states, startState);
			//Output kiss
			ofstream fout("output.kiss", ofstream::out);
			fout << ".start_kiss" << endl;
			fout << ".i " << n_input << endl;
			fout << ".o " << n_output << endl;
			fout << ".p " << pow(2, n_input)*states.size() << endl;
			fout << ".s " << states.size() << endl;
			fout << ".r " << startState << endl;
			for (auto i = states.begin(); i != states.end(); i++)
			{
				for (int j = 0; j < i->second.lines.size(); j++)
				{
					Line l = i->second.lines[j];
					fout << l.in << " " << i->first << " " << l.nextState << " " << l.out << endl;
				}
			}
			fout << ".end_kiss";
			fout.close();
			//Output dot
			ofstream fout2("output.dot", ofstream::out);
			fout2 << "digraph STG {" << endl;
			fout2 << "\trankdir=LR;" << endl << endl;
			fout2 << "\tINIT [shape=point];" << endl;
			for (auto i = states.begin(); i != states.end(); i++)
			{
				fout2 << "\t" << i->first << " [label=\"" << i->first << "\"];" << endl;
			}
			fout2 << endl;
			fout2 << "\tINIT -> " << startState << ";" << endl;
			for (auto i = states.begin(); i != states.end(); i++)
			{
				for (int j = 0; j < i->second.lines.size(); j++)
				{
					fout2 << "\t" << i->first << " -> " << i->second.lines[j].nextState << " [label=\"" << i->second.lines[j].in << "/" << i->second.lines[j].out;
					for (int k = j;;)
					{
						k++;
						if (k >= i->second.lines.size())break;
						if (i->second.lines[j].nextState == i->second.lines[k].nextState)
						{
							fout2 << "," << i->second.lines[k].in << "/" << i->second.lines[k].out;
							i->second.lines.erase(i->second.lines.begin() + k);
							k--;
						}
					}
					fout2 << "\"];" << endl;
				}
			}
			fout2 << "}" << endl;
			fout2.close();
			break;
		}
		else
			break;
	}
}

int main(int argc, char *argv[])
{
	//Need input and output files.
	if (argc != 2)
	{
		cout << "parameter error!" << endl;
		return -1;
	}
	else
	{
		ifstream fin(argv[1]);
		//Can not open.
		if (!fin)
		{
			cout << "file error!" << endl;
			return -1;
		}
		else
		{
			Minimize(fin);
		}
	}
	return 0;
}

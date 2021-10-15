#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>

#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

struct  Edge;

struct Vertex {
	int index;
	vector<Edge*> edges;
	bool isNew = true;
};
struct Edge{
	int id;
	double weight;
	Vertex* first;
	Vertex* second;
};
struct Graph{
	vector<Vertex> vertexs;
	vector<Edge> edgs;
	set<int> disgoal_vertexs;
	set<int> all_vertexs;

	void LoadFromFile(ifstream& in){
		int n,m;
		string buf;
		getline(in, buf);
		stringstream sstr(buf);
		sstr >> n >> m;
		for(int i(0); i < n; i++)
		{
			Vertex v;
			v.index = i;
			vertexs.push_back(v);
			all_vertexs.insert(v.index);
		}
		for(int i(0); i < m; i++)
		{
			Edge ed;
			ed.id = i;
			edgs.push_back(ed);
		}

		int f_ind, s_ind, edge_counter(0);
		while(getline(in,buf))
		{
			stringstream str(buf);
			str >> f_ind;

			while(!str.eof())
			{
				string str_edge;
				str >> str_edge;
				int sep = str_edge.find(';', 0);
				if(sep == string::npos)
					break;
				str_edge[sep] = ' ';
				stringstream sstr_edge(str_edge);
				sstr_edge >> s_ind;
				double edge_weight;
				sstr_edge >> edge_weight;
				edgs[edge_counter].weight = edge_weight;
				edgs[edge_counter].first = &vertexs[f_ind];
				edgs[edge_counter].second = &vertexs[s_ind];
				vertexs[f_ind].edges.push_back(&edgs[edge_counter]);
				edge_counter++;
			}
		}
	}

	void BFS(Vertex* s)
	{
		bool flag = false;
		set<int> goal_vertexs;
		queue<Vertex*> q;
		q.push(s);
		while(!q.empty())
		{
			Vertex* u = q.front();
			q.pop();
			cout << u->index << " ";
			u->isNew = false;
			goal_vertexs.insert(u->index);
			for(int i(0); i < u->edges.size(); i++)
			{
				if(u->edges[i]->second->isNew){
					q.push(u->edges[i]->second);
					u->edges[i]->second->isNew = false;
				}
			}
		}

		// Проверка достижимости вершины, из которой стартует алгоритм

		for(const auto& ed : edgs)
		{
			if(ed.second->index == s->index)
				flag = true;
        }

		//
		cout << endl;
		if(!flag)
		 {
			goal_vertexs.erase(s->index);

		 }
		set_difference(all_vertexs.begin(), all_vertexs.end(), goal_vertexs.begin(), goal_vertexs.end(),
		 inserter(disgoal_vertexs, disgoal_vertexs.begin()));

	}

	void SavetoDOT(ostream& out)
	{
		out << "digraph Gr1{"<<endl;
		for(const auto& v : vertexs)
		{
			out << v.index << ";" << endl;
		}
		for(const auto& ed : edgs)
		{
			out << ed.first->index << " -> " << ed.second->index << "[label=" << ed.weight << "];"<<endl;
		}
		out << "}";
	}
};

 int _tmain(int argc, _TCHAR* argv[])
{
	system("chcp 1251");
	ifstream in("graf781.txt");
	if(!in.is_open())
	{
		return 1;
	}
	Graph graph;
	graph.LoadFromFile(in);
	cout << "Количество достижимых вершин: " << graph.all_vertexs.size()<<endl;
	graph.BFS(&graph.vertexs[0]);

	cout << "---------------------------------------------------------------------" << endl;
	cout << "Количество недостижимых вершин: " << graph.disgoal_vertexs.size()<<endl;
	for(auto x: graph.disgoal_vertexs)
	{
		cout << x << endl;
	}
	ofstream out("graph.gv");
	if(!out.is_open())
		return 0;
	graph.SavetoDOT(out);

	system("c:\\\"Program Files\"\\Graphviz2.38\\bin\\dot.exe -Tpng -ograph.png graph.gv");
	system("graph.png");

	in.close();
	out.close();
	system("pause");
	return 0;
}

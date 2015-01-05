#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <tr1/unordered_map>

#define MAX 3000
#define NUM_PRODUCTS 5

using namespace std;

typedef long long LL;

vector<int> adj[MAX];
vector<LL> likes[MAX][NUM_PRODUCTS];

tr1::unordered_map<LL, int> mapping;
tr1::unordered_map<LL, int> pageToClass;
tr1::unordered_map<string, int> clas;
tr1::unordered_map<int, LL> backmapping;
tr1::unordered_map<int, string> backclass;

int main()
{
	int curuser = 0;
	int curclass = 0;
	ifstream fusers("adjlist_final.txt");
	ifstream fclass("classified_likes.txt");
	ifstream flikes("userlikes.txt");
	ofstream fout("jaccard_values.txt");
	cout << "Starting.\n";
	while(!fusers.eof())
	{
		LL userid;
		fusers >> userid;
		if (fusers.eof())
			break;
		int id;
		if (mapping.find(userid) == mapping.end())
		{
			cout << userid << "\n";
			mapping[userid] = curuser++;
			backmapping[curuser-1] = userid;
		}
		id = mapping[userid];
		int adjcount;
		fusers >> adjcount;
		for (int i = 0; i < adjcount; i++)
		{
			LL temp;
			fusers >> temp;
			int adjid;
			if (mapping.find(temp) == mapping.end())
			{
				mapping[temp] = curuser++;
				backmapping[curuser-1] = temp;
			}
			adjid = mapping[temp];
			adj[id].push_back(adjid);
		}
	}
	fusers.close();
	cout << "Done reading users..\n";

	while(!fclass.eof())
	{
		LL pageid;
		fclass >> pageid;
		if (fclass.eof())
			break;
		string c;
		fclass >> c;
		if (clas.find(c) == clas.end())
		{
			clas[c] = curclass++;
			backclass[curclass-1] = c;
		}
		int prodno = clas[c];
		pageToClass[pageid] = prodno;
	}
	fclass.close();
	cout << "Done reading like classes.\n";

	while(!flikes.eof())
	{
		LL userid;
		flikes >> userid;
		if (flikes.eof())
			break;
		if (mapping.find(userid) == mapping.end() )
		{
			cerr << "User " << userid << " not found in likes.\n";
			exit(1);
		}
		int id = mapping[userid];
		int count;
		flikes >> count;
		for (int i = 0; i < count; i++)
		{
			LL temp;
			flikes >> temp;
			if (pageToClass.find(temp) == pageToClass.end())
				continue;
			likes[id][pageToClass[temp]].push_back(temp);
		}
	}
	flikes.close();
	cout << "Done reading likes.\n";

	// Calculate Jaccard
	for (int i = 0; i < curuser; i++)
		for (int j = 0; j < NUM_PRODUCTS; j++)
			sort(likes[i][j].begin(), likes[i][j].end());

	cout << "Done sorting likes.\n";

	vector<LL> store(4000);
	vector<LL>::iterator last;
	for (int i = 0; i < curuser; i++)
		for (int j = 0; j < adj[i].size(); j++)
		{
			int user2 = adj[i][j];
			for (int k = 0; k < NUM_PRODUCTS; k++)
			{
				last = set_intersection(likes[i][k].begin(), likes[i][k].end(), likes[user2][k].begin(), likes[user2][k].end(), store.begin());
				int intersection = (int) (last - store.begin());
				int u = 1 + (int) (likes[i][k].size() + likes[user2][k].size()) - intersection;
				double jac = sqrt(intersection) / sqrt(u);
				fout << fixed << backmapping[i] << " " << backmapping[user2] << " " << backclass[k] << " " << jac << "\n";
			}
		}
	fout.close();

	return 0;		
}

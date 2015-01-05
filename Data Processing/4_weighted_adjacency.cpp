#include <iostream>
#include <fstream>
#include <vector>
#include <tr1/unordered_map>

#define MAX 3000
#define NUM_PRODUCTS 2

using namespace std;

typedef long long LL;

double jaccardvalue[MAX][MAX][5];

tr1::unordered_map<LL, int> mapping;
tr1::unordered_map<string, int> prodmap;
tr1::unordered_map<int, string> prodbackmap;

int main()
{
	ifstream jacval("jaccard_values.txt");
	ifstream fusers("adjlist_final.txt");
	ofstream fout("adjlist_weighted.txt");
	int curuser = 0;
	int curprod = 0;
	int doneedges = 0;
	while(!jacval.eof())
	{
		LL userid1, userid2;
		double jac;
		string prod;
		jacval >> userid1;
		if (jacval.eof())
			break;
		jacval >> userid2;
		int id1, id2;
		if (mapping.find(userid1) == mapping.end())
			mapping[userid1] = curuser++;
		if (mapping.find(userid2) == mapping.end())
			mapping[userid2] = curuser++;
		id1 = mapping[userid1];
		id2 = mapping[userid2];
		jacval >> prod;
		if (prodmap.find(prod) == prodmap.end())
		{
			prodmap[prod] = curprod++;
			prodbackmap[curprod-1] = prod;
		}
		int prodno = prodmap[prod];
		jacval >> jac;
		jaccardvalue[id1][id2][prodno] = jaccardvalue[id2][id1][prodno] = jac;
	}
	jacval.close();
	
	int doneusers = 0;
	while(!fusers.eof())
	{
		LL userid;
		fusers >> userid;
		int count;
		if (mapping.find(userid) == mapping.end())
		{
			cerr << "User " << userid << " missing.\n";
			cerr << "Fatal error. User not found.\n";
			return 1;
		}
		int curid = mapping[userid];
		fusers >> count;
		fout << userid << " ";
		fout << count;
		for (int i = 0; i < count; i++)
		{
			LL temp;
			fusers >> temp;
			if (mapping.find(temp) == mapping.end())
			{
				cerr << "User " << temp << " missing.\n";
				cerr << "Fatal error. User not found.\n";
				return 1;
			}
			int adjid = mapping[temp];
			for(int k = 0; k < NUM_PRODUCTS; k++)
				fout << fixed << " " << temp << " " << prodbackmap[k] << " " << jaccardvalue[curid][adjid][k];
		}
		fout << "\n";
		cout << "Done " << doneusers++ << " users.\n";
	}
	fusers.close();
	fout.close();

	return 0;
}

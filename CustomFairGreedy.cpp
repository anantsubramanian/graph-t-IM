#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <stack>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <string>
#include <tr1/unordered_map>
#include <sys/time.h>
#include <set>
#include <omp.h>

using namespace std;

#define MAX 2000
#define traverse(container, it) \
	for (typeof(container.begin()) it  = container.begin(); it != container.end(); ++it)
#define LIMIT 10000
#define NUM_PRODUCTS 2
#define EPS 1e-9

int ITERATIONS;

typedef pair<int, double> edge;
typedef long long LL;

tr1::unordered_map<string, int> prodidmap;
string prodmap[NUM_PRODUCTS];

vector<edge> adj1[NUM_PRODUCTS][MAX];
vector<edge> adj2[NUM_PRODUCTS][MAX];
vector<edge> adj3[NUM_PRODUCTS][MAX];
vector<edge> adj4[NUM_PRODUCTS][MAX];
int spamlimit[MAX];
int chosenfor[MAX];
int requiredseeds[NUM_PRODUCTS];

int oracle(vector<int> &seeds, int prod)
{
	int affected = 0;
	bool completed[MAX];
	stack<int> s;
	memset(completed, false, sizeof(completed));
	for (int i = 0; i < seeds.size(); i++)
	{
		//cout << "Seed = " << namemap[backmapping[seeds[i]]] << "\n";
		s.push(seeds[i]);
		completed[seeds[i]] = true;
	}
	affected += seeds.size();
	while(!s.empty())
	{
		int curnode = s.top();
		s.pop();
		int cantrigger = 0;
		traverse(adj1[prod][curnode], it)
		{
			cantrigger++;
			int neighbour = it->first;
			if (completed[neighbour])
				continue;
			double prob = it->second;
			double gen = ((double) (1 + rand()%LIMIT)) / LIMIT;
			if (gen <= prob)
			{
				//cout << namemap[backmapping[curnode]] << " -> " << namemap[backmapping[neighbour]] << " with probability = " << prob << " and genval = " << gen << "\n";
				completed[neighbour] = true;
				affected++;
				s.push(neighbour);
			}
		}
		//cout << "Can trigger = " << cantrigger << "\n";
	}
	return affected;
}

int oracle2(vector<int> &seeds, int prod)
{
	int affected = 0;
	bool completed[MAX];
	stack<int> s;
	memset(completed, false, sizeof(completed));
	for (int i = 0; i < seeds.size(); i++)
	{
		//cout << "Seed = " << namemap[backmapping[seeds[i]]] << "\n";
		s.push(seeds[i]);
		completed[seeds[i]] = true;
	}
	affected += seeds.size();
	while(!s.empty())
	{
		int curnode = s.top();
		s.pop();
		int cantrigger = 0;
		traverse(adj2[prod][curnode], it)
		{
			cantrigger++;
			int neighbour = it->first;
			if (completed[neighbour])
				continue;
			double prob = it->second;
			double gen = ((double) (1 + rand()%LIMIT)) / LIMIT;
			if (gen <= prob)
			{
				//cout << namemap[backmapping[curnode]] << " -> " << namemap[backmapping[neighbour]] << " with probability = " << prob << " and genval = " << gen << "\n";
				completed[neighbour] = true;
				affected++;
				s.push(neighbour);
			}
		}
		//cout << "Can trigger = " << cantrigger << "\n";
	}
	return affected;
}

int oracle3(vector<int> &seeds, int prod)
{
	int affected = 0;
	bool completed[MAX];
	stack<int> s;
	memset(completed, false, sizeof(completed));
	for (int i = 0; i < seeds.size(); i++)
	{
		//cout << "Seed = " << namemap[backmapping[seeds[i]]] << "\n";
		s.push(seeds[i]);
		completed[seeds[i]] = true;
	}
	affected += seeds.size();
	while(!s.empty())
	{
		int curnode = s.top();
		s.pop();
		int cantrigger = 0;
		traverse(adj3[prod][curnode], it)
		{
			cantrigger++;
			int neighbour = it->first;
			if (completed[neighbour])
				continue;
			double prob = it->second;
			double gen = ((double) (1 + rand()%LIMIT)) / LIMIT;
			if (gen <= prob)
			{
				//cout << namemap[backmapping[curnode]] << " -> " << namemap[backmapping[neighbour]] << " with probability = " << prob << " and genval = " << gen << "\n";
				completed[neighbour] = true;
				affected++;
				s.push(neighbour);
			}
		}
		//cout << "Can trigger = " << cantrigger << "\n";
	}
	return affected;
}

int oracle4(vector<int> &seeds, int prod)
{
	int affected = 0;
	bool completed[MAX];
	stack<int> s;
	memset(completed, false, sizeof(completed));
	for (int i = 0; i < seeds.size(); i++)
	{
		//cout << "Seed = " << namemap[backmapping[seeds[i]]] << "\n";
		s.push(seeds[i]);
		completed[seeds[i]] = true;
	}
	affected += seeds.size();
	while(!s.empty())
	{
		int curnode = s.top();
		s.pop();
		int cantrigger = 0;
		traverse(adj4[prod][curnode], it)
		{
			cantrigger++;
			int neighbour = it->first;
			if (completed[neighbour])
				continue;
			double prob = it->second;
			double gen = ((double) (1 + rand()%LIMIT)) / LIMIT;
			if (gen <= prob)
			{
				//cout << namemap[backmapping[curnode]] << " -> " << namemap[backmapping[neighbour]] << " with probability = " << prob << " and genval = " << gen << "\n";
				completed[neighbour] = true;
				affected++;
				s.push(neighbour);
			}
		}
		//cout << "Can trigger = " << cantrigger << "\n";
	}
	return affected;
}

double influence(vector<int> &seeds, int prod)
{
	//int sum = 0;
	int sums[4] = {0, 0, 0, 0};
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			vector<int> seeds1 = seeds;
			int prod1 = prod;
			for (int i = 0; i < ITERATIONS / 4; i++)
				sums[0] += oracle(seeds1, prod1);
		}
		#pragma omp section
		{
			vector<int> seeds1 = seeds;
			int prod1 = prod;
			for (int i = 0; i < ITERATIONS / 4; i++)
				sums[1] += oracle2(seeds1, prod1);
		}
		#pragma omp section
		{
			vector<int> seeds1 = seeds;
			int prod1 = prod;
			for (int i = 0; i < ITERATIONS / 4; i++)
				sums[2] += oracle3(seeds1, prod1);
		}
		#pragma omp section
		{
			vector<int> seeds1 = seeds;
			int prod1 = prod;
			for (int i = 0; i < ITERATIONS / 4; i++)
				sums[3] += oracle4(seeds1, prod1);
		}
	}
	return ((double) sums[0] + sums[1] + sums[2] + sums[3]) / ITERATIONS;
}

inline double influence(int node, vector<int> seeds, int prod)
{
	seeds.push_back(node);
	return influence(seeds, prod);
}

vector<int> *fairGreedy(int numusers, vector<int> products, vector<int> *seeds)
{
	memset(chosenfor, 0, sizeof(chosenfor));
	set<int> remaining = set<int>(products.begin(), products.end());
	int seedsleft = 0;
	for (int i = 0; i < products.size(); i++)
		seedsleft += requiredseeds[products[i]];
	set<int> users;
	seeds = new vector<int>[NUM_PRODUCTS];
	for(int i = 0; i < numusers; i++)
		users.insert(i);
	while(!users.empty() && !remaining.empty())
	{
		//seedsleft--;
		//cout << "Seeds left to be computed = " << seedsleft << "\n";
		//traverse(remaining, it)
			//cout << *it << " ";
		//cout << "\n";
		double minim = influence(seeds[*remaining.begin()], *remaining.begin());
		int minprod = *remaining.begin();
		traverse(remaining, it)
		{
			int curprod = *it;
			if (curprod == minprod) continue;
			double result = influence(seeds[curprod], curprod);
			if (result < minim)
			{
				minim = result;
				minprod = curprod;
			}
		}
		
		//cout << "Minimum product = " << prodmap[minprod] << "\n";
		//cout << "Min influence = " << fixed << minim << "\n";

		double maxinfluence = 0;
		int bestuser;
		traverse(users, it)
		{
			if (find(seeds[minprod].begin(), seeds[minprod].end(), *it) == seeds[minprod].end())
			{
				bestuser = *it;
				break;
			}
		}
	
		traverse(users, it)
		{
			int curuser = *it;
			if (adj1[minprod][curuser].size() == 0)
				continue;
			if (find(seeds[minprod].begin(), seeds[minprod].end(), curuser) != seeds[minprod].end())
				continue;
			double result = influence(curuser, seeds[minprod], minprod);
			if (result >= maxinfluence)
			{
				maxinfluence = result;
				bestuser = curuser;
			}
		}
		//cout << "Best user = " << bestuser << "\n";
		//cout << "Max influence = " << maxinfluence << "\n";
		
		//cout << "All users done.\n";
		seeds[minprod].push_back(bestuser);
		chosenfor[bestuser]++;
		if (chosenfor[bestuser] >= spamlimit[bestuser])
			users.erase(bestuser);
		if (seeds[minprod].size() >= requiredseeds[minprod])
			remaining.erase(minprod);
	}
	return seeds;
}

int main(int argc, char *argv[])
{
	int curuser = 0;
	int curprod = 0;
	if (argc <= 2)
	{
		cerr << "Please give no. of iterations for oracle and Adjacency List file..\n";
		exit(1);
	}
	ITERATIONS = atoi(argv[1]);
	timeval t;
	gettimeofday(&t, NULL);
	srand(t.tv_usec);
	ifstream fprod("InputParams.txt");
	ifstream fadjlist(argv[2]);

	while(!fprod.eof())
	{
		string name;
		int id;
		int reqseeds;
		fprod >> name;
		if (fprod.eof())
			break;
		fprod >> id;
		fprod >> reqseeds;
		prodidmap[name] = id;
		requiredseeds[id] = reqseeds;
		prodmap[id] = name;
	}
	fprod.close();
	
	//cout << 1 << "\n";

	while(!fadjlist.eof())
	{
		int id;
		curuser++;
		int count;
		fadjlist >> id;
		if (fadjlist.eof())
			break;
		fadjlist >> count;
		for(int i = 0; i < count; i++)
		{
			for (int j = 0; j < NUM_PRODUCTS; j++)
			{
				int user2id;
				double value;
				string name;
				fadjlist >> user2id;
				fadjlist >> name;
				fadjlist >> value;
				if (abs(value - 0) < EPS)
					continue;
				adj1[prodidmap[name]][id].push_back(edge(user2id, value));
			}
		}
	}
	
	//cout << 2 << "\n";

	fadjlist.close();
	for (int i = 0; i < curuser; i++)
		spamlimit[i] = 1;// + (sqrt(sqrt(sqrt(((double) spamlimit[i]) / maxcount))) * (NUM_PRODUCTS - 1));

	vector<int> products;
	for(int i = 0; i < NUM_PRODUCTS; i++)
		products.push_back(i);
	vector<int> *seeds;
	//cout << "Starting FairGreedy \n";
	for (int i = 0; i < NUM_PRODUCTS; i++)
		for (int j = 0; j < MAX; j++)
		{
			adj2[i][j] = adj1[i][j];		
			adj3[i][j] = adj1[i][j];		
			adj4[i][j] = adj1[i][j];		
		}
	seeds = fairGreedy(curuser, products, seeds);
	cout << "\n";
	for(int i = 0; i < NUM_PRODUCTS; i++)
	{
		cout << "Seeds for " << prodmap[i] << " :";
		for(int j = 0; j < seeds[i].size(); j++)
			cout << " " << seeds[i][j];
		cout << "\n";
		cout << "Expected Influence = " << influence(seeds[i], i) << " \n";
	}
	//cout << influence (seeds[0], 0);
	return 0;
}

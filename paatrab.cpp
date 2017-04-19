#include<fstream>
#include <vector>
#include <queue>
#include <iostream>

#define INF 0x3F3F

using namespace std;

vector<vector <int>> listaAdj;
vector< vector<int> > dist;
vector<vector <int>> caminho;


void bfs(int s,int n){
	queue<int> fila;		
	int visitado[n];	
	int u;	
	int i;
	int v;	
	unsigned int it;

	for(i = 0; i < n; i++){
		visitado[i] = 0;
	}
	
	dist[s][s] = 0;
	caminho[s][s] = -1;

	fila.push(s);
	
	visitado[s] = 1;
	while(!fila.empty()){
		u = fila.front();
		fila.pop();
		
		for(it = 0; it < listaAdj[u].size(); it++){
			v = listaAdj[u][it];			
			if(!visitado[v]){
				visitado[v] = 1;
				dist[s][v] = dist[s][u] + 1;
				caminho[s][v] = u;
				fila.push(v);
			}

		}

	}
}

void fullBfs(int n){
	int i;

	for(i = 0;i<n;i++){
		bfs(i,n);
	}
}


int main(){
	long long int n;
	long long int m;
	int i,j;
	vector<int>	vecAux;

	cin >> n >> m;
	
	for(i = 0; i < n; i++){
		listaAdj.push_back(vecAux);
	}	
	for(i = 0; i < m; i++){
		cin >> i >> j;
		listaAdj[i].push_back(j);
		listaAdj[j].push_back(i);
	}

	for(i = 0; i < n; i++){
		dist.push_back(vecAux);
		caminho.push_back(vecAux);
		for(j = 0; j < n; j++){
			dist[i].push_back(INF);
			caminho[i].push_back(-1);
		}
	}
	
	
	fullBfs(n);
	
	cout << "Distancias:" << endl << endl; 
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			cout << i << " -> " << j << ": " << dist[i][j] << endl;
		}
		cout << endl;
	}

	return 0;
}

#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <stack>

#define INF 0x3F3F

//Trabalhando sobre um grafo nao direcionado e sem peso nas arestas.

using namespace std;

typedef struct s_path{
    vector<vector <int> > paths;
}typePaths;

vector<vector <int>> listaAdj;      //grafo recebido
vector< vector<int> > dist;         //distancias todos para todos
vector<vector <int>> bfs_caminho;       //usado apenas no fullBfs
vector<vector <typePaths> > todosCaminhos;  //matrix onde todosCaminhos[i][j] guarda todos os menores caminhos entre i e j
vector<int> caminhoAtual;            //Auxiliar para all paths


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
	bfs_caminho[s][s] = -1;

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
				bfs_caminho[s][v] = u;
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

//caminho atual eh vector que guarda o caminho reverso de i a j
void allPaths(int i, int j,int target){
    unsigned int it;
    int it2;
    int atual;
    vector<int> vetorCaminho;
    
    caminhoAtual.push_back(j);
    
    if(i == j){
        vetorCaminho.clear();
        for(it2 = caminhoAtual.size() - 1; it2 >= 0;it2--){
            vetorCaminho.push_back(caminhoAtual[it2]);
        }
        todosCaminhos[i][target].paths.push_back(vetorCaminho);
        
        caminhoAtual.pop_back();
        return;
    }
    
    
    for(it = 0;it < listaAdj[j].size();it++){
        atual = listaAdj[j][it];
        if(dist[i][atual] < dist[i][j]){
            allPaths(i,atual,target);
        }
    }
    
    caminhoAtual.pop_back();
    return;
}

void allPathsCall(int n){
    int i,j;
    
    for(i = 0; i < n; i++){
        for(j = i; j < n; j++){
            //cout << "chamada ao allpaths: " << i << "," << j << endl;
            caminhoAtual.clear();
            allPaths(i,j,j);
        }
    }
}

void printAllPaths(int n){
    int i,j;
    unsigned int it,it2;
    int contador;
    
    cout << "****************PRINT ALL PATHS****************" << endl;
    contador = 0;
    for(i = 0;i < n;i++){
        for(j = i;j < n;j++){
            if(j != i){
                cout << endl << "-----------------------------------------" << endl;
                cout << "Entre " << i << " e " << j << ":" << endl;
                for(it = 0;it < todosCaminhos[i][j].paths.size();it++){
                    contador++;
                    cout << endl << it + 1 << ": ";
                    for(it2 = 0; it2 < todosCaminhos[i][j].paths[it].size();it2++){
                        cout << todosCaminhos[i][j].paths[it][it2] << " ";
                    }
                }
            }
        }
    }
    cout << endl << endl;
    cout << "********************************************************" << endl;
    cout << contador << " caminhos no total entre todos os vertices." << endl;
}

void printDistancias(int n){
    int i,j;
    
    cout << "Distancias:" << endl << endl; 
    for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                    cout << i << " -> " << j << ": " << dist[i][j] << endl;
            }
            cout << endl;
    }
}

int main(){
	int n;
	int m;
	int i,j;
	vector<int> vecAux;
        vector<typePaths> vecAuxPath;
        typePaths pathAux;
        int u,v;
        
        
        cin >> n >> m;
	
	for(i = 0; i < n; i++){
		listaAdj.push_back(vecAux);
	}	
	
	
	for(i = 0; i < m; i++){
		cin >> u >> v;
		listaAdj[u].push_back(v);
		listaAdj[v].push_back(u);
	}
	
	

	for(i = 0; i < n; i++){
		dist.push_back(vecAux);
		bfs_caminho.push_back(vecAux);
                todosCaminhos.push_back(vecAuxPath);
		for(j = 0; j < n; j++){
			dist[i].push_back(INF);
			bfs_caminho[i].push_back(-1);
                        todosCaminhos[i].push_back(pathAux);
		}
	}
	
	cout << "comecou full bfs" << endl;
	fullBfs(n);
	
        cout << "comecou printar distancias" << endl;
        printDistancias(n);
        
        allPathsCall(n);
        
        printAllPaths(n);
                
	return 0;
}

#include <iostream>
#include <list>
#include <queue>
#include <limits.h>

using namespace std;

class Grafo {
    int numV;
    list<int> *arestasV;

public:
    Grafo(int numV);
    void insereAresta(int v1, int v2);
    void buscaLargura(int v);
    void buscaLargura_2(int v);
};

Grafo::Grafo(int numV) {
    this->numV = numV;
    arestasV = new list<int>[numV];
}

void Grafo::insereAresta(int v1, int v2) {
    arestasV[v1].push_back(v2);
}

void Grafo::buscaLargura(int v) {
    queue<int> fila;
    bool visitados[numV];

    for (int i = 0; i < numV; i++)
        visitados[i] = false;

    cout << v << endl;
    visitados[v] = true;

    while (true) {
        list<int>::iterator it;
        for (it = arestasV[v].begin(); it != arestasV[v].end(); it++) {
            if (!visitados[*it]) {
                cout << *it << endl;
                visitados[*it] = true;
                fila.push(*it);
            }
        }
        if (!fila.empty()) {
            v = fila.front();
            fila.pop();
        } else
            break;
    }
}

void Grafo::buscaLargura_2(int v) {

    int dist[numV];
    int pais[numV];

    for (int i = 0; i < numV; ++i)
        dist[i] = INT_MAX, pais[i] = -1;

    dist[v] = 0;
    queue<int> fila;
    fila.push(v);

    while (!fila.empty()) {
        int w = fila.front();
        fila.pop();

        list<int>::iterator it;
        for (it = arestasV[w].begin(); it != arestasV[w].end(); it++) {
            if (dist[*it] == INT_MAX) {
                fila.push(*it);
                dist[*it] = dist[w] + 1;
                pais[*it] = w;
            }
        }
    }

    for (int i = 0; i < numV; ++i) {
        if (dist[v] != INT_MAX) {
            cout << v << " -> " << i << ": " << dist[i] << endl;
        } else {
            cout << v << " -> " << i << ": Sem caminho" << endl;
        }
    }


}

int main() {
    int numV = 7;

    Grafo grafo(numV);

    grafo.insereAresta(0, 1);
    grafo.insereAresta(0, 3);
    grafo.insereAresta(1, 5);
    grafo.insereAresta(2, 6);
    grafo.insereAresta(3, 2);
    grafo.insereAresta(3, 4);
    grafo.insereAresta(3, 0);


    cout << "Árvore gerada:" << endl;
            grafo.buscaLargura(0);

    cout << "Distância entre os vértices:" << endl;
            grafo.buscaLargura_2(0);

    return 0;
}
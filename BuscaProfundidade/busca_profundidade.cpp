#include <iostream>
#include <list>
#include <stack>

using namespace std;

class Grafo {
    int numV;
    list<int> *arestasV;

public:
    Grafo(int numV);
    void insereAresta(int v1, int v2);
    void imprimeArestas();
    void buscaProfundidade(int v);
    void buscaProfundidade_2(); //ordenacao topológica
    void buscaProfundidade_3(); //componentes fortemente conectados
};

Grafo::Grafo(int numV) {
    this->numV = numV;
    arestasV = new list<int>[numV];
}

void Grafo::insereAresta(int v1, int v2) {
    arestasV[v1].push_back(v2);

}

void Grafo::imprimeArestas() {
    list<int>::iterator it;
    for (int i = 0; i < numV; ++i) {
        for (list<int>::iterator it = arestasV[i].begin(); it != arestasV[i].end(); ++it)
            cout << i << " -> " << *it << endl;
    }
}

void Grafo::buscaProfundidade(int v) {
    stack<int> pilha;
    bool visitado[numV];

    for (int i = 0; i < numV; i++)
        visitado[i] = false;

    while (true) {
        if (!visitado[v]) {
            cout << v << endl;
            visitado[v] = true;
            pilha.push(v);
        }

        bool w = false;
        list<int>::iterator it;
        for (it = arestasV[v].begin(); it != arestasV[v].end(); it++) {
            if (!visitado[*it]) {
                w = true;
                break;
            }
        }

        if (w)
            v = *it;
        else {
            pilha.pop();
            if (pilha.empty())
                break;
            v = pilha.top();
        }
    }
}

void Grafo::buscaProfundidade_2() {
    stack<int> pilha;
    stack<int> pilha2;
    int t;
    bool visitado[numV];


    for (int i = 0; i < numV; i++)
        visitado[i] = false;

    for (int v = 0; v < numV; ++v) {
        while (true) {
            if (!visitado[v]) {
                visitado[v] = true;
                pilha.push(v);
            }

            bool w = false;
            list<int>::iterator it;
            for (it = arestasV[v].begin(); it != arestasV[v].end(); it++) {
                if (!visitado[*it]) {
                    w = true;
                    break;
                }
            }

            if (w)
                v = *it;
            else {
                if (pilha.empty())
                    break;
                int t = pilha.top();
                pilha2.push(t);
                pilha.pop();
                if (pilha.empty())
                    break;
                v = pilha.top();
            }
        }
    }

    while (pilha2.empty() == false) {
        cout << pilha2.top() << " ";
        pilha2.pop();
    }
}

void Grafo::buscaProfundidade_3() {
    list<int>::iterator it;
    list<int>::iterator itj;
    for (int i = 0; i < numV; ++i)
        for (int j = 0; j < numV; ++j)
            for (list<int>::iterator it = arestasV[i].begin(); it != arestasV[i].end(); ++it)
                for (list<int>::iterator itj = arestasV[j].begin(); itj != arestasV[j].end(); ++itj) {
                    if (*itj == i && j == *it) {
                        cout << i << "--->" << *it << endl;
                        cout << j << "--->" << *itj << endl;
                    }
                }
}

int main() {
    int numV = 6;

    Grafo grafo(numV);
    /*
    grafo.insereAresta(0, 5);
    grafo.insereAresta(2, 0);
    grafo.insereAresta(3, 0);
    grafo.insereAresta(3, 4);
    grafo.insereAresta(4, 1);
    grafo.insereAresta(4, 2);
    */ 
    
    grafo.insereAresta(0, 5);
    grafo.insereAresta(1, 4);
    grafo.insereAresta(2, 0);
    grafo.insereAresta(2, 4);
    grafo.insereAresta(3, 0);
    grafo.insereAresta(3, 4);
    grafo.insereAresta(4, 1);
    grafo.insereAresta(4, 2);
    grafo.insereAresta(4, 3);
    

    cout << "Arvore gerada:" << endl;
    grafo.buscaProfundidade(3);

    cout << "Arestas:" << endl;
    grafo.imprimeArestas();

    cout << "Ordenação topológica:" << endl;
    grafo.buscaProfundidade_2();

    cout << "\nComponetes:" << endl;
    grafo.buscaProfundidade_3();

    return 0;
}
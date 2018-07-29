#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <math.h>

using namespace std;

typedef struct {
    vector<int> edges;
    bool decouvert;
    int prof;
    int id;
} Node;

float max_prof = 0;
int starter_id;

Node* create_node(int id){
    Node* node = new Node;
    node->edges = vector<int>();
    node->prof = 0;
    node->decouvert = false;
    node->id = id;
    return node;
}

void prepare_graph(map<int, Node*>& graph){
    Node* actuel;
    for (map<int, Node*>::iterator it = graph.begin(); it != graph.end(); it++) {
        actuel = graph[it->first];
        actuel->decouvert = false;
        actuel->prof = 2147483647;
    } 
}

void ParcoursLargeur(map<int, Node*>& graph,int s_id){
    prepare_graph(graph);
    Node* s = graph[s_id];
    s->decouvert = true;
    s->prof = 0;
    queue<int> suiv;
    suiv.push(s->id);
    Node *actuel, *x;
    while (not suiv.empty()) {
        x = graph[suiv.front()];
        suiv.pop();
        for (int i = 0; i < x->edges.size(); i++) {
            actuel = graph[x->edges[i]];
            if (not actuel->decouvert) {
                actuel->decouvert = true;   
                actuel->prof = x->prof + 1;
                suiv.push(actuel->id);
            }
        }
    }
    for (map<int, Node*>::iterator it = graph.begin(); it != graph.end(); it++) {
        actuel = graph[it->first];
        if (actuel->prof > max_prof) {
            max_prof = actuel->prof;
            starter_id = actuel->id;
        }
    }
}

int main(){
    int n, xi, yi;
    cin >> n; cin.ignore();
    map<int, Node*> graph;
    for (int i = 0; i < n; i++) {
        cin >> xi >> yi; cin.ignore();
        if (graph.find(xi) == graph.end())
            graph[xi] = create_node(xi);
        if (graph.find(yi) == graph.end())
            graph[yi] = create_node(yi);
        graph[xi]->edges.push_back(yi);
        graph[yi]->edges.push_back(xi);
    }
    starter_id = xi;
    ParcoursLargeur(graph, starter_id);
    ParcoursLargeur(graph, starter_id);
    cout << ceil(max_prof / 2) << endl;
    for (map<int, Node*>::iterator it = graph.begin(); it != graph.end(); it++)
        delete graph[it->first];
}

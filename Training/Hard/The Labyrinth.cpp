#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cassert>
#include <stack>

using namespace std;

int R;
int C;
int A;
struct Position
{
    int x;
    int y;
};

vector<Position> recupVoisins(vector<vector<char>>& graph, Position cible){
    if (graph[cible.y][cible.x] == '?')
        return {};
    else{
        vector<Position> voisins;
        if (graph[cible.y][cible.x-1] != '#')
            voisins.push_back({cible.x-1, cible.y});
        if (graph[cible.y][cible.x+1] != '#')
            voisins.push_back({cible.x+1, cible.y});
        if (graph[cible.y-1][cible.x] != '#')
            voisins.push_back({cible.x, cible.y-1});
        if (graph[cible.y+1][cible.x] != '#')
            voisins.push_back({cible.x, cible.y+1});
        
        return voisins;
    }
}

vector<Position> dijkstra(vector<vector<char>>& graph, Position source, char goal){
    auto dist = vector<vector<int>>(R, vector<int>(C, numeric_limits<int>::max()));
    auto prev = vector<vector<Position>>(R, vector<Position>(C, {numeric_limits<int>::max(), numeric_limits<int>::max()}));
    vector<Position> inconnu;
    dist[source.y][source.x] = 0;
    for (int y = 0; y < R; ++y){
        for (int x = 0; x < C; ++x)
            inconnu.push_back({x, y});
    }
    while (!inconnu.empty()){
        vector<Position>::iterator minIt = inconnu.begin();
        int minDist = numeric_limits<int>::max();
        for (auto it = inconnu.begin(); it != inconnu.end(); ++it){
            if (dist[it->y][it->x] < minDist){
                minDist = dist[it->y][it->x];
                minIt = it;
            }
        }
        
        if (minDist == numeric_limits<int>::max())
            return {};
        Position cible = *minIt;
        inconnu.erase(minIt);
        if (graph[cible.y][cible.x] == goal){
            stack<Position> pathStack;
            Position node = cible;
            while (prev[node.y][node.x].x != numeric_limits<int>::max() && prev[node.y][node.x].y != numeric_limits<int>::max()){
                pathStack.push(node);
                node = prev[node.y][node.x];
            }

            vector<Position> chemin;
            while (!pathStack.empty()){
                chemin.push_back(pathStack.top());
                pathStack.pop();
            }
            return chemin;
        }
        vector<Position> voisins = recupVoisins(graph, cible);
        for (Position& neighbor : voisins){
            int alt = dist[cible.y][cible.x] + 1;
            if (alt < dist[neighbor.y][neighbor.x]){
                dist[neighbor.y][neighbor.x] = alt;
                prev[neighbor.y][neighbor.x] = cible;
            }
        }
    }
    return {};
}

int main(){
    cin >> R >> C >> A; cin.ignore();
    bool controlTrouve = false;
    bool controlVisite = false;
    while (1) {
        vector<vector<char>> grid;
        int KR;
        int KC;
        cin >> KR >> KC; cin.ignore();
        for (int i = 0; i < R; i++) {
            string ROW; 
            cin >> ROW; cin.ignore();
            grid.push_back({});
            for (char c : ROW)
                grid.back().push_back(c);
        }

        if (grid[KR][KC] == 'C')
            controlVisite = true;
        
        vector<Position> chemin;
        if (controlVisite){
            chemin = dijkstra(grid, {KC, KR}, 'T');
        }
        else{
            chemin = dijkstra(grid, {KC, KR}, 'C');
            if (chemin.empty())
                chemin = dijkstra(grid, {KC, KR}, '?');
        }
        assert(!chemin.empty());
        if (chemin[0].x > KC)
            cout << "RIGHT" << endl;
        else if (chemin[0].x < KC)
            cout << "LEFT" << endl;
        else if (chemin[0].y > KR)
            cout << "DOWN" << endl;
        else
            cout << "UP" << endl;
    }
}

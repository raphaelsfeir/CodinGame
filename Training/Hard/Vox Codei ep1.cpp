#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <map>

using namespace std;

struct Position{
    int x;
    int y;
};

int valDommage(vector<vector<char>>& map, int x, int y){
    int domm = 0;
    for (int i = x-1; i >= max(0, x-3); --i){
        if (map[y][i] == '#')
            break;
        else if (map[y][i] == '@')
            domm++;
    }
    for (int i = x+1; i <= min<int>(map[0].size()-1, x+3); ++i){
        if (map[y][i] == '#')
            break;
        else if (map[y][i] == '@')
            domm++;
    }
    for (int i = y-1; i >= max(0, y-3); --i){
        if (map[i][x] == '#')
            break;
        else if (map[i][x] == '@')
            domm++;
    }
    for (int i = y+1; i <= min<int>(map.size()-1, y+3); ++i){
        if (map[i][x] == '#')
            break;
        else if (map[i][x] == '@')
            domm++;
    }
    return domm;
}

void boum(vector<vector<char>>& map, int x, int y){
    for (int i = x-1; i >= max(0, x-3); --i){
        if (map[y][i] == '#')
            break;
        else if (map[y][i] == '@')
            map[y][i] = '.';
    }
    for (int i = x+1; i <= min<int>(map[0].size()-1, x+3); ++i){
        if (map[y][i] == '#')
            break;
        else if (map[y][i] == '@')
            map[y][i] = '.';
    }
    for (int i = y-1; i >= max(0, y-3); --i){
        if (map[i][x] == '#')
            break;
        else if (map[i][x] == '@')
            map[i][x] = '.';
    }
    for (int i = y+1; i <= min<int>(map.size()-1, y+3); ++i){
        if (map[i][x] == '#')
            break;
        else if (map[i][x] == '@')
            map[i][x] = '.';
    }
}

int CiblesRestantes(vector<vector<char>>& map){
    int result = 0;
    for (int y = 0; y < map.size(); ++y){
        for (int x = 0; x < map[y].size(); ++x){
            if (map[y][x] == '@')
                result++;
        }
    }
    return result;
}

bool victoire(vector<vector<char>> map, int x, int y, int bombs){
    boum(map, x, y);
    // Dommage maximal
    int dommMax = 0;
    for (int y = 0; y < map.size(); ++y){
        for (int x = 0; x < map[y].size(); ++x){
            if (map[y][x] == '.'){
                int domm = valDommage(map, x, y);
                if ((domm > dommMax)/* && victoire(map, x, y, bombs-1)*/)
                    dommMax = domm;
            }
        }
    }
    
    if (dommMax * bombs >= CiblesRestantes(map))
        return true;
    else
        return false;
}

int main(){
    vector<vector<char>> grid;
    vector<vector<char>> resultGrid;
    map<pair<int, int>, int> tickingBombs;
    int larg;
    int haut;
    cin >> larg >> haut; cin.ignore();
	
    for (int i = 0; i < haut; i++){
        string gridRow; // Une ligne de la grille
        cin >> gridRow; cin.ignore();
        grid.push_back({});
        for (char c : gridRow)
            grid.back().push_back(c);
    }
    resultGrid = grid;


    while (1) {
        int ToursRestants;
        int bombs;
        cin >> ToursRestants >> bombs; cin.ignore();
        for(auto it = tickingBombs.begin(); it != tickingBombs.end();){
            it->second--;
            if (it->second == 0){
                boum(grid, it->first.first, it->first.second);
                it = tickingBombs.erase(it);
            }
            else
                ++it;
        }
        // Maximum de dommage
        int dommMax = 0;
        Position bombPos;
        for (int x = 0; x < larg; ++x){
            for (int y = 0; y < haut; ++y){
                if (resultGrid[y][x] == '.'){
                    int domm = valDommage(resultGrid, x, y);
                    if ((domm > dommMax) && victoire(resultGrid, x, y, bombs-1)){
                        dommMax = domm;
                        bombPos = {x, y};
                    }
                }
            }
        }
        if (dommMax == 0){
            cout << "WAIT" << endl;
            continue;
        }
        if ((grid[bombPos.y][bombPos.x] == '.') && (tickingBombs.find({bombPos.x, bombPos.y}) == tickingBombs.end())){
            boum(resultGrid, bombPos.x, bombPos.y);
            tickingBombs[{bombPos.x, bombPos.y}] = 3;
            cout << bombPos.x << " " << bombPos.y << endl;
        }
        else
            cout << "WAIT" << endl;
    }
}

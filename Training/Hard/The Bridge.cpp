#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lanes(4);
std::string::size_type Trouprev;
std::string::size_type longCircuit;

struct State{
    unsigned int vitesse;
    unsigned int x;
    vector<unsigned int> y;
};

// Mouvement optimal
pair<unsigned int, std::string> decide(State etat)
{
    // Attendre
    if (etat.x >= Trouprev)
        return {0, "WAIT"};

    // Accélération
    if (etat.vitesse == 0)
        return {0, "SPEED"};

    pair<unsigned int, string> minPertes = {etat.y.size(), "WAIT"};

    // + Vitesse
    {
        State nouvEtat = etat;
        nouvEtat.vitesse += 1;
        nouvEtat.x += nouvEtat.vitesse;
        for (auto y : etat.y){
            for (unsigned int x = etat.x + 1; x <= nouvEtat.x; ++x)
            {
                if (lanes[y][x] == '0')
                {
                    nouvEtat.y.erase(std::find(nouvEtat.y.begin(), nouvEtat.y.end(), y));
                    break;
                }
            }
        }
        if (nouvEtat.y.size() > 0){
            unsigned int pertes = (etat.y.size() - nouvEtat.y.size()) + decide(nouvEtat).first;
            if (pertes == 0)
                return {0, "SPEED"};

            if (pertes < minPertes.first)
                minPertes = {pertes, "SPEED"};
        }
    }

    {
        State nouvEtat = etat;
        nouvEtat.x += nouvEtat.vitesse;
        for (auto y : etat.y){
            for (unsigned int x = etat.x + 1; x <= nouvEtat.x; ++x){
                if (lanes[y][x] == '0'){
                    nouvEtat.y.erase(std::find(nouvEtat.y.begin(), nouvEtat.y.end(), y));
                    break;
                }
            }
        }

        if (nouvEtat.y.size() > 0){
            unsigned int pertes = (etat.y.size() - nouvEtat.y.size()) + decide(nouvEtat).first;
            if (pertes == 0)
                return {0, "WAIT"};

            if (pertes < minPertes.first)
                minPertes = {pertes, "WAIT"};
        }
    }

    // Saut...possible ?
    {
        State nouvEtat = etat;
        nouvEtat.x += nouvEtat.vitesse;
        for (auto y : etat.y){
            if (lanes[y][nouvEtat.x] == '0')
                nouvEtat.y.erase(std::find(nouvEtat.y.begin(), nouvEtat.y.end(), y));
        }

        if (nouvEtat.y.size() > 0){
            unsigned int pertes = (etat.y.size() - nouvEtat.y.size()) + decide(nouvEtat).first;
            if (pertes == 0)
                return {0, "JUMP"};

            if (pertes < minPertes.first)
                minPertes = {pertes, "JUMP"};
        }
    }
    if (std::find(etat.y.begin(), etat.y.end(), 0) == etat.y.end()){
        State nouvEtat = etat;
        nouvEtat.x += nouvEtat.vitesse;
        nouvEtat.y = {};

        for (auto y : etat.y){
            bool Vivant = true;
            for (unsigned int x = etat.x + 1; x <= nouvEtat.x - 1; ++x){
                if (lanes[y][x] == '0'){
                    Vivant = false;
                    break;
                }
            }
            for (unsigned int x = etat.x + 1; x <= nouvEtat.x; ++x){
                if (lanes[y-1][x] == '0'){
                    Vivant = false;
                    break;
                }
            }

            if (Vivant)
                nouvEtat.y.push_back(y - 1);
        }

        if (nouvEtat.y.size() > 0){
            unsigned int pertes = (etat.y.size() - nouvEtat.y.size()) + decide(nouvEtat).first;
            if (pertes == 0)
                return {0, "UP"};

            if (pertes < minPertes.first)
                minPertes = {pertes, "UP"};
        }
    }

    if (std::find(etat.y.begin(), etat.y.end(), lanes.size()-1) == etat.y.end()){
        State nouvEtat = etat;
        nouvEtat.x += nouvEtat.vitesse;
        nouvEtat.y = {};

        for (auto y : etat.y){
            bool Vivant = true;
            for (unsigned int x = etat.x + 1; x <= nouvEtat.x - 1; ++x){
                if (lanes[y][x] == '0')
                {
                    Vivant = false;
                    break;
                }
            }
            for (unsigned int x = etat.x + 1; x <= nouvEtat.x; ++x){
                if (lanes[y+1][x] == '0')
                {
                    Vivant = false;
                    break;
                }
            }

            if (Vivant)
                nouvEtat.y.push_back(y + 1);
        }

        if (nouvEtat.y.size() > 0){
            unsigned int pertes = (etat.y.size() - nouvEtat.y.size()) + decide(nouvEtat).first;
            if (pertes == 0)
                return {0, "DOWN"};

            if (pertes < minPertes.first)
                minPertes = {pertes, "DOWN"};
        }
    }

    // Ralentissement... possible ?
    if (etat.vitesse > 1){
        State nouvEtat = etat;
        nouvEtat.vitesse -= 1;
        nouvEtat.x += nouvEtat.vitesse;
        for (auto y : etat.y)
        {
            for (unsigned int x = etat.x + 1; x <= nouvEtat.x; ++x)
            {
                if (lanes[y][x] == '0')
                {
                    nouvEtat.y.erase(std::find(nouvEtat.y.begin(), nouvEtat.y.end(), y));
                    break;
                }
            }
        }
        if (nouvEtat.y.size() > 0)
        {
            unsigned int pertes = (etat.y.size() - nouvEtat.y.size()) + decide(nouvEtat).first;
            if (pertes == 0)
                return {0, "SLOW"};

            if (pertes < minPertes.first)
                minPertes = {pertes, "SLOW"};
        }
    }
    return minPertes;
}

int main(){
    int M; // Controles
    cin >> M; cin.ignore();
    int V; // Minimum de survivants
    cin >> V; cin.ignore();
    cin >> lanes[0]; cin.ignore();
    cin >> lanes[1]; cin.ignore();
    cin >> lanes[2]; cin.ignore();
    cin >> lanes[3]; cin.ignore();
    Trouprev = 0;
    Trouprev = max(Trouprev, (lanes[0].rfind('0') != string::npos) ? lanes[0].rfind('0') : 0);
    Trouprev = max(Trouprev, (lanes[1].rfind('0') != string::npos) ? lanes[1].rfind('0') : 0);
    Trouprev = max(Trouprev, (lanes[2].rfind('0') != string::npos) ? lanes[2].rfind('0') : 0);
    Trouprev = max(Trouprev, (lanes[3].rfind('0') != string::npos) ? lanes[3].rfind('0') : 0);
    longCircuit = lanes[0].length();

    while (1) {
        int S; // vitesse
        cin >> S; cin.ignore();
        State currentState;
        currentState.vitesse = S;
        for (int i = 0; i < M; i++) {
            int X; // Coordonnée X
            int Y; // Coordonnée Y
            int A; // A € {0,1} selon l'activation
            cin >> X >> Y >> A; cin.ignore();

            if (A) {
                currentState.x = X;
                currentState.y.push_back(Y);
            }
        }
        cout << decide(currentState).second << endl;
    }
}

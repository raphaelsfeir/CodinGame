#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Noeud{
    Noeud* point = NULL;
    Noeud* tiret = NULL;
    long long valide = 0;
};

string encode(string input){
    string result;
    for (auto& c : input){
        switch (c){
            case 'A': result += ".-"; break;
            case 'B': result += "-..."; break;
            case 'C': result += "-.-."; break;
            case 'D': result += "-.."; break;
            case 'E': result += "."; break;
            case 'F': result += "..-."; break;
            case 'G': result += "--."; break;
            case 'H': result += "...."; break;
            case 'I': result += ".."; break;
            case 'J': result += ".---"; break;
            case 'K': result += "-.-"; break;
            case 'L': result += ".-.."; break;
            case 'M': result += "--"; break;
            case 'N': result += "-."; break;
            case 'O': result += "---"; break;
            case 'P': result += ".--."; break;
            case 'Q': result += "--.-"; break;
            case 'R': result += ".-."; break;
            case 'S': result += "..."; break;
            case 'T': result += "-"; break;
            case 'U': result += "..-"; break;
            case 'V': result += "...-"; break;
            case 'W': result += ".--"; break;
            case 'X': result += "-..-"; break;
            case 'Y': result += "-.--"; break;
            case 'Z': result += "--.."; break;
            default: throw runtime_error("ERROR");
        }
    }
    return result;
}

void insert(Noeud* n, string dict, long long pos = 0){
    while (pos < dict.size()) {
        if (dict[pos] == '.') {
            if (n->point == NULL)
                n->point = new Noeud();
            
            n = n->point;
        }else {
            if (n->tiret == NULL)
                n->tiret = new Noeud();
            
            n = n->tiret;
        }
        pos += 1;
    }
    n->valide += 1;
}

void deleteTree(Noeud* n){
    if (n->point != NULL)
        deleteTree(n->point);
    if (n->tiret != NULL)
        deleteTree(n->tiret);
    delete n;
}

string L;
Noeud* racine = new Noeud();
map<long long, long long> cache;

long long solve(long long pos){
    Noeud* n = racine;
    long long solutions = 0;
    while (pos < L.size()) {
        if ((L[pos] == '.') && (n->point != NULL))
            n = n->point;
        else if ((L[pos] == '-') && (n->tiret != NULL))
            n = n->tiret;
        else
            break;
        if (n->valide > 0) {
            if (pos == L.size()-1)
                solutions += n->valide;
            else {
                if (cache.find(pos+1) != cache.end()) {
                    solutions += n->valide *  cache[pos+1];
                }else {
                    long long res = solve(pos+1);
                    if (res > 0) {
                        solutions += n->valide * res;
                        cache[pos+1] = res;
                    }
                }
            }
        }
        ++pos;
    }
    return solutions;
}

int main(){
    cin >> L; cin.ignore();
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string W;
        cin >> W; cin.ignore();
        insert(racine, encode(W));
    }
    cout << solve(0) << endl;
    deleteTree(racine);
}

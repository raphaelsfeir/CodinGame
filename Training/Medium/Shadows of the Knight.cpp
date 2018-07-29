#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool inStr(const string& source, char key){
    for (int i = 0; i < source.size(); i++) {
        if (source[i] == key) return true;   
    }
    return false;
}

int main(){
    int L, H, N; // Dimensions de l'immeuble
    cin >> L >> H; cin.ignore();
    cin >> N; cin.ignore();
    int x, y;
    cin >> x >> y; cin.ignore();
    vector<vector<bool> > table(L, vector<bool>(H, false));
    int x0 = 0;
    int x1 = L;
    int y0 = 0;
    int y1 = H;
    
    while (1) {
        string NavBomb; // Navigation vers la bombe à partie de la localisation de Batman
        cin >> NavBomb; cin.ignore();
        cerr << x << ' ' << y << endl;
        cerr << x0 << ' ' << x1 << endl;
        cerr << y0 << ' ' << y1 << endl;
        if (inStr(NavBomb, 'U')) 
            y1 = y;
        else if (inStr(NavBomb, 'D')) 
            y0 = y; 
        if (inStr(NavBomb, 'L')) 
            x1 = x;
        else if (inStr(NavBomb, 'R')) 
            x0 = x;
        x = x0 + (x1 - x0) / 2;
        y = y0 + (y1 - y0) / 2;
        cout << x << ' ' << y << endl;
    }
}

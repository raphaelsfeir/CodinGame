#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int L;
    int H;
    cin >> L >> H; cin.ignore();
    vector<vector<int> > jeu(H, vector<int>(L));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < L; j++) {
            cin >> jeu[i][j];
        }   
    }
    int prev;
    cin >> prev; cin.ignore();
    while (1){
        int x;
        int y;
        string pos;
        cin >> x >> y >> pos; cin.ignore();
        cerr << x << ' ' << y << ' ' << pos << endl;
        cerr << jeu[y][x] << endl;
        switch (jeu[y][x]) {
            case 1:
            case 3:
            case 7:
            case 8:
            case 9:
            case 12:
            case 13:
                y++;
                break;
            case 2:
            case 6:
                x += (pos == "LEFT" ? 1 : -1);
                break;
            case 4:
                if (pos == "TOP") x--;
                else y++;
                break;
            case 5:
                if (pos == "TOP") x++;
                else y++;
                break;
            case 10:
                x--;
                break;
            case 11:
                x++;
                break;
        }
        cout << x << ' ' << y << endl;
    }
}

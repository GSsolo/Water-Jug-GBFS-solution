#include <bits/stdc++.h>
using namespace std;

struct State {
    int x, y; // isi jerigen (3-galon, 4-galon)
    vector<pair<int,int>> path; // jejak solusi

    int h() const {
        return abs(x - 3) + abs(y - 2);
    }
};  

// untuk priority_queue (heuristik terkecil diprioritaskan) Inti dari GBFS
struct Compare {
    bool operator()(const State& a, const State& b) {
        return a.h() > b.h();
    }
};

int main() {
    const int capX = 3, capY = 4;
    State start{0, 0, {{0,0}}};
    State goal{3, 2, {}};

    priority_queue<State, vector<State>, Compare> open;
    set<pair<int,int>> visited;

    open.push(start);

    while (!open.empty()) {
        State current = open.top();
        open.pop();

        if (visited.count({current.x, current.y})) continue;
        visited.insert({current.x, current.y});

        // cek goal
        if (current.x == goal.x && current.y == goal.y) {
            cout << "Solusi ditemukan:\n";
            int langka=0;
            for (auto [a,b] : current.path) {
                cout <<"Langka "<<langka<< " (" << a << "," << b << ")\n";
                langka++;
            }
            return 0;
        }
        vector<State> perintah;
        int x = current.x;
        int y = current.y;

        // 1. Isi penuh jerigen 3 galon
        if (x < capX) perintah.push_back({capX, y, current.path});

        // 2. Isi penuh jerigen 4 galon
        if (y < capY) perintah.push_back({x, capY, current.path});

        // 3. Kosongkan jerigen 3 galon
        if (x > 0) perintah.push_back({0, y, current.path});

        // 4. Kosongkan jerigen 4 galon
        if (y > 0) perintah.push_back({x, 0, current.path});

        // 5. Tuang dari 4 ke 3 hingga penuh
        if (x + y >= capX && y > 0) {
            int newX = capX;
            int newY = y - (capX - x);
            perintah.push_back({newX, newY, current.path});
        }

        // 6. Tuang dari 3 ke 4 hingga penuh
        if (x + y >= capY && x > 0) {
            int newX = x - (capY - y);
            int newY = capY;
            perintah.push_back({newX, newY, current.path});
        }

        // 7. Tuang semua dari 4 ke 3
        if (x + y <= capX && y > 0) {
            perintah.push_back({x + y, 0, current.path});
        }

        // 8. Tuang semua dari 3 ke 4
        if (x + y <= capY && x > 0) {
            perintah.push_back({0, x + y, current.path});
        }
        // tambah path lalu masukkan ke open
        for (auto &n : perintah) {
            n.path.push_back({n.x, n.y});
            if (!visited.count({n.x, n.y})) {
                open.push(n);
            }
        }
    }

    cout << "Tidak ada solusi."<<endl;
    return 0;

}

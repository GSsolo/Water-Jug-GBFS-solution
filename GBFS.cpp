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
            for (auto [a,b] : current.path) {
                cout << "(" << a << "," << b << ")\n";
            }
            return 0;
        }

        vector<State> perintah;

        // 1. Isi penuh X
        perintah.push_back({capX, current.y, current.path});
        // 2. Isi penuh Y
        perintah.push_back({current.x, capY, current.path});
        // 3. Kosongkan X
        perintah.push_back({0, current.y, current.path});
        // 4. Kosongkan Y
        perintah.push_back({current.x, 0, current.path});

        // 5. Tuang X -> Y
        {
            int transfer = min(current.x, capY - current.y);
            perintah.push_back({current.x - transfer, current.y + transfer, current.path});
        }
        // 6. Tuang Y -> X
        {
            int transfer = min(current.y, capX - current.x);
            perintah.push_back({current.x + transfer, current.y - transfer, current.path});
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
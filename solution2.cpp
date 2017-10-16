// Gaussian Elimination O(n^6)
#include <iostream>
#include <algorithm>
#include <bitset>
using namespace std;
using eqVec = bitset<90000>;

vector<vector<int>>mp;
vector<eqVec>eq;
int n, m;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int calcIndex(int i, int j)
{
    return i * m + j;
}

bool inbound(int i, int j)
{
    return i >= 0 && j >= 0 && i < n && j < m;
}

void printEQ()
{
    for(auto vec : eq) {
        cout << vec << endl;
    }
}

void xorTo(int from, int to)
{
    eq[to] ^= eq[from];
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int len = s.length();
        vector<int>tempVec;
        for(int j = 0; j < len; j++) {
            tempVec.push_back(s[j] - '0');
        }
        mp.push_back(tempVec);
    }
    m = mp[0].size();
    int cntx = n * m;

    // calc bit matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            eqVec cur;
            cur[calcIndex(i, j)] = 1;
            if(mp[i][j] == 2) {
                cur[cntx] = 0;
            } else {
                for(int k = 0; k < 4; k++) {
                    int curi = i, curj = j;
                    while(true) {
                        curi += dx[k];
                        curj += dy[k];
                        if(inbound(curi, curj) && mp[curi][curj] != 2) {
                            cur[calcIndex(curi, curj)] = 1;
                        } else {
                            break;
                        }
                    }
                }
                cur[cntx] = mp[i][j];
            }
            eq.push_back(cur);
        }
    }

#ifdef DEBUG
    // eq is (cntx) x (cntx + 1) matrix
    printEQ();
    cout << endl;
#endif

    // Gaussian Elimination
    for(int i = 0; i < cntx; i++) {
        int target;
        for(target = i; target < cntx && !eq[target][i] ; target++);
        if(target >= cntx) {
            eq[i][i] = 1;
        } else {
            swap(eq[i], eq[target]);
        }
        for(int j = 0; j < cntx; j++) {
            if(j == i)	continue;
            if(eq[j][i]) {
                xorTo(i, j);
            }
        }
    }

    for(int i = 0; i < cntx; i++) {
        cout << eq[i][cntx];
    }
    cout << endl;

    return 0;
}


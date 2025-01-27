#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define pii pair<int,int>
#define ll long long
#define llu unsigned long long
#define fs first
#define sd second

using namespace std;

const int maxn = 500;

int N,M,prevMap[maxn][maxn], curMap[maxn][maxn];
int originPMap[maxn][maxn], originCMap[maxn][maxn];
int prevOneCnt[maxn], curOneCnt[maxn];

vector<int> changeRow;
vector<pii> changeCol;

bool isEqualColumn(pii p) {
    for(int i=0;i<N;i++) {
        if(curMap[i][p.fs] != prevMap[i][p.sd]) {
            return false;
        }
    }

    return true;
}

void exchangeColumn(pii p) {
    for(int i=0;i<N;i++) {
        swap(prevMap[i][p.fs], prevMap[i][p.sd]);
    }
}

bool changeColumn() {
    for(int i=0;i<M;i++) {
        bool flag = false;
        for(int j=i;j<M;j++) {
            if(isEqualColumn({i,j})) {
                if(i!=j) {
                    exchangeColumn({i,j});
                    changeCol.push_back({i+1,j+1});
                }
                flag = true;
                break;
            }
        }
        if(!flag) {
            return false;
        }
    }

    return true;
}

void copyMap() {
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            prevMap[i][j] = originPMap[i][j];
            curMap[i][j] = originCMap[i][j];
        }
    }
}

void printAns() {
    cout<<changeRow.size()+changeCol.size()<<'\n';
    for(auto a: changeRow) {
        cout<<0<<' '<<a<<'\n';
    }
    for(auto a: changeCol) {
        cout<<1<<' '<<a.fs<<' '<<a.sd<<'\n';
    }
}

void Solution() {
    cin>>N>>M; // input
    for(int i=0;i<2;i++) {
        for(int j=0;j<N;j++) {
            for(int k=0;k<M;k++) {
                if(i) {
                    cin>>originCMap[j][k];
                    curOneCnt[j]+=originCMap[j][k];
                }
                else {
                    cin>>originPMap[j][k];
                    prevOneCnt[j]+=originPMap[j][k];
                }
            }
        }
    }

    copyMap();

    for(int i=0;i<N;i++) { // row
        if(prevOneCnt[i] == M - curOneCnt[i]) {
            for(int j=0;j<M;j++) {
                prevMap[i][j] = prevMap[i][j] ? 0:1;
            }
            changeRow.push_back(i+1);
        }
        else if(prevOneCnt[i] != curOneCnt[i]) {
            cout<<-1;
            return;
        }
    }

    if(changeColumn()) {
        printAns();
        return;
    }

    copyMap();
    changeRow.clear();
    changeCol.clear();

    for(int i=0;i<N;i++) { // row: 갯수가 뒤집거나 안뒤집거나 똑같음
        if(prevOneCnt[i] == M - curOneCnt[i]) {
            if(prevOneCnt[i] == curOneCnt[i]) {
                continue;
            }

            for(int j=0;j<M;j++) {
                prevMap[i][j] = prevMap[i][j] ? 0:1;
            }
            changeRow.push_back(i+1);
        }
    }

    if(changeColumn()) {
        printAns();
        return;
    } 

    cout<<-1;
}

int main() {
    FASTIO
    Solution();
}

/*
행은 단지 색깔만 바뀌고, 열은 위치만 교환되는 것이기에

1의 갯수를 통해 색깔을 뒤집거나 그대로 1행과 맞다고 체크

행히 다 맞다고 체크가 되면 한 열별로 비교

=>바꾼후에도 또 저 리스트가 달라질 수 있기에 이것도 업데이트해서 진행
*/
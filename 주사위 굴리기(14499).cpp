#include <iostream>
#include <vector>
#define pii pair<int,int>

using namespace std;

int N, M, x, y, K;
int MAP[20][20];

int dx[] = { 0, 0, -1, 1 };
int dy[] = { 1, -1, 0, 0 };

int Dice[7] = { 0 };

int insts[1000];

void init() {
	cin >> N >> M >> x >> y >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAP[i][j];
		}
	}
	for (int i = 0; i < K; i++)
	{
		cin >> insts[i];
		insts[i]--;
	}
}

void roll(int d) {
	int d1, d2, d3, d4, d5, d6;
	d1 = Dice[1], d2 = Dice[2], d3 = Dice[3];
	d4 = Dice[4], d5 = Dice[5], d6 = Dice[6];

	if (d == 0)
	{
		Dice[1] = d4;
		Dice[4] = d6;
		Dice[6] = d3;
		Dice[3] = d1;
	}
	else if (d == 1)
	{
		Dice[4] = d1;
		Dice[6] = d4;
		Dice[3] = d6;
		Dice[1] = d3;
	}
	else if (d == 2)
	{
		Dice[1] = d5;
		Dice[2] = d1;
		Dice[6] = d2;
		Dice[5] = d6;
	}
	else if (d == 3)
	{
		Dice[5] = d1;
		Dice[1] = d2;
		Dice[2] = d6;
		Dice[6] = d5;
	}
}

int main() {
	init();
	for (int i = 0; i < K; i++)
	{
		int inst = insts[i];
		int nx = x + dx[inst];
		int ny = y + dy[inst];

		if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;

		roll(inst);
		if (!MAP[nx][ny]) MAP[nx][ny] = Dice[6];
		else
		{
			Dice[6] = MAP[nx][ny];
			MAP[nx][ny] = 0;
		}

		cout << Dice[1] << endl;

		x = nx;
		y = ny;
	}
}
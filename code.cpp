#pragma GCC optimize ("Ofast")
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cmath>
#include<set>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<random>
#include<queue>
#include<ctime>
using namespace std;

vector<vector<int>>g;
vector<int>pred;
int S = 0;
void dfs(int s, int p) {
	pred[s] = p;
	for (int i = 0; i < g[s].size(); ++i) {
		if (g[s][i] != p) {
			dfs(g[s][i], s);
		}
	}
}
void dfscalc(int s, deque<int>& ans) {
	int meaningful = 0;
	for (int i = 0; i < g[s].size(); ++i) {
		if (g[s][i] == pred[s]) {
			continue;
		}
		if (g[g[s][i]].size() > 1) {
			++meaningful;
		}
	}
	if (meaningful == 0) {
		ans.push_back(s);
		for (int i = 0; i < g[s].size(); ++i) {
			if (g[s][i] == pred[s]) {
				continue;
			}
			ans.push_back(g[s][i]);
		}
		return;
	}
	if (meaningful == 1) {
		for (int i = 0; i < g[s].size(); ++i) {
			if (g[s][i] == pred[s]) {
				continue;
			}
			if (g[g[s][i]].size() > 1) {
				dfscalc(g[s][i], ans);
				bool f = (ans.back() == g[s][i]);
				if (f) {
					ans.push_front(s);
				}
				else {
					ans.push_back(s);
				}
				for (int q = 0; q < g[s].size(); ++q) {
					if (q == i || g[s][q] == pred[s]) {
						continue;
					}
					if (f) {
						ans.push_back(g[s][q]);
					}
					else {
						ans.push_front(g[s][q]);
					}
				}
				return;
			}
		}
		cout << "!!!";
		while (1);
	}
	if (meaningful == 2 && s == S) {
		deque<int>ans1;
		deque<int>ans2;
		int cnt = 0;
		int x1 = 0;
		int x2 = 0;
		for (int i = 0; i < g[s].size(); ++i) {
			if (g[s][i] == pred[s]) {
				continue;
			}
			if (g[g[s][i]].size() > 1) {
				++cnt;
				if (cnt == 1) {
					dfscalc(g[s][i], ans1);
					x1 = g[s][i];
				}
				else {
					dfscalc(g[s][i], ans2);
					x2 = g[s][i];
				}
			}
		}
		if (ans1.back() != x1) {
			reverse(ans1.begin(), ans1.end());
		}
		if (ans2[0] != x2) {
			reverse(ans2.begin(), ans2.end());
		}
		ans.push_back(s);
		for (int i = 0; i < ans1.size(); ++i) {
			ans.push_back(ans1[i]);
		}
		for (int i = 0; i < g[s].size(); ++i) {
			if (g[s][i] != x1 && g[s][i] != x2 && g[s][i] != pred[s]) {
				ans.push_back(g[s][i]);
			}
		}
		for (int i = 0; i < ans2.size(); ++i) {
			ans.push_back(ans2[i]);
		}
	}
	else {
		cout << "No";
		exit(0);
	}
}
int32_t main() {
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	g.assign(n, {});
	pred.assign(n, 0);
	for (int i = 1; i < n; ++i) {
		int f, t;
		cin >> f >> t;
		--f;
		--t;
		g[f].push_back(t);
		g[t].push_back(f);
	}
	for (int i = 0; i < g.size(); ++i) {
		if (g[i].size() > 1) {
			S = i;
			break;
		}
	}
	dfs(S, -1);
	deque<int> ans;
	dfscalc(S, ans);
	cout << "Yes\n";
	for (int i = 0; i < ans.size(); ++i) {
		cout << ans[i] + 1 << ' ';
	}
	return 0;
}

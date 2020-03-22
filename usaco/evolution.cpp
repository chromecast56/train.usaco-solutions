#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

vector<unordered_set<string>> cows; //array of cows, each w/ a set of traits
unordered_map<string,int> sz; //store the "subtree sizes", how many times each trait occurs
vector<pair<int,string>> order; //determine ordering of traits to group by (largest size first)
bool visited[26]; //visited[i] means "have we seen the trait i?"

bool dfs(vector<unordered_set<string>> &v, int ind = 0) { //recursively divide the groups by two (ind is the index of the trait in
    if (ind==sz.size()) return 1;                         //the order vector

    vector<unordered_set<string>> a,b; //Vec a is the cows that have the trait, Vec b is the cows that don't

    for (int i=0;i<v.size();i++)
        if (v[i].find(order[ind].S) != v[i].end())
            a.push_back(v[i]);
        else
            b.push_back(v[i]);

    if (!a.empty() && visited[ind]) return 0; //we saw the trait in this group and in an eariler group, so its bad
    if (!a.empty()) visited[ind] = 1; //we saw the trait in this group, mark it

    return dfs(a,ind+1) && dfs(b,ind+1); // Recurse down, if any group is bad then the entire system is bad
}
int main()
{
    ofstream fout("evolution.out");
    ifstream fin("evolution.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n; fin>>n;
    cows.resize(n);
    for (int i=0;i<n;i++) { //IO
        int k; fin>>k;
        for (int j=0;j<k;j++) {
            string trait; fin>>trait;
            cows[i].insert(trait);
            sz[trait]++;
        }
    }

    for (auto &val: sz) //copy items from map to vector
        order.emplace_back(val.S,val.F);

    sort(order.rbegin(),order.rend()); //sort vector in reverse

    fout << (dfs(cows) ? "yes" : "no") << '\n';

    return 0;
}

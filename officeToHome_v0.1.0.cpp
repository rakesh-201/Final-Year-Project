#include <bits/stdc++.h>
using namespace std;

const int NO_OF_SEATS = 5;
const string MALE = "Male";
const string FEMALE = "Female";

int watchmanCost, watchmanCount;

vector<int> vacantCars;

double getDist(int x, int y, int xx, int yy){
  return sqrt((pow((xx-x) * 1.0, 2) + pow((yy-y) * 1.0, 2)) * 1.0);
}

void findClosestDrop(vector<vector<int>> &locations, vector<string> &gender, vector<bool> &vis, int x, int y, int &ans, double &dist, bool findingLastDrop = 0){
    for (int j = 0; j < vis.size(); ++j) {
        if (!vis[j]) {
            int xx = locations[j][0];
            int yy = locations[j][1];

            double d = getDist(x, y, xx, yy);
            
            if(findingLastDrop && gender[j] == FEMALE)
                d += watchmanCost;

            if (d < dist) {
                dist = d;
                ans = j;
            }
        }
    }
}

void dfs(vector<vector<int>> &locations, vector<string> &gender, vector<int> &path, vector<bool> &vis,
         int i, int carNum) {
    path.push_back(i);
    vis[i] = 1;
    
    if(path.size() == NO_OF_SEATS){
        return;
    }

    int x = locations[i][0];
    int y = locations[i][1];
    int ans = -1;
    double dist = INT_MAX;
    
    bool findingLastDrop = (path.size() == (NO_OF_SEATS - 1));

    findClosestDrop(locations, gender, vis, x, y, ans, dist, findingLastDrop);

    if(findingLastDrop){
        if(gender[ans] == FEMALE){
            --watchmanCount;        // need to make changes to watchmanCost as well
        }
    }

    if(dist != INT_MAX)
        dfs(locations, gender, path, vis, ans, carNum);
    else{
        vacantCars.push_back(carNum);
    }
}

void printPaths(vector<vector<int>> &allocations, vector<vector<int>> &locations, vector<string> &gender){
    for(auto &path: allocations){
        for(auto &node: path)
            cout<<"[ "<<gender[node]<<" - ("<<locations[node][0]<< ", "<<locations[node][1]<<") ], ";
        cout<<endl<<endl;
    }
}

void getPaths(vector<vector<int>> &locations, vector<string> &gender) {
    int size = locations.size();
    vector<vector<int>> allocations;
    vector<bool> vis(size, 0);

    while(size){
        int drop = -1;
        double dist = INT_MAX;
        findClosestDrop(locations, gender, vis, 0, 0, drop, dist);

        allocations.push_back({});
        dfs(locations, gender, allocations.back(), vis, drop, allocations.size()-1);        
        size -= allocations.back().size();
    }

    printPaths(allocations, locations, gender);
}


int main() {
    vector<vector<int>> locations{
        {0, 1},
        {2, 1},
        {4, 6},
        {5, 10},
        {2, 7},
        {-1, 1},
        {-2, 1},
        {-2, 5},
        {-2, -1},
        {-3, -5},
        {-5, -5},
        {-3, 5},
        {3, -5},
        {7, -22},
        {10, -11},
        {-13, -12},
    };

    vector<string> gender {
        FEMALE,
        MALE,
        MALE,
        MALE,
        MALE,
        MALE,
        MALE,
        MALE,
        MALE,
        MALE,
        FEMALE,
        FEMALE,
        FEMALE,
        FEMALE,
        FEMALE,
        MALE
    };

    watchmanCount = 100;
    watchmanCost = 100;

    getPaths(locations, gender);

    return 0;
}
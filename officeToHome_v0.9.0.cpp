#include <bits/stdc++.h>
#include <vector>
using namespace std;

const int NO_OF_SEATS = 5;
const string MALE = "Male";
const string FEMALE = "Female";

int watchmanCost, watchmanCount, supportingFactor;

vector<int> vacantCars;

double getDist(int x, int y, int xx, int yy){
  return sqrt((pow((xx-x) * 1.0, 2) + pow((yy-y) * 1.0, 2)) * 1.0);
}

void findClosestDrop(vector<vector<int>> &locations, vector<string> &gender, vector<bool> &vis, vector<vector<bool>> &friends, int x, int y, int &ans, double &dist, vector<int> &path, bool findingLastDrop = 0){
    for (int j = 0; j < vis.size(); ++j) {
        if (!vis[j]) {
            int xx = locations[j][0];
            int yy = locations[j][1];

            double d = getDist(x, y, xx, yy);
            
            if(findingLastDrop && gender[j] == FEMALE)
                d += watchmanCost;

            int numberOfFriends = 0;
            for(auto &id : path){
                if(friends[id][j])
                    ++numberOfFriends;
            }
            d -= numberOfFriends * supportingFactor;

            if (d < dist) {
                dist = d;
                ans = j;
            }
        }
    }
}

void dfs(vector<vector<int>> &locations, vector<string> &gender, vector<vector<bool>> &friends, vector<int> &path, vector<bool> &vis,
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

    findClosestDrop(locations, gender, vis, friends, x, y, ans, dist, path, findingLastDrop);

    if(findingLastDrop){
        if(gender[ans] == FEMALE){
            --watchmanCount;        // need to make changes to watchmanCost as well
        }
    }

    if(dist != INT_MAX)
        dfs(locations, gender, friends, path, vis, ans, carNum);
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

void getPaths(vector<vector<int>> &locations, vector<string> &gender, vector<vector<bool>> &friends) {
    int size = locations.size();
    vector<vector<int>> allocations;
    vector<bool> vis(size, 0);

    while(size){
        int drop = -1;
        double dist = INT_MAX;
        allocations.push_back({});

        findClosestDrop(locations, gender, vis, friends, 0, 0, drop, dist, allocations.back());
        dfs(locations, gender, friends, allocations.back(), vis, drop, allocations.size()-1);        
        size -= allocations.back().size();
    }

    printPaths(allocations, locations, gender);
}

void markFriends(vector<vector<bool>> &friends){
    friends[0][1] = 1;
    friends[1][0] = 1;
    
    friends[0][3] = 1;
    friends[3][0] = 1;

    friends[0][4] = 1;
    friends[4][0] = 1;

    friends[0][6] = 1;
    friends[6][0] = 1;

    friends[0][8] = 1;
    friends[8][0] = 1;

    friends[0][9] = 1;
    friends[9][0] = 1;

    friends[0][11] = 1;
    friends[11][0] = 1;

    friends[0][14] = 1;
    friends[14][0] = 1;

    friends[2][1] = 1;
    friends[1][2] = 1;
    
    friends[2][3] = 1;
    friends[3][2] = 1;

    friends[2][4] = 1;
    friends[4][2] = 1;

    friends[2][6] = 1;
    friends[6][2] = 1;

    friends[2][8] = 1;
    friends[8][2] = 1;

    friends[2][9] = 1;
    friends[9][2] = 1;

    friends[2][11] = 1;
    friends[11][2] = 1;

    friends[2][14] = 1;
    friends[14][2] = 1;
    
    friends[7][1] = 1;
    friends[1][7] = 1;
    
    friends[7][3] = 1;
    friends[3][7] = 1;

    friends[7][4] = 1;
    friends[4][7] = 1;

    friends[7][6] = 1;
    friends[6][7] = 1;

    friends[7][8] = 1;
    friends[8][7] = 1;

    friends[7][9] = 1;
    friends[9][7] = 1;

    friends[7][11] = 1;
    friends[11][7] = 1;

    friends[7][14] = 1;
    friends[14][7] = 1;
    
    friends[12][1] = 1;
    friends[1][12] = 1;
    
    friends[12][3] = 1;
    friends[3][12] = 1;

    friends[12][4] = 1;
    friends[4][12] = 1;

    friends[12][6] = 1;
    friends[6][12] = 1;

    friends[12][8] = 1;
    friends[8][12] = 1;

    friends[12][9] = 1;
    friends[9][12] = 1;

    friends[12][11] = 1;
    friends[11][12] = 1;

    friends[12][14] = 1;
    friends[14][12] = 1;
    
    friends[15][1] = 1;
    friends[1][15] = 1;
    
    friends[15][3] = 1;
    friends[3][15] = 1;

    friends[15][4] = 1;
    friends[4][15] = 1;

    friends[15][6] = 1;
    friends[6][15] = 1;

    friends[15][8] = 1;
    friends[8][15] = 1;

    friends[15][9] = 1;
    friends[9][15] = 1;

    friends[15][11] = 1;
    friends[11][15] = 1;

    friends[15][14] = 1;
    friends[14][15] = 1;
    
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

    int n = locations.size();
    vector<vector<bool>> friends(n, vector<bool>(n, 0));

    markFriends(friends);

    watchmanCount = 100;
    watchmanCost = 100;
    supportingFactor = 1;

    getPaths(locations, gender, friends);

    return 0;
}
import math

NO_OF_SEATS = 5
MALE = "Male"
FEMALE = "Female"

watchmanCost = 0
watchmanCount = 0
supportingFactor = 0

vacantCars = []

def getDist(x, y, xx, yy):
    return math.sqrt((math.pow((xx-x) * 1.0, 2) + math.pow((yy-y) * 1.0, 2)) * 1.0)

def findClosestDrop(locations, gender, vis, friends, x, y, ans, dist, path, findingLastDrop=False):
    for j in range(len(vis)):
        if not vis[j]:
            xx = locations[j][0]
            yy = locations[j][1]

            d = getDist(x, y, xx, yy)

            if findingLastDrop and gender[j] == FEMALE:
                d += watchmanCost

            numberOfFriends = 0
            for id in path:
                if friends[id][j]:
                    numberOfFriends += 1
            d -= numberOfFriends * supportingFactor

            if d < dist:
                dist = d
                ans = j

def dfs(locations, gender, friends, path, vis, i, carNum):
    path.append(i)
    vis[i] = True

    if len(path) == NO_OF_SEATS:
        return

    x = locations[i][0]
    y = locations[i][1]
    ans = -1
    dist = float('inf')

    findingLastDrop = (len(path) == (NO_OF_SEATS - 1))

    findClosestDrop(locations, gender, vis, friends, x, y, ans, dist, path, findingLastDrop)

    if findingLastDrop:
        if gender[ans] == FEMALE:
            watchmanCount -= 1

    if dist != float('inf'):
        dfs(locations, gender, friends, path, vis, ans, carNum)
    else:
        vacantCars.append(carNum)

def printPaths(allocations, locations, gender):
    for path in allocations:
        for node in path:
            print("[", gender[node], "- (", locations[node][0], ", ", locations[node][1], ")], ", end="")
        print("\n")

def getPaths(locations, gender, friends):
    size = len(locations)
    allocations = []
    vis = [False] * size

    while size:
        drop = -1
        dist = float('inf')
        allocations.append([])

        findClosestDrop(locations, gender, vis, friends, 0, 0, drop, dist, allocations[-1])
        dfs(locations, gender, friends, allocations[-1], vis, drop, len(allocations) - 1)
        size -= len(allocations[-1])

    printPaths(allocations, locations, gender)

def markFriends(friends):
    friends[0][1] = True
    friends[1][0] = True

    friends[0][3] = True
    friends[3][0] = True

    friends[0][4] = True
    friends[4][0] = True

    friends[0][6] = True
    friends[6][0] = True

    friends[0][8] = True
    friends[8][0] = True

    friends[0][9] = True
    friends[9][0] = True

    friends[0][11] = True
    friends[11][0] = True

    friends[0][14] = True
    friends[14][0] = True

    friends[2][1] = True
    friends[1][2] = True

    friends[2][3] = True
    friends[3][2] = True

    friends[2][4] = True
    friends[4][2] = True

    friends[2][6] = True
    friends[6][2] = True

    friends[2][8] = True
    friends[8][2] = True

    friends[2][9] = True
    friends[9][2] = True

    friends[2][11] = True
    friends[11][2] = True

    friends[2][14] = True
    friends[14][2] = True

    friends[7][1] = True
    friends[1][7] = True

    friends[7][3] = True
    friends[3][7] = True

    friends[7][4] = True
    friends[4][7] = True

    friends[7][6] = True
    friends[6][7] = True

    friends[7][8] = True
    friends[8][7] = True

    friends[7][9] = True
    friends[9][7] = True

    friends[7][11] = True
    friends[11][7] = True

    friends[7][14] = True
    friends[14][7] = True

    friends[12][1] = True
    friends[1][12] = True

    friends[12][3] = True
    friends[3][12] = True

    friends[12][4] = True
    friends[4][12] = True

    friends[12][6] = True
    friends[6][12] = True

    friends[12][8] = True
    friends[8][12] = True

    friends[12][9] = True
    friends[9][12] = True

    friends[12][11] = True
    friends[11][12] = True

    friends[12][14] = True
    friends[14][12] = True

    friends[15][1] = True
    friends[1][15] = True

    friends[15][3] = True
    friends[3][15] = True

    friends[15][4] = True
    friends[4][15] = True

    friends[15][6] = True
    friends[6][15] = True

    friends[15][8] = True
    friends[8][15] = True

    friends[15][9] = True
    friends[9][15] = True

    friends[15][11] = True
    friends[11][15] = True

    friends[15][14] = True
    friends[14][15] = True

locations = [
    [0, 1],
    [2, 1],
    [4, 6],
    [5, 10],
    [2, 7],
    [-1, 1],
    [-2, 1],
    [-2, 5],
    [-2, -1],
    [-3, -5],
    [-5, -5],
    [-3, 5],
    [3, -5],
    [7, -22],
    [10, -11],
    [-13, -12],
]

gender = [
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
    MALE,
]

n = len(locations)
friends = [[False] * n for _ in range(n)]

markFriends(friends)

watchmanCount = 100
watchmanCost = 100
supportingFactor = 1

getPaths(locations, gender, friends)

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string reverse(string str) {
    string result;
    for (int i = str.length() - 1;i >= 0;i--) {
        result += str[i];                                                     // REVERSES THE ENTIRE STRING
    }
    return result;
}

string bridges[7] = {"AaB", "AbB", "AcC", "AdC", "AeD", "BfD", "CgD"};        // LIST OF ALL BRIDGES - AREAS ARE MARKED WITH CAPITAL LETTERS AND BRIDGES WITH SMALL LETTERS
vector<string> paths = {};                                                    // LIST OF ALL "WALK" PATHS

class bridgePuzzle {
    public:
    
        vector<string> startWalkingFromArea(string area) {
            createPathFrom(area);                                             // CALLS A "createPathFrom()" FUNCTION WITH AREA "A", "B", "C", or "D"
            return paths;                                                     // RETURNS ALL GENERATED PATHS
        }


        void createPathFrom(string area, string lastPath="NONE", vector<string> bridgesCrossedUntilNow = {}) {

            lastPath = (lastPath == "NONE") ? area : lastPath;                // IF THERE IS NO PATH, PROGRAM STARTS IN THE SELECTED AREA

            vector<string> availableBridges;                                  // VECTOR ARRAY OF BRIDGES A CERTAIN AREA

            for(int bridge = 0;bridge < 7;bridge++) {
                if(bridges[bridge].find(area) != string::npos && (find(bridgesCrossedUntilNow.begin(), bridgesCrossedUntilNow.end(), bridges[bridge].substr(1, 1)) == bridgesCrossedUntilNow.end())) { 
                    availableBridges.push_back(bridges[bridge]);              // FINDS ALL BRIDGES IN A CERTAIN AREA AND ADDS THEM TO THE "availableBridges" ARRAY
                }
            }

            if(availableBridges.size() == 0) {
                paths.push_back(lastPath);                                    // IF THERE ARE NO AVAILABLE BRIDGES, THE LAST PATH IS ADDED TO THE "paths" ARRAY
                lastPath = "NONE";                                            // CLEARS THE LAST PATH VARIABLE
                return;
            }

            for(string bridge: availableBridges) {                            // IF A BRIDGE IS AVAILABLE, THE PROGRAM SELECTS A CERTAIN PATH
                string currentlyCrossing = (bridge[0] == area[0]) ? bridge.substr(1) : reverse(bridge.substr(0, 2));
                bridgesCrossedUntilNow.push_back(bridge.substr(1, 1));        // WHEN THE PATH IS DECIDED, THE PROGRAM ADDS IT TO THE ARRAY OF ALL BRIDGES CROSSED SO FAR ("bridgesCrossedUntilNow" variable) AND CONTINUES CREATING/PROCESSING THE PATH
                createPathFrom(string(1, currentlyCrossing.back()), (lastPath + currentlyCrossing), bridgesCrossedUntilNow);
            }
        }
};


int main() {
    string allAreas[4] = {"A", "B", "C", "D"};
    int numberOfSteps, numberOfSolutions = 0;

    bridgePuzzle puzzle;                                                      // CREATES AN OBJECT "puzzle" OF THE "bridgePuzzle" CLASS
    for(string area: allAreas) {
        vector<string> walkPatterns = puzzle.startWalkingFromArea(area);      // GENERATES PATHS IN ALL AREAS
    }

    for(string path: paths) {
        cout << path << endl;                                                 // LOGS ALL PATHS TO THE CONSOLE - OPTIONAL
    }

    for(string currentWalk: paths) {
        if(currentWalk.find('a') != string::npos && currentWalk.find('b') != string::npos && currentWalk.find('c') != string::npos && currentWalk.find('d') != string::npos && currentWalk.find('e') != string::npos && currentWalk.find('f') != string::npos && currentWalk.find('g') != string::npos) {
            numberOfSolutions += 1;                                           // IF THE PROGRAM HAS CROSSED ALL BRIDGES, IT WILL ADD A SOLUTION TO THE "numberOfSolutions" VARIABLE
        }

        for(char letter: currentWalk) {
            if(letter >= 'a' && letter <= 'z') numberOfSteps += 1;            // IF THE PROGRAM CROSSED THE BRIDGE, IT ADDS A VALUE TO THE "numberOfSteps" VARIABLE
        }
    }

    cout << "\nNumber of bridges crossed: " << numberOfSteps << endl;         // LOGS THE NUMBER OF BRIDGES CROSSED TO THE CONSOLE
    cout << "Number of solutions: " << numberOfSolutions << endl;             // LOGS THE NUMBER OF SOLUTIONS FOUND TO THE CONSOLE

    return 0;
}

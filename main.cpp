/*
CIS 7A Discrete Structures C++
Team: Eric Chang, Joseph Medina, Arthur Luu
May 20th 2022
*/
// Description of program: This program calculates different travel options from
// 4 cities for sales teams. The program will analyze and show multiple routes,
// alternative paths and cheapest paths.

/*
  objectives: determine variations of trip to noted cities tarting from
riverside  (route 1)

determine shortest path (choice 3)

provide representation of trips, low-cost and shortest paths, including
matricies, adjacencies (choice 4?)

  */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//////// struct functions/////////////////////
// struct to hold adjacent cities
struct AdjacentCities {
  int adj1, adj2, adj3, adj4, city;
};

struct Node {
  int val, cost;
  Node *next;
};

struct Edge {
  int src, dest, weight;
};
///////////////////////////////////////////
class Graph {

private:
  Node *getadjNode(int value, int weight, Node *head) {
    Node *newNode = new Node;
    newNode->val = value;
    newNode->cost = weight;

    newNode->next = head;

    return newNode;
  }

  int N; // nodes in the graph, number of cities

public:
  Node **head;
  // constructor
  Graph(Edge edges[], int n, int N) {
    head = new Node *[N]();
    this->N = N;

    for (int i = 0; i < N; ++i) {
      head[i] = nullptr;
    }
    // edges to the directed graph
    for (int i = 0; i < n; ++i) {
      int src = edges[i].src;
      int dest = edges[i].dest;
      int weight = edges[i].weight;

      // insert in the beginning
      Node *newNode = getadjNode(dest, weight, head[src]);

      head[src] = newNode;
    }
  }

  // Destructor
  ~Graph() {
    for (int i = 0; i < N; i++) {
      Node *current = head[i];
      while (current) {
        Node *temp = current;
        current = current->next;
        delete temp;
      }
    }
    delete[] head;
  }
};

//////////VOID FUNCTIONS TO BE CALLED IN MAIN///////////////
void printRoutes(Graph &graph, int start, int current, bool visited[],
                 vector<int> &route, int weight) {
  visited[current] = true;
  route.push_back(current);

  // Check if all cities have been visited
  bool allVisited = true;
  for (int i = 1; i <= 4; i++) {
    if (!visited[i]) {
      allVisited = false;
      break;
    }
  }

  static int routeNumber = 1;

  // If all cities have been visited, print the route and weight
  if (allVisited) {
    cout << "Route " << routeNumber++ << ": ";
    for (int i = 0; i < route.size(); i++) {
      cout << route[i];
      if (i != route.size() - 1) {
        cout << " -> ";
      }
    }
    cout << ", Total Miles: " << weight << endl;
  }

  // Recursively explore all neighboring cities
  Node *currentNode = graph.head[current];
  while (currentNode) {
    int nextCity = currentNode->val;
    int edgeWeight = currentNode->cost;
    if (!visited[nextCity]) {
      printRoutes(graph, start, nextCity, visited, route, weight + edgeWeight);
    }
    currentNode = currentNode->next;
  }

  // Backtrack
  visited[current] = false;
  route.pop_back();
}

void routePresentation() {
  const int numCities = 4;
  Edge edges[] = {{1, 2, 24},  // Riverside to Perris
                  {1, 3, 16},  // Riverside to Moreno Valley
                  {1, 4, 33},  // Riverside to Hemet
                  {2, 3, 18},  // Perris to Moreno Valley
                  {2, 4, 30},  // Perris to Hemet
                  {3, 2, 18},  // Moreno Valley to Perris
                  {3, 4, 26},  // Moreno Valley to Hemet
                  {4, 2, 30},  // Hemet to Perris
                  {4, 3, 26}}; // Hemet to Moreno Valley

  Graph graph(edges, 9, numCities);

  vector<int> route;
  bool visited[numCities + 1] = {false};

  cout << "\n"
       << "Possible routes starting from Riverside: " << endl;
  cout << "(1): Riverside, (2): Perris, (3): Moreno Valley, (4): Hemet"
       << "\n"
       << endl;
  printRoutes(graph, 1, 1, visited, route, 0);
}

void UserChoices() {
  // main menu choices
  cout << "1.) Route Presentation (Matricies)" << endl;
  cout << "2.) Adjacent Roads" << endl;
  cout << "3.) Cheapest Roundtrip Route" << endl;
  cout << "4.) Turn off GPS" << endl;
};

void RouteDestinations() {
  // Cities / Map
  cout << "DESTINATION CITIES" << endl;
  cout << "City (1) Riverside" << endl;
  cout << "City (2) Perris" << endl;
  cout << "City (3) Moreno Valley" << endl;
  cout << "City (4) Hemet"
       << "\n"
       << endl;
}

void ShortestRoute() {
  // shortest route that is the most cost effective
  cout << "The Shortest and Cheapest route is: " << endl;
  cout << "---------------------------------------" << endl;
  cout << "Your Route: "
       << "\n"
       << endl;
  cout << " RIVERSIDE to PERRIS (24 miles) to \n MORENO VALLEY (18 miles)  to "
          "HEMET (26 miles) "
       << "\n"
       << endl;
  cout << "Route: " << endl;
  cout << " 1 -> 2 -> 3 -> 4" << endl;
  cout << " Total Miles: 68 " << endl;
  cout << "---------------------------------------" << endl;
}


void Choice1() {
  /// void function
  routePresentation();
}

void Choice2() {

  cout << "Here is a list of Adjacent Roads: "
       << "\n"
       << endl;

  AdjacentCities cityArray[4];

  cityArray[0] = {2, 3, 4}; // Riverside
  cityArray[1] = {1, 3, 4}; // Perris
  cityArray[2] = {1, 2, 4}; // Moreno Valley
  cityArray[3] = {1, 2, 3}; // Hemet

  cout << "Adjacent Roads: "
       << "\n"
       << endl;

  for (int i = 0; i < 4; i++) {
    cout << "City " << (i + 1) << ": ";
    cout << cityArray[i].adj1 << " ";
    cout << cityArray[i].adj2 << " ";
    cout << cityArray[i].adj3 << endl;
  }
}

void Choice3() {
  // Cheapest Roundtrip Route
  ShortestRoute();
};

void clearCases() // makes readibility better
{
  // Move  cursor to line 18
  cout << "\033[18;1H";
  // Clear 20 lines starting from line 18
  for (int i = 0; i < 20; i++) {
    cout << "\033[K\n";
  }
  // Move  cursor back to line 18
  cout << "\033[18;1H";
};

void Choice4(){
      cout << "\033[2J" << endl;
      cout << "\033[1;1H";
      cout << "(GPS OFF) Goodbye Now.";
};
////////////////MAIN FUNCTION//////////////////
int main() {
  // Main Menu
  cout << "Welcome to Sleepy Joe's Solar Sales GPS :"
       << "\n"
       << "---------------------------------------" << endl;
  RouteDestinations();

  cout << "MAIN MENU: " << endl;
  // edges hardcoded in with weights
  int n = 0;
  // User Options
  UserChoices();
  cout << "---------------------------------------" << endl;
  // User input
  cout << "Please selet an option. " << endl;
  do {
    cout << "\n";
    cout << "Press a # to continue: " << endl;
    cin >> n;
    cout << "\n";

    switch (n) {
    case 1: {
      clearCases();
      Choice1();
      break;
    }
    case 2: {
      clearCases();
      Choice2();
      break;
    }
    case 3: {
      clearCases();
      Choice3();
      break;
    }
    case 4: {
      Choice4();
      return 0;
    }
    }
     if (n < 1 || n > 5) {
      cout << "Error. Please select from the 4 options or Turn off GPS.";
    }
  } while (n != 5);

  return 0;
}

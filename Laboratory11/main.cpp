#define INFINITY 10000000
#include <iostream>
#include <string.h>
#include <sstream>
#include <map>
#include <list>

using namespace std;

struct Vertice{
    map < int, double > adjacency;
};

struct Graph{
    Vertice * vertice;
    int vertices;
};


double getWeight(Graph &g, int u, int v){
    return g.vertice[u].adjacency[v];
}

void insertEdge(Graph &g, int u, int v, double weight){
    g.vertice[u].adjacency[v] = weight;
}

void loadGraph(Graph &g, int n, int m){
    g.vertices = n;
    g.vertice = new Vertice[n];

    int u,v,w;
    for (int i = 0; i < m; i++){
        cin >> u;
        cin >> v;
        cin >> w;
        insertEdge(g,u,v,w);
    }
}

bool edgeExist(Graph &g, int u, int v){
    return g.vertice[u].adjacency.count(v);
}

bool findEdge(Graph &g, int u, int v, double &weight){
    if (u == v) {
        weight = 0;
        return true;
    }
    if (edgeExist(g, u, v)){
        weight = g.vertice[u].adjacency[v];
        return true;
    };
    return false;
}

void showAsMatrix(Graph &g){
    double weight;
    bool find;
    for (int i = 0; i < g.vertices; i++){

        for (int j = 0; j < g.vertices; j++){
            find = findEdge(g, i, j, weight);

            if (find){
                cout << weight << ",";
            }else{
                cout << '-' << ',';
            }
        }
        cout << endl;
    }
}

void showAsArrayOfLists(Graph &g){
    for (int i = 0; i < g.vertices; i++){
        cout << i << ':';
        for (    map<int, double>::iterator it = g.vertice[i].adjacency.begin(); it != g.vertice[i].adjacency.end(); it++){
            cout << it->first << '(' << it ->second << "),";
        }
        cout << endl;
    }
}


void searchDepth(Graph &g, int current, bool visited[]){
    visited[current] = true;
    cout << current << ",";

    for(map<int, double>::iterator it = g.vertice[current].adjacency.begin(); it != g.vertice[current].adjacency.end(); it++)
        if (!visited[it->first])
            searchDepth(g, it->first, visited);
}



void DFS(Graph &g, int current){
    bool *visited = new bool[g.vertices];
    for (int i = 0; i < g.vertices; i++)
        visited[i] = false;

    searchDepth(g, current, visited);

    cout << endl;
}

void BFS(Graph &g, int current){
    bool *visited = new bool[g.vertices];
    for(int i = 0; i < g.vertices; i++)
        visited[i] = false;

    list<int> queue;

    visited[current] = true;
    queue.push_back(current);

    while(!queue.empty())
    {
        current = queue.front();
        cout << current << ",";
        queue.pop_front();

        for(map<int, double>::iterator it = g.vertice[current].adjacency.begin(); it != g.vertice[current].adjacency.end(); it++)
        {
            if(!visited[it->first])
            {
                visited[it->first] = true;
                queue.push_back(it->first);
            }
        }
    }
    cout << endl;
}

bool isCommand(const string command,const char *mnemonic){
    return command==mnemonic;
}


int main(){
    string line;
    string command;
    Graph *graph;
    int currentT=0;
    int value;
    cout << "START" << endl;
    while(true){
        getline(cin,line);
        std::stringstream stream(line);
        stream >> command;
        if(line=="" || command[0]=='#')
        {
            // ignore empty line and comment
            continue;
        }

        // copy line on output with exclamation mark
        cout << "!" << line << endl;;

        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);

        // zero-argument command
        if(isCommand(command,"HA")){
            cout << "END OF EXECUTION" << endl;
            break;
        }
        // zero-argument command
        if(isCommand(command,"SM"))
        {
            showAsMatrix(graph[currentT]);
            continue;
        }
        if(isCommand(command,"SA"))
        {
            showAsArrayOfLists(graph[currentT]);
            continue;
        }


        // read next argument, one int value
        stream >> value;

        if(isCommand(command,"LG"))
        {
            int m;
            stream >> m;
            loadGraph(graph[currentT],value,m);
            continue;
        }
        if(isCommand(command,"BF"))
        {
            BFS(graph[currentT],value);
            continue;
        }
        if(isCommand(command,"DF"))
        {
            DFS(graph[currentT],value);
            continue;
        }

        if(isCommand(command,"IE"))
        {
            int v;
            double w;
            stream >> v >> w;
            insertEdge(graph[currentT],value,v,w);
            continue;
        }

        if(isCommand(command,"FE"))
        {
            int v;
            stream >> v;
            double w;
            bool ret=findEdge(graph[currentT],value,v,w);

            if(ret)
                cout << w << endl;
            else
                cout << "false" << endl;
            continue;
        }


        if(isCommand(command,"CH"))
        {
            currentT=value;
            continue;
        }

        if(isCommand(command,"GO"))
        {
            graph=new Graph[value];
            continue;
        }

        cout << "wrong argument in test: " << command << endl;
        return 1;
    }
}

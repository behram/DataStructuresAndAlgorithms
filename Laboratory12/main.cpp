#include<iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

using namespace std;

#define INFINITY 10000000

struct Graph{
    float ** edges;
    int u;
};

void loadGraph(Graph &g, int n, int m){

    g.u = n;

    float ** temp = new float*[n];
    for (int i = 0; i<n ; i++)
    {
        temp[i] = new float[n];
    }
    g.edges = temp;
    int a,b;
    float c;

    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<n; j++)
        {
            g.edges[i][j] = INFINITY;
        }
    }

    while (scanf("%d %d %f", &a,&b,&c)!= 0)
    {
        g.edges[a][b] = c;
    }
}

void insertEdge(Graph &g, int u, int v, double weight){

    g.edges[u][v] = weight;
}

bool findEdge(Graph &g, int u, int v, double &weight){
    if (g.edges[u][v]!=INFINITY)
    {
        weight = g.edges[u][v];
        return true;
    }

    return false;
}

void showAsMatrix(Graph &g){

    for (int i = 0; i< g.u; i++)
    {
        for (int j = 0; j<g.u; j++)
        {
            if(i == j)
            {
                cout << "0,";
                continue;
            }
            if(g.edges[i][j]==INFINITY)
            {
                cout << "-,";
                continue;
            }
            else
            {
                cout << g.edges[i][j] <<",";
            }

        }
        cout << endl;
    }
}

void showAsArrayOfLists(Graph &g){

    for (int i = 0; i< g.u; i++)
    {
        cout << i << ":";
        for (int j = 0; j< g.u; j++)
        {
            if (g.edges[i][j]!=INFINITY)
            {
                cout << j << "(" << g.edges[i][j] << "),";
            }
        }
        cout << endl;
    }
}

int shortestDistance(int dist[], bool sptSet[], int V)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++){
        if (!sptSet[v] && dist[v] <= min){
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void SSSP(Graph &g, int src)
{
    int dist[g.u];

    bool sptSet[g.u];

    for (int i = 0; i < g.u; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < g.u-1; count++) {
        int u = shortestDistance(dist, sptSet, g.u);

        sptSet[u] = true;

        for (int v = 0; v < g.u; v++){
            if (!sptSet[v] && g.edges[u][v] && dist[u] != INT_MAX
                && dist[u]+g.edges[u][v] < dist[v]){
                dist[v] = dist[u] + g.edges[u][v];
            }
        }
    }

    for (int i = 0; i < g.u; i++){
        printf("%d(%d)\n", i, dist[i]);
    }
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

        if(isCommand(command,"SS"))
        {
            SSSP(graph[currentT], value);
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

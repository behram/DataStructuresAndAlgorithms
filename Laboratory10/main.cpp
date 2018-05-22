#include<iostream>
#include<string.h>
#include <sstream>

using namespace std;

#define INFINITY 10000000

struct Graph{
    double * arr;
    int vertices;
};

double getWeight(Graph &g, int u, int v){
    return g.arr[u*g.vertices + v];
}
void insertEdge(Graph &g, int u, int v, double weight){
    g.arr[u*g.vertices + v] = weight;
}

void loadGraph(Graph &g, int n, int m){
    g.vertices = n;
    g.arr = new double[n*n];
    for (int i = 0; i < n*n; i++){
        if (i/g.vertices == i% g.vertices)
            g.arr[i] = 0;
        else
            g.arr[i] = -1;

    }
    int u,v,w;
    for (int i = 0; i < m; i++){
        cin >> u;
        cin >> v;
        cin >> w;
        insertEdge(g,u,v,w);
    }
}


bool findEdge(Graph &g, int u, int v, double &weight){
    weight = g.arr[u*g.vertices + v];
    return (weight > 0);
}

void showAsMatrix(Graph &g){
    double d;
    for (int i = 0; i < g.vertices; i++){
        for (int j = 0; j < g.vertices; j++){
            d = g.arr[i*g.vertices + j];
            if (d < 0){
                cout << '-' << ',';
            }
            else
                cout << g.arr[i*g.vertices + j] << ',';
        }
        cout << endl;
    }
}

void showAsArrayOfLists(Graph &g){
    for (int i = 0; i < g.vertices; i++){
        cout << i << ":";
        for (int j = 0; j < g.vertices; j++){
            if (g.arr[i*g.vertices+j]>0)
                cout << j << '(' << g.arr[i*g.vertices+j] << "),";
        }
        cout << endl;
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

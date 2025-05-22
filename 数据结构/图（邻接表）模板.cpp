#include <iostream>
#include <vector>
#include <list>

class Graph
{
public:
    Graph(int vertices);
    void addEdge(int src, int dest);
    void printGraph();

private:
    int vertices;
    std::vector<std::list<int>> adjList;
};

Graph::Graph(int vertices)
{
    this->vertices = vertices;
    adjList.resize(vertices);
}

void Graph::addEdge(int src, int dest)
{
    adjList[src].push_back(dest);
    adjList[dest].push_back(src); // For undirected graph
}

void Graph::printGraph()
{
    for (int i = 0; i < vertices; ++i)
    {
        std::cout << "Vertex " << i << ":";
        for (auto x : adjList[i])
            std::cout << " -> " << x;
        std::cout << std::endl;
    }
}

int main()
{
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.printGraph();

    return 0;
}
#include "graph.h"

void initGraph(graph &G) {
    firstVertex(G) = NULL;
}

void addVertex(graph &G, string newVertexID) {
    adrVertex newVertex = new vertex;
    infoVertex(newVertex) = newVertexID;
    nextVertex(newVertex) = NULL;
    firstEdge(newVertex) = NULL;

    if (firstVertex(G) == NULL) {
        firstVertex(G) = newVertex;
    } else {
        adrVertex temp = firstVertex(G);
        while (nextVertex(temp) != NULL) {
            temp = nextVertex(temp);
        }
        nextVertex(temp) = newVertex;
    }
}

void addEdge(graph &G, string startVertexID, string endVertexID, int weight) {
    adrVertex start = firstVertex(G);
    adrVertex end = firstVertex(G);

    while (start != NULL && infoVertex(start) != startVertexID) {
        start = nextVertex(start);
    }

    while (end != NULL && infoVertex(end) != endVertexID) {
        end = nextVertex(end);
    }

    if (start != NULL && end != NULL) {
        adrEdge newEdge = new edge;
        destEdge(newEdge) = endVertexID;
        weightEdge(newEdge) = weight;
        nextEdge(newEdge) = firstEdge(start);
        firstEdge(start) = newEdge;

        // Add reverse edge for undirected graph
        newEdge = new edge;
        destEdge(newEdge) = startVertexID;
        weightEdge(newEdge) = weight;
        nextEdge(newEdge) = firstEdge(end);
        firstEdge(end) = newEdge;
    }
}

void buildGraph(graph &G) {
    initGraph(G);
    string vertexID;
    while (true) {
        cout << "Masukkan nama kota (atau . untuk selesai): ";
        cin >> vertexID;
        if (vertexID == ".") break;
        addVertex(G, vertexID);
    }

    string start, end;
    int weight;
    while (true) {
        cout << "Masukkan kota awal (atau . untuk selesai): ";
        cin >> start;
        if (start == ".") break;
        cout << "Masukkan kota tujuan: ";
        cin >> end;
        cout << "Masukkan jarak: ";
        cin >> weight;
        addEdge(G, start, end, weight);
    }
}

void printGraph(graph &G) {
    adrVertex temp = firstVertex(G);
    while (temp != NULL) {
        cout << "Kota: " << infoVertex(temp) << endl;
        adrEdge edgeTemp = firstEdge(temp);
        while (edgeTemp != NULL) {
            cout << "  Ke: " << destEdge(edgeTemp) << " dengan jarak " << weightEdge(edgeTemp) << endl;
            edgeTemp = nextEdge(edgeTemp);
        }
        temp = nextVertex(temp);
    }
}

void findShortestPath(graph &G, string startVertexID, string endVertexID) {
    const int MAX = 100;
    const int INF = 1e9;
    string vertices[MAX];
    int adjMatrix[MAX][MAX];
    int vertexCount = 0;

    adrVertex temp = firstVertex(G);
    while (temp != NULL) {
        vertices[vertexCount++] = infoVertex(temp);
        temp = nextVertex(temp);
    }

    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            adjMatrix[i][j] = (i == j) ? 0 : INF;
        }
    }

    temp = firstVertex(G);
    while (temp != NULL) {
        int u = -1;
        for (int i = 0; i < vertexCount; i++) {
            if (vertices[i] == infoVertex(temp)) {
                u = i;
                break;
            }
        }

        adrEdge edgeTemp = firstEdge(temp);
        while (edgeTemp != NULL) {
            int v = -1;
            for (int i = 0; i < vertexCount; i++) {
                if (vertices[i] == destEdge(edgeTemp)) {
                    v = i;
                    break;
                }
            }
            adjMatrix[u][v] = weightEdge(edgeTemp);
            edgeTemp = nextEdge(edgeTemp);
        }

        temp = nextVertex(temp);
    }

    int dist[MAX], prev[MAX];
    bool visited[MAX] = {false};
    for (int i = 0; i < vertexCount; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }

    int startIdx = -1, endIdx = -1;
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i] == startVertexID) startIdx = i;
        if (vertices[i] == endVertexID) endIdx = i;
    }

    if (startIdx == -1 || endIdx == -1) {
        cout << "Salah satu atau kedua kota tidak ditemukan!" << endl;
        return;
    }

    dist[startIdx] = 0;
    for (int i = 0; i < vertexCount; i++) {
        int u = -1;
        for (int j = 0; j < vertexCount; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF) break;

        visited[u] = true;
        for (int v = 0; v < vertexCount; v++) {
            if (adjMatrix[u][v] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                prev[v] = u;
            }
        }
    }

    if (dist[endIdx] == INF) {
        cout << "Tidak ada jalur dari " << startVertexID << " ke " << endVertexID << endl;
    } else {
        cout << "Jalur terpendek dari " << startVertexID << " ke " << endVertexID << " adalah " << dist[endIdx] << endl;
        string path = endVertexID;
        for (int at = endIdx; at != -1; at = prev[at]) {
            if (at != endIdx) path = vertices[at] + " -> " + path;
        }
        cout << "Rute: " << path << endl;
    }
}

string findMostVisitedNode(graph &G) {
    const int MAX = 100;
    int edgeCount[MAX] = {0};
    string vertices[MAX];
    int vertexCount = 0;

    adrVertex temp = firstVertex(G);
    while (temp != NULL) {
        vertices[vertexCount++] = infoVertex(temp);
        temp = nextVertex(temp);
    }

    temp = firstVertex(G);
    while (temp != NULL) {
        adrEdge edgeTemp = firstEdge(temp);
        while (edgeTemp != NULL) {
            for (int i = 0; i < vertexCount; i++) {
                if (vertices[i] == destEdge(edgeTemp)) {
                    edgeCount[i]++;
                    break;
                }
            }
            edgeTemp = nextEdge(edgeTemp);
        }
        temp = nextVertex(temp);
    }

    int maxCount = -1;
    string mostVisited;
    for (int i = 0; i < vertexCount; i++) {
        if (edgeCount[i] > maxCount) {
            maxCount = edgeCount[i];
            mostVisited = vertices[i];
        }
    }

    return mostVisited;
}

void findAlternativePath(graph &G, string startVertexID, string endVertexID, string blockedVertex) {
    const int MAX = 100;
    const int INF = 1e9;
    string vertices[MAX];
    int adjMatrix[MAX][MAX];
    int vertexCount = 0;

    adrVertex temp = firstVertex(G);
    while (temp != NULL) {
        vertices[vertexCount++] = infoVertex(temp);
        temp = nextVertex(temp);
    }

    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            adjMatrix[i][j] = (i == j) ? 0 : INF;
        }
    }

    temp = firstVertex(G);
    while (temp != NULL) {
        int u = -1;
        for (int i = 0; i < vertexCount; i++) {
            if (vertices[i] == infoVertex(temp)) {
                u = i;
                break;
            }
        }

        adrEdge edgeTemp = firstEdge(temp);
        while (edgeTemp != NULL) {
            int v = -1;
            for (int i = 0; i < vertexCount; i++) {
                if (vertices[i] == destEdge(edgeTemp)) {
                    v = i;
                    break;
                }
            }

            if (vertices[u] != blockedVertex && vertices[v] != blockedVertex) {
                adjMatrix[u][v] = weightEdge(edgeTemp);
            }

            edgeTemp = nextEdge(edgeTemp);
        }

        temp = nextVertex(temp);
    }

    // Jalankan logika mirip dengan findShortestPath
    int dist[MAX], prev[MAX];
    bool visited[MAX] = {false};
    for (int i = 0; i < vertexCount; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }

    int startIdx = -1, endIdx = -1;
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i] == startVertexID) startIdx = i;
        if (vertices[i] == endVertexID) endIdx = i;
    }

    if (startIdx == -1 || endIdx == -1) {
        cout << "Salah satu atau kedua kota tidak ditemukan!" << endl;
        return;
    }

    dist[startIdx] = 0;
    for (int i = 0; i < vertexCount; i++) {
        int u = -1;
        for (int j = 0; j < vertexCount; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF) break;

        visited[u] = true;
        for (int v = 0; v < vertexCount; v++) {
            if (adjMatrix[u][v] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                prev[v] = u;
            }
        }
    }

    if (dist[endIdx] == INF) {
        cout << "Tidak ada jalur alternatif dari " << startVertexID << " ke " << endVertexID << " dengan " << blockedVertex << " diblokir." << endl;
    } else {
        cout << "Jalur alternatif dari " << startVertexID << " ke " << endVertexID << " dengan " << blockedVertex << " diblokir adalah " << dist[endIdx] << endl;
        string path = endVertexID;
        for (int at = endIdx; at != -1; at = prev[at]) {
            if (at != endIdx) path = vertices[at] + " -> " + path;
        }
        cout << "Rute: " << path << endl;
    }
}

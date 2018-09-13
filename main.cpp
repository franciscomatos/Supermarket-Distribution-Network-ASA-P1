#include <vector>
#include <stdio.h>
#include <algorithm>


/*will be used for output*/
int subnetworks = 0;
int nConnections = 0;
std::vector<int> scc;
std::vector<std::vector<int> > connections;

bool sortFunction(const std::vector<int>& a, const std::vector<int>&b) {
  if(a[0] == b[0])
    return a[1] < b[1];
  else
    return a[0] < b[0];
}

bool checkForDuplicates(std::vector<int> * list, int * origin, int * item) {
  int i, size = (*list).size();
  for(i = 0; i < size; i++) {
    if((*list)[i] == (*item)) {
      return true;
    }
  }
  return false;
}

int findScc(int item, int * rootLow) {
  int i, size = scc.size();
  for(i = 0; i < size; i++) {
    if(rootLow[scc[i]] == rootLow[item]) return scc[i];
  }
  return -1;
}

void tarjanVisit(int i, std::vector<std::vector<int> > * graph, int * visited,
  int * visitedVertices, int * iVisited, int * low, std::vector<int> * stack,
  int * stackedVertices, int * rootLow) {

    int j, size = (*graph)[i].size();

    visitedVertices[i] = 1;
    low[i] = *visited;
    iVisited[i] = (*visited)++;
    (*stack).push_back(i);
    stackedVertices[i] = 1;

    for(j = 0; j < size; j++) {
      if(visitedVertices[(*graph)[i][j]] == 0) {
        tarjanVisit((*graph)[i][j], graph, visited, visitedVertices,
          iVisited, low, stack, stackedVertices, rootLow);
        low[i] = std::min(low[i],low[(*graph)[i][j]]);
      } else if(stackedVertices[(*graph)[i][j]] == 1) {
        low[i] = std::min(low[i],iVisited[(*graph)[i][j]]);
      }

      if(i != (*graph)[i][j]) {
        if(low[(*graph)[i][j]] != iVisited[i]) {
        nConnections++;
        connections[nConnections-1].push_back(i);
        connections[nConnections-1].push_back((*graph)[i][j]);
        }
      }
    }

    if(low[i] == iVisited[i]) {
      subnetworks++;
      int n, smallest = (*stack).back();
      do {
        n = (*stack).back();
        rootLow[n] = low[i];
        if(n < smallest) smallest = n;
        (*stack).pop_back();
        stackedVertices[n] = 0;
      } while(n != i);
      scc[subnetworks-1] = smallest;
    }

    /*cleans the memory*/
    (*graph)[i].clear();
}

void tarjan(std::vector<std::vector<int> > * graph, int * nVertices, int * rootLow) {
  int visited = 0;

  int * visitedVertices = new int[*nVertices]();
  int * iVisited = new int[*nVertices]();
  int * low = new int[*nVertices]();
  int * stackedVertices = new int[*nVertices]();
  std::vector<int> stack (*nVertices);

  int i;
  for(i = 0; i < *nVertices; i++) {
    visitedVertices[i] = 0;
    stackedVertices[i] = 0;
  }

  for(i = 0; i < *nVertices; i++) {
    if(visitedVertices[i] == 0) {
      tarjanVisit(i, graph, &visited, visitedVertices, iVisited,
        low, &stack, stackedVertices, rootLow);
    }
  }

  /*cleans the memory*/
  delete[] visitedVertices;
  delete[] iVisited;
  delete[] low;
  delete[] stackedVertices;
  stack.clear();
}

int main() {
  int nVertices, allConnections, a, b, i;

  scanf("%d %d", &nVertices, &allConnections);

  std::vector<std::vector<int> > connectedVertices(nVertices);
  scc.resize(nVertices);
  connections.resize(allConnections);

  for(i = 0; i < allConnections; ++i){
    scanf("%d %d", &a, &b);
    connectedVertices[a-1].push_back(b-1);
  }

  int * rootLow = new int[nVertices]();

  tarjan(&connectedVertices, &nVertices, rootLow);

  scc.resize(subnetworks);
  connections.resize(nConnections);


  std::vector<std::vector<int> > connectionsIndexes(nVertices);

  int sccOrigin, sccDestiny, size = connections.size();
  for(i = 0; i < size; i++) {
    sccOrigin = findScc(connections[i][0], rootLow);
    sccDestiny = findScc(connections[i][1], rootLow);
    if(sccOrigin != sccDestiny &&
      checkForDuplicates(&(connectionsIndexes[sccOrigin]), &sccOrigin, &sccDestiny) == false) {
        connectionsIndexes[sccOrigin].push_back(sccDestiny);
        connections[i][0] = sccOrigin;
        connections[i][1] = sccDestiny;
    } else {
      connections[i][0] = -1;
      connections[i][1] = -1;
      nConnections--;
    }
  }

  std::sort(connections.begin(), connections.end(), sortFunction);

  printf("%d\n%d\n",subnetworks,nConnections);
  for(i = 0; i < size; i++) {
    if(connections[i][0] != -1 && connections[i][1] != -1)
      printf("%d %d\n", connections[i][0]+1, connections[i][1]+1);
  }

  /*cleans the memory*/
  size = connectedVertices.size();
  for(i = 0; i < size; i++)
    connectedVertices[i].clear();
  for(i = 0; i < nConnections; i++)
    connections[i].clear();
  for(i = 0; i < nVertices; i++)
    connectionsIndexes[i].clear();

  connectedVertices.clear();
  scc.clear();
  connections.clear();
  connectionsIndexes.clear();
  delete[] rootLow;

  return 0;
}

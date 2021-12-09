#include<iostream>
#include <chrono>
#include "Node.h"
#include "maze.h"
#include "dfs.h"
#include "bfs.h"
#include<string>
#include<cstring>
#include<alloca.h>
using namespace std::chrono;

int UI();

int main()
{
    Maze *puzzle;
    std::cout<<"Enter the name of imageName with Extension"<<std::endl;
    std::string imgName="";
    std::cin>>imgName;
     char *img;

    

    img= (char *)alloca(imgName.size() + 1);
    memcpy(img, imgName.c_str(), imgName.size() + 1);


    puzzle=new Maze(img);
   system("clear");
    int AlgOption =UI();
    auto start = high_resolution_clock::now();
    switch(AlgOption)
    {
    case 1:
        puzzle->dfs();
        break;
    case 2:
            puzzle->bfs();
        break;
     default:
        std::cout<<"INVALID INPUT";
        return -1;
    }
        auto stop = high_resolution_clock::now();
 auto duration = duration_cast<microseconds>(stop - start);
    system("clear");
     std::string alg ="";
  switch(AlgOption)
    {
    case 1:
        std::cout<<"\tDepth First Search";
         alg="Depth First Search";
        break;
    case 2:
        std::cout<<"\tBreadth First Search ";
        alg="Breadth First Search ";
        break;
   
    }
   
    
    std::cout<<"\nTime Complexity: O(|V|+|E|)";
    std::cout<<"\nTotal Time taken by "<<alg<<" Algorithm: "<<duration.count()<< " ms";
    std::cout<<"\nNo. of Steps: "<<puzzle->steps;
    std::cout << "\nAverage Time taken by "<<alg<<"  Algorithm: "<< (float) duration.count() / puzzle->steps<< " ms";
    std::cout<<"\nTotal Number of Nodes: "<<puzzle->nodeList.size();
    std::cout<<"\nUsed Nodes count: "<<puzzle->path.size();
    std::cout<<"\nDistance: "<<puzzle->printSolution();
    return 0;
}

int UI()
{
    std::cout<<"Choose Solving Algorithm";
    std::cout<<"\n1. Depth First Search";
    std::cout<<"\n2. Breadth First Search";
    std::cout<<"\nEnter You Choice: ";
 
    int val;
    std::cin>>val;
    return val;
}

#include<vector>
#include<iterator>
#include<math.h>
#include "opencv2/core/version.hpp"
#include <opencv2/highgui/highgui.hpp>

class Maze
{
    int height;
    int width;
    Node* SNode;
    Node* ENode;
    int noOfNodes;
    cv::Mat image;

public:
    std::vector<Node*> connections;

        std::vector<Node*> nodeList;
    std::vector<int> path;

    long int steps;
    Maze(char* imageName)
    {
        image = cv::imread(imageName , CV_LOAD_IMAGE_COLOR); //BGR format
          if(! image.data ) 
          {
      std::cout <<  "Corrupt Image" << std::endl ;
      exit(0);
            }
        this->height=image.size().height;
        this->width=image.size().width;
        Node* topNodes[width]={nullptr};
        Node *leftnode;
        Node *n;
        steps=1;
        Node* t;
        noOfNodes=0;
        int i=0,j=0;
        while(image.data[i*3]!=255) //if B of BGR pixel is white then stop
        {
            i=i+1;
        }
        SNode= new Node(i,0,noOfNodes);
        nodeList.push_back(SNode);
        connections.push_back(SNode);
        topNodes[i]=SNode;
        noOfNodes += 1;
        int rowOffset,rowAboveOffset,rowBelowOffset;
        bool prv,cur,nxt;

        for(j=1;j<height-1;j++)
        {
            rowOffset = (j * width);
            rowAboveOffset = rowOffset - width;
            rowBelowOffset = rowOffset + width;
            prv = false;
            cur = false;
            nxt = (image.data[(rowOffset+1)*3] == 255);// 1->next

            leftnode = nullptr;
            for(i=1;i<width-1;i++)
            {
                // Move previous, current and next onwards.
                // This way we read from the image once per pixel,
                prv = cur;
                cur = nxt;
                nxt = (image.data[(rowOffset + i+1)*3] != 0); //B of RGB
                n=nullptr;
                if(!cur)
                {
                    //ON WALL - No action
                    continue;
                }
                if(prv)
                {
                    if(nxt)//path path path
                    {
                        //create node iff there is path above or below
                        if((image.data[(rowAboveOffset + i)*3] != 0) || (image.data[(rowBelowOffset + i)*3] != 0))
                        {
                            n = new Node(i,j,noOfNodes);
                            nodeList.push_back(n);
                            if(image.data[(rowOffset + i)*3 + 1] == 0) // R of BGR, B!=0 and R=0 then it mightbe blue or green
                            {
                                connections.push_back(n);
                            }
                            leftnode->neighbours[1] = n;
                            n->neighbours[3] = leftnode;
                            leftnode = n;
                        }
                    }
                    else
                    {
                       
                        n = new Node(i,j,noOfNodes);
                        nodeList.push_back(n);
                        if(image.data[(rowOffset + i)*3 + 1] == 0)  
                            {
                                connections.push_back(n);
                            }
                        leftnode->neighbours[1] = n;
                        n->neighbours[3] = leftnode;
                        leftnode = nullptr;
                    }
                }
                else
                {
                    if(nxt)
                    {
                       
                        n = new Node(i,j,noOfNodes);
                        nodeList.push_back(n);
                        if(image.data[(rowOffset + i)*3 + 1] == 0) 
                            {
                                connections.push_back(n);
                            }
                        leftnode = n;
                    }
                    else
                    {
                        
                        if((image.data[(rowAboveOffset + i)*3] == 0) || (image.data[(rowBelowOffset + i)*3] == 0))
                        {
                            n = new Node(i,j,noOfNodes);
                            nodeList.push_back(n);
                        if(image.data[(rowOffset + i)*3 + 1 ] == 0) 
                            {
                                connections.push_back(n);
                            }
                        }
                    }
                }
                 if (n != nullptr)
                  {
                        if (image.data[(rowAboveOffset + i)*3] != 0)
                        {
                            t = topNodes[i];
                            t->neighbours[2] = n;
                            n->neighbours[0] = t;

                        }

                        
                        if (image.data[(rowBelowOffset + i)*3] != 0)
                        {
                            topNodes[i] = n;
                        }
                        else
                        {
                            topNodes[i] = nullptr;
                        }
                        noOfNodes += 1;
                    }

            } 

        }

        j=height - 1;
        i=1;
        while(image.data[(j*width + i)*3] ==0)
        {
            i=i+1;
        }
        ENode = new Node(i,j,noOfNodes);
        nodeList.push_back(ENode);
        connections.push_back(ENode);
        t = topNodes[i];
        t->neighbours[2] = ENode;
        ENode->neighbours[0] = t;
        noOfNodes += 1;
        
    }
    int printSolution()
    {
        int curX,curY,nxtX,nxtY;
        int noOfOnes=0;
        std::vector<int>::iterator itr=path.begin();
        while(1)
        {
            curX=nodeList[*itr]->x;
            curY=nodeList[*itr]->y;
            image.data[  ( width * curY +  curX)*3 + 1  ]=255;
            noOfOnes+=1;
            if(nodeList[*itr]==SNode)
            {
                break;
            }
            itr++;
            nxtX=nodeList[*itr]->x;
            nxtY=nodeList[*itr]->y;
            if(curX>nxtX)// moving nxtX is left of curX
            {
                while(curX!=nxtX)
                {
                    image.data[  ( width * curY +  curX)*3 ]=0;
                    image.data[  ( width * curY +  curX)*3 + 2 ]=0;
                    noOfOnes+=1;
                    curX-=1;
                }
            }
            else//rights
            {
                 while(curX!=nxtX)
                {
                    image.data[  ( width * curY +  curX)*3 ]=0;
                    image.data[  ( width * curY +  curX)*3 + 2 ]=0;
                    noOfOnes+=1;
                    curX+=1;
                }
            }
            if(curY>nxtY)//i.e. nxtY is below of curY
            {
                while(curY!=nxtY)
                {
                    image.data[  ( width * curY +  curX)*3 ]=0;
                    image.data[  ( width * curY +  curX)*3 + 2 ]=0;
                    noOfOnes+=1;
                    curY-=1;
                }
            }
            else//above
            {
                 while(curY!=nxtY)
                {
                    image.data[  ( width * curY +  curX)*3 ]=0;
                    image.data[  ( width * curY +  curX)*3 + 2 ]=0;
                    noOfOnes+=1;
                    curY+=1;
                }
            }
        }
        for(std::vector<Node*>::iterator itr=connections.begin();itr!=connections.end();itr++)
        {
            image.data[ (  width * (*itr)->y +  (*itr)->x )*3 + 1 ]=0;
            image.data[ (  width * (*itr)->y +  (*itr)->x )*3 + 2 ]=0;
            image.data[ (  width * (*itr)->y +  (*itr)->x )*3 ]=255;
        }

    cv::namedWindow("Maze with Route", CV_WINDOW_NORMAL);

    
    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    cv::imwrite("result/#solved.png", image, compression_params);
    cv::imshow("Maze with Route", image);
    
    cv::waitKey(0); 
    
    cv::destroyWindow("Maze with Route");            

        return noOfOnes;
    }
    void dfs();
    void dfs(Node*,Node*);
    void bfs();
    void bfs(Node*,Node*);
    int getdistance(int,int);
    float getVirtualDist(int);
    

};

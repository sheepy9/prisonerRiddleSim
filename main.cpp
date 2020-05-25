#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_BOXES 100
#define MAX_PICKS 50

int myrandom (int i) { return std::rand()%i;}

std::vector<int> generateArray()
{
    //randomize seed
    std::vector<int> boxes;
    for(int i=1; i<=MAX_BOXES; i++)
        boxes.push_back(i);

    //do 100,000 swaps

    std::random_shuffle(boxes.begin(), boxes.end(), myrandom);
    /*
    for(int i=0; i<1000; i++)
    {
        int first = rand()%100;
        int second = rand()%100;

        int t = boxes[first];
        boxes[first] = boxes[second];
        boxes[second] = t;
    }
    */

    return boxes;
}

bool vectorContentCheck(std::vector<int> loopList, int x) 
{
    if(std::find(loopList.begin(), loopList.end(), x) != loopList.end())
        return true;
    return false;
}

bool vectorContentCheck(std::vector<std::vector<int>> loopList, int x) 
{
    for(int i=0; i<loopList.size(); i++)
        if(std::find(loopList[i].begin(), loopList[i].end(), x) != loopList[i].end())
            return true;
    return false;
}

std::vector<std::vector<int>> countLoops(std::vector<int> boxes)
{
    std::vector<std::vector<int>> loopList;
    loopList.push_back(*(new std::vector<int>()));

    for(int i=0; i<MAX_BOXES; i++)
    {
        std::vector<int> tempLoop;
        int currentNumber = boxes[i];
        if(vectorContentCheck(loopList, currentNumber))
            continue;
        while(true)
        {
            currentNumber = boxes[currentNumber-1];
            if(vectorContentCheck(tempLoop, currentNumber))
                break;
            else
                tempLoop.push_back(currentNumber);
        }
        if(!tempLoop.empty())
            loopList.push_back(tempLoop);
    }

    loopList.erase(loopList.begin(), loopList.begin()+1);
    std::cout << "Loops are: " << std::endl;
    for(int i=0; i<loopList.size(); i++)
    {
        std::cout << "Loop no. " << i << " with size " << loopList[i].size() << ": ";
        if(!loopList[i].empty())
            for(int j=0; j<loopList[i].size(); j++)
                std::cout << loopList[i][j] << ", ";
        std::cout << std::endl;
    }

    std::cout << "LoopList size is " << loopList.size();


    return loopList;
}

bool traverseLoopList(std::vector<int> boxes)
{
    bool success = true;
    for(int prisonNo = 1; prisonNo<=MAX_BOXES; prisonNo++)
    {
        int guess = prisonNo;
        int guessCount = 0;
        for(int count=1; count<=MAX_PICKS; count++)
        {
            guessCount++;
            if(boxes[guess-1] == prisonNo)
            {
                guessCount--;
                break;
            }
            else
                guess = boxes[guess-1];
        }
        if(guessCount>=MAX_PICKS)
            success = false;
    }

    return success;
}

int main()
{
    srand((unsigned)time(0)); 
    int success = 0;
    int totalTests = 100000;
    for(int i=1; i<=totalTests; i++)
    {
        std::vector<int> boxes = generateArray();

        
        /*
        for(int i=0; i<MAX_BOXES; i++)
            std::cout << i+1 << ": " << boxes[i] << std::endl;
        std::cout << std::endl;
        */
        

        if(traverseLoopList(boxes))
            success++;

        //std::vector<std::vector<int>> loopList = countLoops(boxes);
        std::cout << "Success rate: " << 100*success/totalTests << "%";
        std::cout << "Num of successes: " << success << "; Num of iterations: " << i << std::endl;
    }

    
    return 0;
}

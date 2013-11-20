#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

string database = "AACCTGACATCTT";
string query = "CCAGCGTCAACTT";



double substitution_matrix[4][4] = {{1.0,-0.1,-0.1,-0.15},
                                    {0,1.0,-0.15,-0.1},
                                    {0,0,1.0,-0.1},
                                    {0,0,0,1.0}};

double score(char x, char y, bool gap)
{
    int xIndex, yIndex;
    if (x == 'A')
        xIndex = 0;
    else if (x == 'G')
        xIndex = 1;
    else if (x == 'C')
        xIndex = 2;
    else if (x == 'T')
        xIndex = 3;
        
    if (y == 'A')
        yIndex = 0;
    else if (y == 'G')
        yIndex = 1;
    else if (y == 'C')
        yIndex = 2;
    else if (y == 'T')
        yIndex = 3;
            
    return substitution_matrix[yIndex][xIndex];
}

double MaxScore(int dIndex, int qIndex, bool gap)
{
    if(dIndex == database.length() - 1 || qIndex == query.length() - 1)
    {
        return score(database.at(database.length() - 1), query.at(query.length() - 1), gap);
    }
    
    double regScore = score(database.at(dIndex), query.at(qIndex), gap);
    double gapScore = (gap ? -0.2 : -0.05);
    
    return max( gapScore + MaxScore(dIndex, qIndex + 1, true), max( gapScore + MaxScore(dIndex + 1, qIndex, true),  regScore + MaxScore(dIndex + 1, qIndex + 1, false) ) );
    
}

int main(int argc, char* argv[])
{
    cout << "Score: " << MaxScore(0,0, false);
}

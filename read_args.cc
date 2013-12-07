#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
string databaseFile;
string queryFile;
string numbSequences = "100"; //Default # of sequences if not specified
string alignment = "1"; //Default if not specified
string scoringFile;

vector<string> formattedArgs;
int main(int argc, char * argv[])
{
    for(int i = 0; i < argc; ++i)
    {
        if(argv[i][0] == 'd')
        {
            databaseFile = argv[i+2];
            i = i + 2;
        }
        else if(argv[i][0] == 'q')
        {
            queryFile = argv[i+2];
            i = i + 2;
        }
        else if(argv[i][0] == 'n')
        {
            numbSequences = argv[i+2];
            i = i + 2;
        }
        else if(argv[i][0] == 'a')
        {
            alignment = argv[i+2];
            i = i + 2;
        }
        else if(argv[i][0] == 's')
        {
            scoringFile = argv[i+2];
            i = i + 2;
        }
    }
    
    //Verification
    cout << "Database File: " << databaseFile << endl;
    cout << "Query File: " << queryFile << endl;
    cout << "Number of Sequences: " << numbSequences << endl;
    cout << "Alignment: " << alignment << endl;
    cout << "Scoring File: " << scoringFile << endl;
    
    //Scoring Matrix Verification
    ifstream scoreFile;
    scoreFile.open(scoringFile);
    double scoringMatrix[4][4];
    string read;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            scoreFile >> read;
            scoringMatrix[j][i] = atof(read.c_str());
            cout << read << " ";
        }
        cout << endl;
    }
    
    /*
     * In our main program we'd use these strings(databaseFile, queryFile, etc)
     * to open the correct file or set the correct number of Sequences
    */
    
    
    
}

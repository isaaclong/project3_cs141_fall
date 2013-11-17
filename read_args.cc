#include <iostream>
#include <vector>

using namespace std;
string databaseFile;
string queryFile;
string numbSequences = "100"; //Default # of sequences if not specified
string alignment = "1"; //Default if not specified
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
    }
    
    //Verification
    cout << "Database File: " << databaseFile << endl;
    cout << "Query File: " << queryFile << endl;
    cout << "Number of Sequences: " << numbSequences << endl;
    cout << "Alignment: " << alignment << endl;
    
    /*
     * In our main program we'd use these strings(databaseFile, queryFile, etc)
     * to open the correct file or set the correct number of Sequences
    */
    
    
    
}

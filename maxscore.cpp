#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "node.cpp"

using namespace std;

string database = "AACCTGACATCTT";
string query = "CCAGCGTCAACTT";



double substitution_matrix[4][4] = {{1.0,-0.1,-0.1,-0.15},
                                    {-0.1,1.0,-0.15,-0.1},
                                    {-0.1,-0.15,1.0,-0.1},
                                    {-0.15,-0.1,-0.1,1.0}};

Node empty_cell(-999, pair<int,int>(-1,-1), false);

vector<Node> empty_col(query.size(), empty_cell);

vector< vector<Node> > calc_table(database.size(), empty_col);

double score(char x, char y)
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

double iterative_MaxScore(const string &ref, const string &query)
{
    
    calc_table[0][0] = Node( 0, pair<int,int>(0, -1), false );
    calc_table[1][0] = Node( score(ref[0], query[0]) - 0.2, pair<int,int>(0, 0), true );
    calc_table[0][1] = Node( 0, pair<int,int>(0, 0), true );
    
    
    //Generate the zero column
    for (int i = 2; i < calc_table[0].size(); i++)
    {
        calc_table[0][i] = Node( 0, pair<int,int>(0,i-1), true);
    }
    
    //Generate the zero row
    for (int i = 2; i < calc_table.size(); i++)
    {
        calc_table[i][0] = Node( calc_table[i-1][0].score - 0.05 , pair<int,int>(i-1,0), true);
    }
    
    //Make calculations
    //i: database
    //j: query
    for (int i = 1; i < calc_table.size(); i++)
    {
        for (int j = 1; j < calc_table[i].size(); j++)
        {
            double gap_value_insertion = calc_table[i-1][j].gap ? -0.05 : -0.2;
            double gap_value_deletion = calc_table[i][j-1].gap ? -0.05 : -0.2;
            //double current_score = score(ref.at(i), query.at(j), false);
            
            double insertion = calc_table[i-1][j].score + gap_value_insertion;
            double deletion = calc_table[i][j-1].score + gap_value_deletion;
            double substitution = calc_table[i-1][j-1].score + score(ref.at(i), query.at(j));
            
            if (deletion >= insertion && deletion >= substitution)
            {
                Node cell(deletion, pair<int,int>(i, j-1), true );
                calc_table[i][j] = cell;
            }
            else if ( insertion >= deletion && insertion >= substitution)
            {
                Node cell(insertion, pair<int,int>(i-1, j), false);
                calc_table[i][j] = cell;
            }
            
            else 
            {
                Node cell(substitution, pair<int,int>(i-1, j-1), true);
                calc_table[i][j] = cell;
            }
        }
    }
    return calc_table[database.size()-1][query.size()-1].score;
}

double MaxScore(int dIndex, int qIndex, bool gap)
{
    if(dIndex == database.length() - 1 || qIndex == query.length() - 1)
    {
        return score(database.at(database.length() - 1), query.at(query.length() - 1));
    }
    
    double regScore = score(database.at(dIndex), query.at(qIndex));
    double gapScore = (gap ? -0.05 : -0.2);
    
    double deletion = gapScore + MaxScore(dIndex, qIndex + 1, true);
    double insertion = gapScore + MaxScore(dIndex + 1, qIndex, true);
    double substitution = regScore + MaxScore(dIndex + 1, qIndex + 1, false);
    
    //cout << "__" << ", " <<  query[qIndex] << " " << deletion << endl;
    //cout << database[dIndex] << ", " << "__" << " " << insertion << endl;
    //cout << database[dIndex] << ", " <<  query[qIndex] << " " << substitution << endl;
    
    
    return max( deletion, max( insertion,  substitution) );
    
}

int main(int argc, char* argv[])
{
    //cout << "Score: " << MaxScore(0,0, false) << endl;
    cout << "DATABASE: " << database << endl;
    cout << "QUERY: " << query << endl;
    iterative_MaxScore(database, query);
    for(int i = 0; i < calc_table.size(); ++i)
    {
        for(int e = 0; e < calc_table[i].size(); ++e)
        {
            cout << setw(7) <<  calc_table[i][e].score << " <--(" << calc_table[i][e].max_previous_index.first << "," << calc_table[i][e].max_previous_index.second << ")";
        }
        cout << endl << endl;
    }
    
    //cout << calc_table[database.size()-1][query.size()-1].score << endl;
}

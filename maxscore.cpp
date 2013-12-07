#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "node.cpp"

using namespace std;

//string database = "AACCTGACATCTT";
//string query = "CCAGCGTCAACTT";

/*
  
Now main gets the query string and database string from the input 
files that Nick gave us. It reads in only the first organism from the 
database file for testing, and gets a score of -524. I am not sure if this 
is correct or not. I have a test in place that just sets the database string
to be equal to the query string, so that the score should just be the length
of the query string (300). We get 299, with a small error on the top 
left node as can be seen in the alignment print out. I think the next
step towards confirming or denying the -524 score is testing it with 
query and database strings of differing lengths, as this could very well 
be where our error is if the calculation is off.  
    
*/


double substitution_matrix[4][4] = {{1.0,-0.1,-0.1,-0.15},
                                    {-0.1,1.0,-0.15,-0.1},
                                    {-0.1,-0.15,1.0,-0.1},
                                    {-0.15,-0.1,-0.1,1.0}};

Node empty_cell(-999, pair<int,int>(-1,-1), false);

//vector<Node> empty_col(query.size(), empty_cell);

//vector< vector<Node> > calc_table(database.size(), empty_col);

//Function to reverse a string in place
string string_reverse(string &str)
{
    for(int i = 0, e = str.size() - 1; i <= str.size() /2 && e >= str.size() / 2; ++i, --e)
    {
        char temp = str[i];
        str[i] = str[e];
        str[e] = temp;
    }
    return str;
}

//Print colored alignments of database alignment and query alignment
//Green: Matching substitution
//Red: Mismatching substitution
//Blue: Insertion or Deletion
void print_colored_alignments(string &database_alignment, string &query_alignment)
{
    for(int i = 0; i < database_alignment.size(); ++i)
    {
        //Insertion or Deletion
        if(database_alignment[i] == '_' || query_alignment[i] == '_')
        {
            cout << "\033[34m" << database_alignment[i] << "\033[0m";
        }
        //Matching Substitution
        else if(database_alignment[i] == query_alignment[i])
        {
            cout << "\033[32m" << database_alignment[i] << "\033[0m";
        }
        //Mis-matching substitution
        else
        {
            cout << "\033[31m" << database_alignment[i] << "\033[0m";
        }
    }
    cout << endl << endl << endl;
    for(int i = 0; i < query_alignment.size(); ++i)
    {
        //Insertion or Deletion
        if(database_alignment[i] == '_' || query_alignment[i] == '_')
        {
            cout << "\033[34m" << query_alignment[i] << "\033[0m";
        }
        //Matching Substitution
        else if(database_alignment[i] == query_alignment[i])
        {
            cout << "\033[32m" << query_alignment[i] << "\033[0m";
        }
        //Mis-matching substitution
        else
        {
            cout << "\033[31m" << query_alignment[i] << "\033[0m";
        }
    }
    cout << endl;
    
}

//Print most optimal alignment given memoization table
// now passing in database size and query size 
void print_alignment(vector< vector<Node> > &calc_table, string database, string query)
{
    int i = database.size() - 1, j = query.size() - 1;
    int e, y;
    string database_alignment, query_alignment;
    Node final_node = calc_table[i][j];
    //Node prev_node = calc_table[final_node.max_previous_index.first][final_node.max_previous_index.second];
    while(i >= 0 && j >= 0)
    {
        e = final_node.max_previous_index.first;
        y = final_node.max_previous_index.second;
        if(i - 1 == e && j - 1 == y)
        {
            database_alignment.push_back(database[i]);
            query_alignment.push_back(query[j]);
            --i;
            --j;
        }
        
        else if(i - 1 == e & j == y)
        {
            //add space into query
            database_alignment.push_back(database[i]);
            query_alignment.push_back('_');
            --i;
        }
            
        else
        {   
            //add space to database
            database_alignment.push_back('_');
            query_alignment.push_back(query[j]);
            --j;
        }
        final_node = calc_table[i][j];
    }
    //Alignments are in reverse at this point, reverse them to get actual alignment
    string_reverse(database_alignment);
    string_reverse(query_alignment);
    
    //Color terminal output of alignments for easier readability
    print_colored_alignments(database_alignment, query_alignment);
}

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

//Generate memoization table
//now passing in calc_table as parameter
double iterative_MaxScore(const string &ref, const string &query,
                            vector< vector<Node> > &calc_table)
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
            
            double gap_value_deletion = calc_table[i][j-1].gap ? -0.05 : -0.2;
            double gap_value_insertion;
            if(j == query.size() - 1 && i > query.size()-1)
            {
                gap_value_insertion = 0;
            }
            else
            {
                gap_value_insertion = calc_table[i-1][j].gap ? -0.05 : -0.2;
            }
            
            
            
            //double current_score = score(ref.at(i), query.at(j), false);
            
            double insertion = calc_table[i-1][j].score + gap_value_insertion;
            double deletion = calc_table[i][j-1].score + gap_value_deletion;
            double substitution = calc_table[i-1][j-1].score + score(ref.at(i), query.at(j));
            
            
            if(substitution >= insertion && substitution >= deletion)
            {
                Node cell(substitution, pair<int,int>(i-1, j-1), false);
                calc_table[i][j] = cell;
            }
            else if (deletion >= insertion && deletion >= substitution)
            {
                Node cell(deletion, pair<int,int>(i, j-1), true );
                calc_table[i][j] = cell;
            }
            else if ( insertion >= deletion && insertion >= substitution)
            {
                Node cell(insertion, pair<int,int>(i-1, j), true);
                calc_table[i][j] = cell;
            }

        }
    }
    //return calc_table[database.size()-1][query.size()-1].score;
    return calc_table[ref.size()-1][query.size()-1].score;
}

/*
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
*/

int main(int argc, char* argv[])
{
    /*
     * Add the code here to read 
     * arguments(input/output files, alignment, and number of sequences)
    */
     
    ifstream in;
    
    // input file name hardcoded for now, if need to use a string use .open(filename.c_str());
    in.open("input.txt");
    string testQuery;
    getline(in, testQuery);
    in.close();

    cout << endl << endl;

    in.open("chromosomes-small.txt");
    string testDatabase;
    //for(int i = 0; i < 2; i++)
    //{
        //in >> test;
        getline(in, testDatabase); // first line is info line
        getline(in, testDatabase);
    //}
    in.close();        

    //----------------------------------------

    // ADDED FOR TESTING
    testDatabase = testQuery;
    testDatabase.push_back('A');

    //cout << "DATABASE: " << database << endl;
    //cout << "   QUERY: " << query << endl;

    cout << "Real database test" << endl << endl 
         << "testDatabase: " << endl << endl << testDatabase << endl << endl
         << "testQuery: " << endl << endl << testQuery << endl << endl;
    
    //vector<Node> empty_col(query.size(), empty_cell);
    //vector< vector<Node> > calc_table(database.size(), empty_col);

    vector<Node> empty_col(testQuery.size(), empty_cell);
    vector< vector<Node> > calc_table(testDatabase.size(), empty_col);

    iterative_MaxScore(testDatabase, testQuery, calc_table);

    //iterative_MaxScore(database, query);
    
    //----------------------------------------

    /*
    for(int i = 0; i < calc_table.size(); ++i)
    {
        for(int e = 0; e < calc_table[i].size(); ++e)
        {
            cout << setw(7) <<  calc_table[i][e].score << " <--(" << calc_table[i][e].max_previous_index.first << "," << calc_table[i][e].max_previous_index.second << ")";
        }
        cout << endl << endl;
    }
    */

    //----------------------------
    

    //print_alignment(calc_table);
    print_alignment(calc_table, testDatabase, testQuery);
    
    //cout << "Score: " << calc_table[database.size()-1][query.size()-1].score << endl;
    cout << "Score: " << calc_table[testDatabase.size()-1][testQuery.size()-1].score << endl;
    cout << "Query Size: " << testQuery.size() << endl;

    //----------------------------

    
}

#include <utility>

using namespace std;
class Node
{
    public:
    double score;
    pair<int, int> max_previous_index;
    bool gap;
    
    Node(double curr_score, pair<int,int> max_prev_index, bool Gap)
    :score(curr_score), max_previous_index(max_prev_index), gap(Gap)
    {}
    
    
};

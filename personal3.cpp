#include <iostream>
#include <string>
#include <istream>
#include <sstream>
#include <ostream>
#include <fstream>
#include <cmath>

using namespace std;

class PopularVoteData
{
    public:
        double find_obama_percent_per_state(int, int);
        double find_romney_percent_per_state(int, int);
        friend istream &operator >> (istream &input, PopularVoteData &data)
        {
            input >> data.pop_obama >> data.pop_romney >> data.pop_other
                  >> data.total_pop_vote;
            getline(input, data.state_name);
        }
    private:
        int pop_obama,
            pop_romney,
            pop_other,
            total_pop_vote,
            running_count_total_pop_vote,
            obama_running_count_total_pop_vote,
            romney_running_count_total_pop_vote,
            num_rows;
        char buffer[1000];
        string state_name;
        double  obama_percent_per_state;
        double  romney_percent_per_state;

};

double find_romney_percent_per_state(int pop_romney, int total_pop_vote)
{
    romney_percent_per_state = (double(pop_romney)/double(total_pop_vote))*100;
    return romney_percent_per_state;
}

double find_obama_percent_per_state(int pop_obama, int total_pop_vote)
{
   obama_percent_per_state = (double(pop_obama)/double(total_pop_vote))*100;
   return obama_percent_per_state;
}

int main()
{
    ifstream input("elect12.csv");
}

#include <iostream>
#include <string>
#include <istream>
#include <sstream>
#include <ostream>
#include <fstream>

using namespace std;

class PopularVoteData
{
    private:
        int pop_obama,
            pop_romney,
            pop_other,
            total_pop_vote,
            running_count_total_pop_vote = 0,
            obama_running_count_total_pop_vote = 0,
            romney_running_count_total_pop_vote = 0,
            num_rows = 0;
        char buffer[1000];

    friend istream &operator >> (istream &input, PopularVoteData &data);


};

istream &operator >> (istream &input, PopularVoteData &data)
{
while (input.getline(buffer, 1000))
  {
    num_rows++;

    istringstream buffer_stream(buffer);
    buffer_stream >> pop_obama >> pop_romney >> pop_other >> total_pop_vote
                  >> state_name;

    running_count_total_pop_vote += total_pop_vote;
    obama_running_count_total_pop_vote += pop_obama;
    romney_running_count_total_pop_vote += pop_romney;

    obama_percent_per_state = (double(pop_obama)/double(total_pop_vote))*100;
    romney_percent_per_state = (double(pop_romney)/double(total_pop_vote))*100;
    state_margin_of_victory =  (obama_percent_per_state - romney_percent_per_state);
    running_total_margin_victory += state_margin_of_victory;

    if (obama_best_margin < state_margin_of_victory){
        obama_best_margin = state_margin_of_victory;
        obama_best_state = state_name;
      }

    if (obama_worst_margin > state_margin_of_victory){
        obama_worst_margin = state_margin_of_victory;
        obama_worst_state = state_name;
      }

    if (romney_best_margin < state_margin_of_victory){
       romney_best_margin = state_margin_of_victory;
       romney_best_state = state_name;
    }

    if (romney_worst_margin > state_margin_of_victory){
       romney_worst_margin = state_margin_of_victory;
       romney_worst_state = state_name;
    }

    if (pop_obama > pop_romney)
      obama_states += state_name + " ";
    else
      romney_states += state_name + " ";
  }

    highest_margin_victory = obama_best_margin;
    lowest_margin_victory = obama_worst_margin;
    average_victory_margin = ((running_total_margin_victory)/num_rows);

    obama_percent_total_pop_vote =
(double(obama_running_count_total_pop_vote)/double(running_count_total_pop_vote))*100;

romney_percent_total_pop_vote =
(double(romney_running_count_total_pop_vote)/double(running_count_total_pop_vote))*100;

margin_of_victory = (obama_percent_total_pop_vote) -
                    (romney_percent_total_pop_vote);
}

int main()
{
    ifstream input("elect12.csv");
}

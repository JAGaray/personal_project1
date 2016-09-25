#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
  // input file
  // elect12.csv
  // popular vote for obama, popular vote for romney, popular vote for other candidates, state name
  // int int int int string
  //
  char buffer[1000];
  int pop_obama,
      pop_romney,
      pop_other,
      total_pop_vote;
  string state_name;
  ifstream in("elect12.csv");

  int running_count_total_pop_vote = 0,
      obama_running_count_total_pop_vote = 0,
      romney_running_count_total_pop_vote = 0;

  int num_electoral_votes,
      total_winning_electoral_votes = 0;
  string state_abbrev;
  double popular_vote_percentage,
         margin_of_victory,
         average_victory_margin,
         highest_margin_victory,
         lowest_margin_victory;
  string list_of_state_codes ="";
  string winning_candidate;
  string obama_best_state;
  string obama_worst_state;
  string romney_best_state;
  string romney_worst_state;
  string obama_states = "";
  string romney_states = "";
  string winner_best_state;
  string winner_worst_state;
  double obama_best_margin = 0,
         obama_worst_margin = 0,
         romney_best_margin = 0,
         romney_worst_margin = 0;
  double running_total_margin_victory = 0;
  double state_margin_of_victory = 0;
  int num_rows = 0;

  while (in.getline(buffer, 1000))
  {
    num_rows++;

    istringstream buffer_stream(buffer);
    buffer_stream >> pop_obama >> pop_romney >> pop_other >> total_pop_vote
                  >> state_name;
    // cout << pop_obama << pop_romney << pop_other << total_pop_vote
    //      << state_name << endl;
    running_count_total_pop_vote += total_pop_vote;
    obama_running_count_total_pop_vote += pop_obama;
    romney_running_count_total_pop_vote += pop_romney;

    double obama_percent_per_state = (double(pop_obama)/double(total_pop_vote))*100;
    double romney_percent_per_state = (double(pop_romney)/double(total_pop_vote))*100;
    state_margin_of_victory =  (obama_percent_per_state - romney_percent_per_state);
    // cout << state_margin_of_victory << endl;
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
  //
  // cout << obama_states << endl;
  // cout << romney_states << endl;

  double obama_percent_total_pop_vote,
         romney_percent_total_pop_vote;

obama_percent_total_pop_vote =
(double(obama_running_count_total_pop_vote)/double(running_count_total_pop_vote))*100;

romney_percent_total_pop_vote =
(double(romney_running_count_total_pop_vote)/double(running_count_total_pop_vote))*100;

margin_of_victory = (obama_percent_total_pop_vote) -
                    (romney_percent_total_pop_vote);
  // input file
  // ev10.csv
  // number of electoral college votes, stat name
  // int string

int obama_electoral_running_count = 0,
    romney_electoral_running_count = 0;



  ifstream ev10("ev10.csv");
  while (ev10.getline(buffer, 1000))
  {
    istringstream buffer_stream(buffer);

    buffer_stream >> num_electoral_votes >> state_abbrev;
    //
    size_t found = obama_states.find(state_abbrev);
    if (found != string::npos)
      obama_electoral_running_count += num_electoral_votes;
    else romney_electoral_running_count += num_electoral_votes;
    // cout << num_electoral_votes << state_abbrev << endl;
    list_of_state_codes += state_abbrev + " ";
  }
    if (obama_electoral_running_count > romney_electoral_running_count) {
      total_winning_electoral_votes = obama_electoral_running_count;
      winning_candidate = "Barack HUSSEIN Obama";
      winner_best_state = obama_best_state;
      winner_worst_state = obama_worst_state;
      popular_vote_percentage = obama_percent_total_pop_vote;
        }
    else {
      total_winning_electoral_votes = romney_electoral_running_count;
      winning_candidate = "Willard Mitt Romney";
      winner_best_state = romney_best_state;
      winner_worst_state = romney_worst_state;
      popular_vote_percentage = romney_percent_total_pop_vote;
        }


  cout << winning_candidate
       << " won the national election with "
       << popular_vote_percentage
       << "% of the popular vote and a margin of  "
       << margin_of_victory
       << " points." << endl;
  cout << winning_candidate << " received " << total_winning_electoral_votes
       << " electoral votes." << endl;
  cout << winning_candidate << " had an unweighted average victory margin of "
       << average_victory_margin << " points." << endl;
  cout << winning_candidate << " best state was " << winner_best_state
       << ", where he won by " << highest_margin_victory << " points." << endl;
  cout << winning_candidate << " worst state was " << winner_worst_state
       << ", where he lost by " << lowest_margin_victory << " points." << endl;







int num_of_states;
string state_codes = "";
string region = "";

  do {
    cout << "How many states would you like to check?" << endl;
    cin >> num_of_states;
    if (num_of_states < 0)
    cout << "Please enter a positive number." << endl;
  } while(num_of_states < 0);

  for (int i = 0; i < num_of_states; i++){
    cout << "Please enter one of the code(s) of the state(s) you would like to check." << endl;
    cin >> state_codes;
    region += state_codes + " ";

    size_t found = list_of_state_codes.find(state_codes);
    if (found == string::npos){
      cout << state_codes << " is not a legal state." << endl;
      i = -1;
      region = "";
    }
  }

int running_count_region_pop_vote = 0,
    running_count_region_obama_pop_vote = 0,
    running_count_region_romney_pop_vote = 0;

  in.clear();
  in.seekg(0, ios::beg);
  while (in.getline(buffer, 1000))
  {
    istringstream buffer_stream(buffer);
    buffer_stream >> pop_obama >> pop_romney >> pop_other >> total_pop_vote
                  >> state_name;
    size_t found = region.find(state_name);
    if (found != string::npos){
      running_count_region_pop_vote += total_pop_vote;
      running_count_region_obama_pop_vote += pop_obama;
      running_count_region_romney_pop_vote += pop_romney;
    }
  }

  double obama_percent_region_pop_vote = 0,
         romney_percent_region_pop_vote = 0;
        //  region_margin_of_victory
  obama_percent_region_pop_vote = (double(running_count_region_obama_pop_vote)/
                                   double(running_count_region_pop_vote))*100;
  romney_percent_region_pop_vote = (double(running_count_region_romney_pop_vote)/
                                    double(running_count_region_pop_vote))*100;
  double region_margin_of_victory;
  if (obama_percent_region_pop_vote > romney_percent_region_pop_vote){
    region_margin_of_victory = (obama_percent_region_pop_vote) -
                                romney_percent_region_pop_vote;
    cout << "Obama won the popular vote by " << region_margin_of_victory <<
            " points in the region." << endl;
  }
  else{
    region_margin_of_victory = romney_percent_region_pop_vote -
                                obama_percent_region_pop_vote;
    cout << "Romney won the popular vote by " << region_margin_of_victory <<
            " points in the region." << endl;
  }



  return 0;
}

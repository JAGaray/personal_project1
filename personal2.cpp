#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    char buffer[1000];
    int num_rows,
        pop_obama,
        pop_romney,
        pop_other,
        total_pop_vote,
        running_count_total_pop_vote,
        obama_running_count_total_pop_vote,
        romney_running_count_total_pop_vote,
        num_of_states,
        running_count_region_pop_vote = 0,
        running_count_region_obama_pop_vote = 0,
        running_count_region_romney_pop_vote = 0;
    double obama_percent_per_state,
           romney_percent_per_state,
           state_margin_of_victory,
           running_total_margin_victory,
           obama_percent_region_pop_vote,
           romney_percent_region_pop_vote,
           region_margin_of_victory;
    string state_name;
    string obama_states = "";
    string romney_states = "";
    string state_codes = "";
    string region = "";
    string list_of_state_codes = "";


    ifstream in("elect12.csv");

  while (in.getline(buffer, 1000))
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

    list_of_state_codes += state_name;

    if (pop_obama > pop_romney)
      obama_states += state_name + " ";
    else
      romney_states += state_name + " ";
  }
do {
    cout << "How many states would you like to check?" << endl;
    cin >> num_of_states;
    if (num_of_states < 0)
    cout << "Please enter a positive number." << endl;
  } while(num_of_states < 0);

  for (int i = 0; i < num_of_states; i++){
    cout << "Please enter one of the code(s) of the state(s) you would like to check."
    << endl;
    cin >> state_codes;
    region += state_codes;

    size_t found = list_of_state_codes.find(state_codes);
    if (found == string::npos){
      cout << state_codes << " is not a legal state." << endl;
      i = -1;
      region = "";
    }
  }

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

  obama_percent_region_pop_vote = (double(running_count_region_obama_pop_vote)/
                                   double(running_count_region_pop_vote))*100;
  romney_percent_region_pop_vote = (double(running_count_region_romney_pop_vote)/
                                    double(running_count_region_pop_vote))*100;
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
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Statedata
{
public:
    Statedata(){}
    Statedata(int a, int s, int r, int d, string l){
        pop_obama = a;
        pop_romney = s;
        pop_other = r;
        total_pop_vote = d;
        state_name = l;
    }
    double state_margin_of_victory(){
        double obama_percent_per_state = (double(pop_obama)/double(total_pop_vote))*100;
        double romney_percent_per_state = (double(pop_romney)/double(total_pop_vote))*100;
        return (obama_percent_per_state - romney_percent_per_state);
    }

    bool obama_state(){
        return pop_obama > pop_romney;
    }

    bool romney_state(){
        return pop_obama < pop_romney;
    }
    string name(){
        return state_name;
    }
    int total_population_vote(){
        return total_pop_vote;
    }
    int pop_vote_obama(){
        return pop_obama;
    }
    int pop_vote_romney(){
        return pop_romney;
    }
    private:
        int pop_obama,
            pop_romney,
            pop_other,
            total_pop_vote;
        string state_name;

};

class Someshit{
    public:
    Someshit(const char* filename){
       ifstream input(filename);
       int i = 0;
       char buffer[1000];
       int a,b,c,d;
       obama_best_margin = 0;
       obama_worst_margin = 0;
       romney_best_margin = 0;
       romney_worst_margin = 0;
       string name;
       romney_best_state, romney_worst_state, obama_best_state, obama_worst_state = "";
        while (input.getline(buffer, 1000))
        {
            istringstream buffer_stream(buffer);
            buffer_stream >> a >> b >> c >> d
                          >> name;
            data[i] = Statedata(a,b,c,d,name);
            i++;
        }
        highest_margin();
        margin_of_victory();
    }

    void highest_margin(){
        for(int i = 0; i < 51; i++){
            if (obama_best_margin < data[i].state_margin_of_victory()){
                obama_best_margin = data[i].state_margin_of_victory();
                obama_best_state = data[i].name();
              }

            if (obama_worst_margin > data[i].state_margin_of_victory()){
                obama_worst_margin = data[i].state_margin_of_victory();
                obama_worst_state = data[i].name();
              }

            if (romney_best_margin < data[i].state_margin_of_victory()){
               romney_best_margin = data[i].state_margin_of_victory();
               romney_best_state = data[i].name();
            }

            if (romney_worst_margin > data[i].state_margin_of_victory()){
               romney_worst_margin = data[i].state_margin_of_victory();
               romney_worst_state = data[i].name();
            }

        }
    }

    double average_victory_margin(){
        double running_total_margin_victory= 0;
        for(int i = 0; i < 51; i++){
            running_total_margin_victory += data[i].state_margin_of_victory();
        }
        return((running_total_margin_victory)/51.0);
    }

    double margin_of_victory(){
        double obama_running_count_total_pop_vote = 0;
        double running_count_total_pop_vote = 0;
        double romney_running_count_total_pop_vote = 0;
         for(int i = 0; i < 51; i++){
             obama_running_count_total_pop_vote  += double(data[i].pop_vote_obama());
             running_count_total_pop_vote += double(data[i].total_population_vote());
             romney_running_count_total_pop_vote += double(data[i].pop_vote_romney());
         }
            obama_percent_total_pop_vote =
            (double(obama_running_count_total_pop_vote)/double(running_count_total_pop_vote))*100;

            romney_percent_total_pop_vote =
            (double(romney_running_count_total_pop_vote)/double(running_count_total_pop_vote))*100;
            return (obama_percent_total_pop_vote) -
                    (romney_percent_total_pop_vote);
    }

    string obama_states(){
        string states = "";
        for(int i = 0; i < 51; i++){
            if(data[i].obama_state())
                states += data[i].name() + " ";
        }
        return states;
    }

    string romney_states(){
        string states = "";
        for(int i = 0; i < 51; i++){
            if(data[i].romney_state())
                states += data[i].name() + " ";
        }
        return states;
    }

    string get_obama_best_state(){
            return obama_best_state;
    }

    string get_romney_best_state(){
            return romney_best_state;
    }
    string get_romney_worst_state(){
            return romney_worst_state;
    }

    string get_obama_worst_state(){
            return obama_worst_state;
    }

    double get_obama_best_margin(){
            return obama_best_margin;
    }

    double get_obama_worst_margin(){
            return obama_worst_margin;
    }


    double get_romney_best_margin(){
            return romney_best_margin;
    }

    double get_romney_worst_margin(){
            return romney_worst_margin;
    }

    double get_romney_percent_total_pop_vote(){
        return romney_percent_total_pop_vote;
    }
    double get_obama_percent_total_pop_vote(){
        return obama_percent_total_pop_vote;
    }

private:
    Statedata  data[51];
    double obama_best_margin, obama_worst_margin, romney_best_margin, romney_worst_margin, obama_percent_total_pop_vote, romney_percent_total_pop_vote;
    string romney_best_state, romney_worst_state, obama_best_state, obama_worst_state;
};
struct electoralcollege{
    int votes;
    string name;
};
class Someothershit{
public:
    Someothershit(const char* filename){
       ifstream input(filename);
       int i = 0;
       char buffer[1000];
        while (input.getline(buffer, 1000))
        {
            istringstream buffer_stream(buffer);
            buffer_stream >> data[i].votes >> data[i].name;
            i++;
        }
    }

    int obama_votes(string obama_states){
        int votes = 0;
        for(int i = 0; i < 51; i++){
            size_t found = obama_states.find(data[i].name);
            if (found != string::npos)
                votes += data[i].votes;
        }
        return votes;
    }

    int romney_votes(string romney_states){
        int votes = 0;
        for(int i = 0; i < 51; i++){
            size_t found = romney_states.find(data[i].name);
            if (found != string::npos)
                votes += data[i].votes;
        }
        return votes;
    }
private:
    electoralcollege data[51];
};

int main()
{
    int total_winning_electoral_votes;
    string winning_candidate, winner_best_state, winner_worst_state;
    double popular_vote_percentage, highest_margin_victory, lowest_margin_victory ;
    Someshit shit("elect12.csv");
    Someothershit othershit("ev10.csv");
    
    if (othershit.obama_votes(shit.obama_states()) > othershit.romney_votes(shit.romney_states())) {
      total_winning_electoral_votes = othershit.obama_votes(shit.obama_states());
      winning_candidate = "Barack Hussein Obama";
      winner_best_state = shit.get_obama_best_state();
      winner_worst_state = shit.get_obama_worst_state();
      popular_vote_percentage = shit.get_obama_percent_total_pop_vote();
      highest_margin_victory = shit.get_obama_best_margin();
      lowest_margin_victory = shit.get_obama_worst_margin();
    }
    else
    {
      total_winning_electoral_votes = othershit.romney_votes(shit.romney_states());
      winning_candidate = "Willard Mitt Romney";
      winner_best_state = shit.get_romney_best_state();
      winner_worst_state = shit.get_romney_worst_state();
      popular_vote_percentage = shit.get_romney_percent_total_pop_vote();
      highest_margin_victory = shit.get_romney_best_margin();
      lowest_margin_victory = shit.get_romney_worst_margin();
    }
    if (othershit.obama_votes(shit.obama_states()) == othershit.romney_votes(shit.romney_states())) {
      winning_candidate = "Barack Hussein Obama";
      cout << "The election resulted in a tie!" << endl;
     }
     else {
       cout << winning_candidate
            << " won the national election with "
            << popular_vote_percentage
            << "% of the popular vote and a margin of  "
            << shit.margin_of_victory()
            << " points." << endl;
     }

  cout << winning_candidate << " received " << total_winning_electoral_votes
       << " electoral votes." << endl;
  cout << winning_candidate << " had an unweighted average victory margin of "
       << shit.average_victory_margin() << " points.";
  cout << winning_candidate << " best state was " << winner_best_state
       << ", where he won by " << highest_margin_victory << " points." << endl;
  cout << winning_candidate << " worst state was " << winner_worst_state
         << ", where he lost by " << lowest_margin_victory << " points." << endl;




  return 0;
}

#include <smithers.h>
#include <m2pp.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

int main(int argc, char *argv[]) 
{
    std::string sender_id = "82209006-86FF-4982-B5EA-D1E29E55D481";

    if (argc != 6) {
        std::cerr << "Usage: " << argv[0] << " <number_of_bots> <no_of_tournaments> <chips> <big_blind> <hands_before_blind_doubles>"
                  << "\n\tExample: " << argv[0] << " 3 5 10000 200 20" << std::endl;
        return 1;
    }
    
    int bots = std::stoi(argv[1]);
    int tournaments = std::stoi(argv[2]);
    int chips = std::stoi(argv[3]); 
    int big_blind = std::stoi(argv[4]); 
    int raise_rate = std::stoi(argv[5]); 

    smithers::Smithers waylon_smithers;
    waylon_smithers.await_registered_players(bots, chips);

    std::string start_input;
    std::cout << "..continue?" << std::endl;
    std::cin >> start_input;

    for (int i=0; i<tournaments; i++){
        waylon_smithers.play_tournament(chips, big_blind, raise_rate);
        std::cout<<"---"<<std::endl;
    }

    return 0;
}

#include "game.h"

#include <random>
#include <iostream>
#include <sstream>



namespace {

} // close anon


namespace smithers{

const char Card::S[] = {"CDHS"};
const char Card::R[] = {"23456789TJQKA"};

std::ostream& operator<<(std::ostream& stream, const Card& card){
    stream << Card::R[card.rank] << Card::S[card.suit];
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Hand& hand){
    stream << "|"  << hand.card1 << " " << hand.card2 << "|" 
           << "s " << hand.seat << "|"
           << "p " << hand.in_play << "|"
           << "d " << hand.is_dealer << "|";
    return stream;
}

Json::Value& operator<<(Json::Value& j_val, const Hand& hand){
    std::ostringstream _;
    _ << hand;
    j_val = _.str();
    return j_val;
};

Json::Value& operator<<(Json::Value& j_val, const Card& card){
    std::ostringstream _;
    _ << card;
    j_val = _.str();
    return j_val;
};


Game::Game(){
    build_deck();
}


const std::vector<Hand>& Game::deal_hands(int number_of_players ){
    std::vector<Card> all_cards;
    for (int i=0; i< 2*number_of_players; i++){
        all_cards.push_back(deal_a_card());
    }

    for (int i=0; i<number_of_players; i++){
        Hand this_hand = {all_cards[i], all_cards[i+number_of_players], true, false, i};
        std::cout << this_hand << std::endl;
        m_hands.push_back(this_hand);
    }
    return m_hands;    
}

std::vector<Card> Game::deal_flop(){
    std::vector<Card> flop;
    burn_card(deal_a_card()); // burn 
    for (int i=0; i<3; i++){ // and turn 
        Card c = deal_a_card();
        m_table.push_back(c);
        flop.push_back(c);
    }
    return flop;
}

Card Game::deal_river(){

    burn_card(deal_a_card()); // burn 
    Card c = deal_a_card(); // and turn 
    m_table.push_back(c);

    return c;
}
Card Game::deal_turn(){
    return deal_river(); // code duplication is evil
}

const std::vector<Card>& Game::get_table(){
    return m_table;
};

const std::string Game::get_table_str(){
    std::ostringstream t;
    t << "| ";
    for (size_t i=0; i<m_table.size(); i++){
        t << m_table[i] << " ";
    }
    t << "|";
    return t.str();
}

void Game::burn_card(const Card c){
    m_burnt.push_back(c);
}

void Game::build_deck(){
    for (int i=0; i<52; ++i){
        const Card card = {(int) i/4, i % 4 }; 
        m_deck.push_back(card); 
    }
}

const Card Game::deal_a_card(){
    std::random_device gen;
    std::uniform_int_distribution<> dis(0, m_deck.size()-1);

    int card_no = dis(gen);

    const Card this_card(m_deck[card_no]);
    m_deck.erase(m_deck.cbegin() + card_no);

    return this_card;
}





} // close smithers
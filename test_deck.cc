// Copyright 2021 xqr98003. All rights reserved.

#include <random>
#include <iostream>
#include <algorithm>

#include "deck/deck.h"

bool descending(Card a, Card b) {
  return a > b;
}

int main(int argc, char* argv[]) {
  // seed random number generator
  std::random_device rd;
  std::mt19937 rng(rd());

  // create a deck
  Deck deck(&rng);
  // no need to explicitly call deck.shuffle(): constructor shuffles
  //   by default

  // deal a bridge hand
  std::array<std::vector<Card>, 4> hands;
  for (size_t i = 0; ; i++) {
    auto c = deck.deal_card();
    if (!c) break;

    size_t hand_i = i % hands.size();
    auto& hand = hands[hand_i];
    hand.push_back(*c);
  }

  // print the hand in conventional fashion
  std::string hand_names[4] = {
      "North", "West", "South", "East"
  };
  for (size_t hand_i = 0; hand_i < hands.size(); hand_i++) {
    auto& hand = hands[hand_i];
    std::sort(hand.begin(), hand.end(), descending);

    std::cout << hand_names[hand_i] << ":" << std::endl;
    for (Suit suit = 4; suit-- > 0;) {
      std::cout << "  " << Deck::get_suit_name(suit) << " : ";

      size_t cards_in_suit = 0;
      for (auto card : hand) {
        if (Deck::get_suit(card) == suit) {
          std::cout << Deck::get_rank_name(Deck::get_rank(card)) << " ";
          cards_in_suit++;
        }
      }
      if (cards_in_suit == 0) {
        std::cout << "void";
      }

      std::cout << std::endl;
    }
  }

  return 0;
}

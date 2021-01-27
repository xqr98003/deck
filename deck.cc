// Copyright 2021 xqr98003. All rights reserved.

#include <utility>
#include <string>

#include "deck/deck.h"

std::array<std::string, 13> Deck::rank_names_ = {{
    u8"2", u8"3", u8"4", u8"5", u8"6", u8"7", u8"8", u8"9", u8"10",
    u8"J", u8"Q", u8"K", u8"A"
}};

std::array<std::string, 4> Deck::suit_names_ = {{
    u8"\u2663",  // clubs
    u8"\u2666",  // diamonds
    u8"\u2665",  // hearts
    u8"\u2660"   // spades
}};

Deck::Deck(std::mt19937* random_number_generator, bool do_shuffle)
  : rng_(random_number_generator), index_(0) {
  for (size_t i = 0; i < MAX_CARD; i++) {
    cards_[i] = i;
  }
  if (do_shuffle) shuffle();
}

void Deck::shuffle() {
  Card tmp;
  for (size_t i = 0; i < MAX_CARD; i++) {
    std::uniform_int_distribution<> unif(i, MAX_CARD - 1);
    size_t swap_index = unif(*rng_);

    // swap - avoiding std::swap() because it allocates a new temp
    // variable on each call
    tmp = cards_[i];
    cards_[i] = cards_[swap_index];
    cards_[swap_index] = tmp;
  }
  index_ = 0;
}

std::string Deck::get_suit_name(Suit s) {
  return suit_names_[s];
}

std::string Deck::get_rank_name(Rank r) {
  return rank_names_[r];
}

// Copyright 2021 xqr98003. All rights reserved.

#ifndef DECK_H_
#define DECK_H_

#include <array>
#include <random>
#include <optional>
#include <string>
#include <cstdint>
#include <cassert>

enum CardRank {
  RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_9, RANK_10,
  RANK_J, RANK_Q, RANK_K, RANK_A
};

enum CardSuit {
  SUIT_C, SUIT_D, SUIT_H, SUIT_S
};

typedef uint8_t Card;
typedef uint8_t Rank;
typedef uint8_t Suit;

const size_t MAX_CARD = 52;

class Deck {
 protected:
  std::mt19937* rng_;
  std::array<Card, MAX_CARD> cards_;
  uint8_t index_;

  static std::array<std::string, 13> rank_names_;
  static std::array<std::string, 4> suit_names_;

 public:
  /**
   * Construct a deck of cards. It will automatically be shuffled unless
   * do_shuffle is explicitly set to false.
   *
   * @param random_number_generator You must provide a pointer to a
   *    seeded random number generator to use for random shuffling.
   *    Note that the Deck object will use your generator whenever
   *    shuffle() is called, so it must persist for the life of the
   *    Deck. The Deck object doesn't take ownership of the generator
   *    and the destructor doesn't clean it up.
   * @param do_shuffle You can suppress the default automatic shuffling
   *    by setting do_shuffle to false.
   */
  explicit Deck(std::mt19937* random_number_generator, bool do_shuffle = true);

  /**
   * Shuffle the deck. This randomizes the random card ordering and also
   * resets the card counter so that there is a full deck remaining. Note
   * that the constructor calls shuffle() automatically by default, so
   * you may not need to call it explicitly.
   */
  void shuffle();

  /**
   * Return the size of the deck.
   *
   * @return The number of cards remaining in the deck.
   */
  inline size_t size() const {
    return cards_.size() - index_;
  }

  /**
   * Deal the next card from the deck.
   *
   * @return An optional value which is either the next card from the
   *   deck, or null if there are no cards remaining.
   */
  inline std::optional<Card> deal_card() {
    if (size() == 0) {
      return {};
    } else {
      return cards_[index_++];
    }
  }

  /**
   * Return the suit of the card. Legal suits are named in the CardSuit
   * enum.
   */
  inline static Suit get_suit(Card c) {
    assert(c < MAX_CARD);
    return c / 13;
  }

  /**
   * Return the rank of the card. Legal ranks are named in the CardRank
   * enum. You can meaningfully compare ranks with the default numeric
   * comparison operators (<, >, etc.). Aces are high.
   */
  inline static Rank get_rank(Card c) {
    assert(c < MAX_CARD);
    return c % 13;
  }

  /**
   * Return a string representation of the suit (unicode character for
   * the conventional suit symbol). String is UTF8 encoded.
   */
  static std::string get_suit_name(Suit s);

  /**
   * Return a string representation of the rank. String is UTF8 encoded.
   */
  static std::string get_rank_name(Rank r);
};

#endif  // DECK_H_

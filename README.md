
# Solution overview

This problem is straightforward, and my solution is probably a little
bit fancier than would make sense for real project work, because part of
the point has to be demonstrating interesting coding skills.

Here are some design decisions that might be worth mentioning:

- The representation of the Card and Deck data types is like a somewhat
  modernized version of old-school C style, which favors simplicity, use
  of static memory allocation, and taking care about memory
  representation. For example, representing a Card doesn't need more
  than an 8-bit data type. Minimizing use of dynamic memory allocation
  can be important for predictable real-time performance.

- The problem statement intentionally left vague what should happen when
  `deal_card()` is called on an empty deck. I decided to use a
  `std::optional` return value: the optional normally contains a card,
  but if the deck is empty, the optional is a null value. This approach
  is somewhat similar to returning both a card and a separate error
  flag, but using an optional is self-documenting, and the structure of
  the optional forces the user to do an explicit dereference operation
  on the optional before using the value of the card, which is a good
  nudge for them to specify what to do in case the value is
  missing. Another obvious approach would have been to raise an
  exception if the deck is empty, but using exceptions can create a big
  headache in large-scale high-availability systems where different
  legacy components may have different exception conventions, and you
  really don't want the application to crash for trivial reasons.

- I decided to force the user to explicitly specify a seeded random
  number generator for the deck to use.  Proper use of random number
  generators can of course have security implications (online
  poker?). In a robotics simulation context, it can be important to
  control all sources of randomness in a coordinated way so you can try
  to deterministically replicate bugs on subsequent runs by using the
  same random seed.

- I decided to make the Deck constructor shuffle the deck by
  default. That's because the desired behavior of the deck before
  shuffling is not specified, and it's generally good for a constructor
  to return its object in a well-defined, usable state. (That eliminates
  a whole class of potential bugs caused by trying to use improperly
  initialized objects.)

- I decided not to worry about implementing thread safety. It was not
  mentioned in the problem statement, and would add significant
  complexity.

# Requirements

The code should be fairly portable. It was tested in the
following environment:

- OS: Ubuntu Linux 20.04
- Compiler: g++ 9.3.0
- Optional:
    - Auto-generated documentation: Doxygen 1.8.17
    - Style checking: cpplint 1.5.4 under Python 3.8.5

# Installation

Use the provided Makefile:

- Run `make` to build the `test_deck` binary.

- Run `make doc` to rebuild the documentation. The only interesting
  output file is the Deck class in `html/classDeck.html`. I've committed
  the Doxygen output to the repo, so a rebuild shouldn't be necessary.

- Run `make lint` to perform style checking.

# Usage

Run `./test_deck`. Sample output is shown below. (If you run it for
yourself, note that the suit characters may not render properly,
depending on whether your terminal expects UTF8 console output.)

    North:
      ♠ : A J
      ♥ : Q 10 3
      ♦ : Q J 8
      ♣ : A J 6 5 3
    West:
      ♠ : K 8
      ♥ : A 5 4
      ♦ : K 9 5 4 3 2
      ♣ : 8 7
    South:
      ♠ : 9 5 4 2
      ♥ : K 9 2
      ♦ : A
      ♣ : K Q 9 4 2
    East:
      ♠ : Q 10 7 6 3
      ♥ : J 8 7 6
      ♦ : 10 7 6
      ♣ : 10

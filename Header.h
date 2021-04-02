#ifndef HEADER_H
#define HEADER_H

#include <array>

constexpr int max_score{ 21 }; //In blackjack, 21 is the maximum score you can achieve before you lose.
constexpr int dealer_min_score{ 17 }; //In blackjack, 17 is the minimum score the dealer has to achieve.
enum class BJoutcome
{
	player_win,
	dealer_win,
	tie
};

enum cardRank
{
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	ten,
	jack,
	queen,
	king,
	ace,
	max_rank
};

enum suits
{
	clubs,
	diamonds,
	hearts,
	spades,
	max_suits
};

struct cardInfo
{
	cardRank rank{};
	suits suit{};
};
void printCard(const cardInfo& cardsInfo);
std::array<cardInfo, 52> createDeck(std::array<cardInfo, 52>& Deck);
void printDeck(const std::array<cardInfo, 52>& hello);
std::array<cardInfo, 52> shuffleDeck(std::array<cardInfo, 52>& yup);
int getCardValue(cardInfo card, int& aceCounter);
int readCardValue(cardInfo card, int& aceCounter);
char WantsHit();
int isOverMax(int& acecounter, int& score);
bool playerTurn(int& playerScore, std::array<cardInfo, 52>::size_type& counter, std::array<cardInfo, 52> deck, int dealerscore, int& acecounter);
bool dealerTurn(int playerScore, std::array<cardInfo, 52>::size_type& counter, std::array<cardInfo, 52> deck, int& dealerScore, int& acecounter);
BJoutcome playBlackjack(std::array<cardInfo, 52> deck);

#endif
#include <iostream>
#include <array>
#include <algorithm>
#include <ctime>
#include <random>
#include "Header.h"

void printCard(const cardInfo& cardsInfo) {
	switch (cardsInfo.rank)
	{
	case two:
		std::cout << "2";
		break;
	case three:
		std::cout << "3";
		break;
	case four:
		std::cout << "4";
		break;
	case five:
		std::cout << "5";
		break;
	case six:
		std::cout << "6";
		break;
	case seven:
		std::cout << "7";
		break;
	case eight:
		std::cout << "8";
		break;
	case nine:
		std::cout << "9";
		break;
	case ten:
		std::cout << "10";
		break;
	case jack:
		std::cout << "J";
		break;
	case queen:
		std::cout << "Q";
		break;
	case king:
		std::cout << "K";
		break;
	case ace:
		std::cout << "A";
		break;
	default:
		std::cout << "Error on ranks!";
		break;

	}
	switch (cardsInfo.suit)
	{
	case clubs:
		std::cout << "C";
		break;
	case diamonds:
		std::cout << "D";
		break;
	case hearts:
		std::cout << "H";
		break;
	case spades:
		std::cout << "S";
		break;
	default:
		std::cout << "Error on suits!";
		break;
	}
}

std::array<cardInfo, 52> createDeck(std::array<cardInfo, 52>& Deck) {
	int currentcardIndex{ 0 };
	for (int k{ 0 }; k < static_cast<int>(max_suits); ++k) {
		for (int i{ 0 }; i < static_cast<int>(max_rank); ++i)

		{
			Deck[currentcardIndex].rank = static_cast<cardRank>(i);
			Deck[currentcardIndex].suit = static_cast<suits>(k);
			++currentcardIndex;
		}
	}
	return Deck;
}

void printDeck(const std::array<cardInfo, 52>& hello) {
	for (const auto& yes : hello) {
		printCard(yes);
		std::cout << "\n";
	}

}

std::array<cardInfo, 52> shuffleDeck(std::array<cardInfo, 52>& yup)
{

	std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::shuffle(yup.begin(), yup.end(), mt);
	return yup;
}

int getCardValue(cardInfo card, int& aceCounter) {
	if (card.rank <= cardRank::nine)
	{
		return (static_cast<int>(card.rank) + 2);
	}

	switch (card.rank)
	{
	case cardRank::ten:
	case cardRank::jack:
	case cardRank::queen:
	case cardRank::king:
		return 10;
	case cardRank::ace:
		++aceCounter;
		return 11;
	default:
		return 0;
	}

}

/*
This part was actually a huge issue for me. I realised that when i wanted to hit and received an ace card, ace counter is incremented by 1. If the score is above 21 which is the max score,
ace counter will be decremented by one.

However, in the getCardValue() function that tells the current player the card that they got, ace counter gets reincremented to 1. This resulted in an issue where if you were to press hit again
and not get an ace, score will be minused by 10 as ace counter is still one, and then get decremented to 0 and work subsequently. I haven't thought of a good fix for now, so the best way for now
would be to have a seperate readCardValue() function that tells the player the card the he/she got.
*/
int readCardValue(cardInfo card, int& aceCounter) { 
	if (card.rank <= cardRank::nine)
	{
		return (static_cast<int>(card.rank) + 2);
	}

	switch (card.rank)
	{
	case cardRank::ten:
	case cardRank::jack:
	case cardRank::queen:
	case cardRank::king:
		return 10;
	case cardRank::ace:
		return 11;
	default:
		return 0;
	}

}


char WantsHit() {
	std::cout << "(h) to hit or (s) to stand!";
	char ch{};
	std::cin >> ch;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (ch != 's' && ch!= 'h')
	{
		std::cout << "Please enter a valid input!";
		char tmp{};
		std::cin >> tmp;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		ch = tmp;
	}
	return ch;
}

int isOverMax(int& acecounter, int &score) {
	while (score > max_score)
	{
		if (acecounter > 0)
		{
			--acecounter;
			score -= 10;
			std::cout << "Your score is above 21 and you have an ace, hence your ace will be counted as 1 instead! Your current score is " << score << "\n";
		}
		else
		{
			return score;
		}
	}
	return score;
}




bool playerTurn(int& playerScore, std::array<cardInfo, 52>::size_type& counter, std::array<cardInfo, 52> deck, int dealerscore, int& acecounter) {
	playerScore = isOverMax(acecounter, playerScore);
	std::cout << "It's your turn!\n";
	std::cout << "Dealer score is: " << dealerscore << "\n";
	std::cout << "Your score is: " << playerScore << "\n";
	char ifHit{ WantsHit() };
	while (ifHit == 'h')
	{
		playerScore += getCardValue(deck[counter], acecounter);
		playerScore = isOverMax(acecounter, playerScore);
		std::cout << "You got a " << readCardValue(deck[counter], acecounter) << " your score is " << playerScore << "\n";
		counter++;
		if (playerScore > max_score)
		{
			std::cout << "You have busted!\n";
			return false;
		}
		ifHit = WantsHit();
	}
	return true;

}

bool dealerTurn(int playerScore, std::array<cardInfo, 52>::size_type& counter, std::array<cardInfo, 52> deck, int& dealerScore, int& acecounter) {
	dealerScore = isOverMax(acecounter, dealerScore);
	std::cout << "Dealer's turn!\n";
	std::cout << "Player score is currently " << playerScore << "\n";
	std::cout << "Your score is currently " << dealerScore << "\n";
	while (dealerScore < 17)
	{
		dealerScore += getCardValue(deck[counter], acecounter);
		dealerScore = isOverMax(acecounter, dealerScore);
		std::cout << "Dealer got a " << readCardValue(deck[counter], acecounter) << " and now has " << dealerScore << "\n";
		counter++;
	}
	if (dealerScore > max_score)
	{
		std::cout << "Dealer busted!\n";
		return false;
	}
	char toContinue{ WantsHit() };
	while (toContinue == 'h')
	{
		dealerScore += getCardValue(deck[counter], acecounter);
		dealerScore = isOverMax(acecounter, dealerScore);

		std::cout << "You got a " << readCardValue(deck[counter], acecounter) << " your score is " << dealerScore << "\n";
		counter++;
		if (dealerScore > max_score)
		{
			std::cout << "Dealer busted!\n";
			return false;
		}
		toContinue = WantsHit();
	}

	return true;
}




BJoutcome playBlackjack(std::array<cardInfo, 52> deck) {
	int playerAceCounter{ 0 };
	int dealerAceCounter{ 0 };
	std::array<cardInfo, 52>::size_type counter{ 0 };
	int dealerScore{ getCardValue(deck[counter++], dealerAceCounter) };
	int playerScore{ getCardValue(deck[counter++], playerAceCounter) };
	playerScore += getCardValue(deck[counter++], playerAceCounter);
	bool playerBust{ playerTurn(playerScore, counter, deck, dealerScore, playerAceCounter) };
	if (!playerBust)
	{
		return BJoutcome::dealer_win;
	}
	bool dealerBust{ dealerTurn(playerScore, counter, deck, dealerScore, dealerAceCounter) };
	if (!dealerBust) {
		return BJoutcome::player_win;
	}
	if (dealerBust && playerBust)
	{
		if (playerScore > dealerScore)
		{
			return BJoutcome::player_win;
		}
		else if (dealerScore > playerScore) {
			return BJoutcome::dealer_win;
		}
		else
		{
			return BJoutcome::tie;
		}
	}
}

int main() {
	std::array<cardInfo, 52> deck;
	deck = createDeck(deck);
	shuffleDeck(deck);
	printDeck(deck);
	BJoutcome outcome{ playBlackjack(deck) };
	if (outcome == BJoutcome::dealer_win)
	{
		std::cout << "Dealer wins!";
	}
	else if (outcome == BJoutcome::player_win)
	{
		std::cout << "Player wins!";
	}
	else
	{
		std::cout << "Tie between player and dealer!";
	}
	return 0;
}
#include<iostream>
#include <queue>
#include<cstdlib>
#include<vector>
#include"Card.h"

using namespace std;

void shuffleDeck(queue<Card> & deck)
{
	Card temp;		//creating temp Card for swapping
	vector<Card>newDeck;	//creating vector for swapping
	while(deck.size() != 0)
	{
		newDeck.push_back(deck.front());	//pushing the queue deck onto vector newdeck
		deck.pop();							//popping the queue
	}
	
	for (unsigned int i = 0; i < newDeck.size(); i++)
	{
		for (unsigned int j = 0; j < newDeck.size(); j++)		//nested for loop for swapping
		{
			if (rand() % 2 == 0)		//random number
			{
				temp = newDeck[i];			//swapping algorithm
				newDeck[i] = newDeck[j];
				newDeck[j] = temp;
			}
		}
	}

	while(newDeck.size() > 0)		//while vector has stuff in it
	{
		deck.push(newDeck.back());		//putting the vector back into the queue
		newDeck.pop_back();
	}
	
}


void playGame(queue<Card> & deck1, queue<Card> & deck2)
{

	vector<Card> warCount;		//empty vector to hold 

	while (!deck1.empty() && !deck2.empty())		//loops while neither deck is empty
	{
	
		cout << deck1.front().getCardValue() << " vs " << deck2.front().getCardValue() << endl;	//announces the card battle.
		if (deck1.front().getCardValue() > deck2.front().getCardValue())		//if deck 1 wins
		{
			deck1.push(deck1.front());	//pushes deck1 and deck two fronts to back of deck 1 queue.
			deck1.push(deck2.front());
			deck1.pop();				//pops off deck1 and 2.  Now deck 2 is one less, deck 1 is one more.
			deck2.pop();
		}
		else if (deck1.front().getCardValue() < deck2.front().getCardValue())		//if deck 2 wins
		{
			deck2.push(deck2.front());		//deck 2 gets both cards
			deck2.push(deck1.front());
			deck1.pop();					//both cards popped off front of queue, deck 1 down a card, deck 2 up one.
			deck2.pop();
		}
		else if (deck1.front().getCardValue() == deck2.front().getCardValue())		//if there is a tie
		{
			if (deck1.size() < 4)		//each deck needs at least 4 cards.  the original tie, the two facedown, and the showdown...
			{
				for (unsigned int i = 0; i < deck1.size() +1; i++)		//if they don't have that, they automatically lose.
				{
					deck1.pop();		//and the deck is emptied to exit the while loop of neither deck being empty.
				}
				
			}
			else if (deck2.size() < 4)		//same is done for deck 2
			{
				for (unsigned int i = 0; i < deck2.size() +1; i++)
				{
					deck2.pop();
					cout << deck2.size() << endl;
				}
			
			}
			else
			{
				cout << "WAR!!! " << endl;		//with sufficient cards, war is triggered.
				
				while ((deck1.size() > 3) && (deck2.size() > 3) && deck1.front().getCardValue() == deck2.front().getCardValue())	//while the decks have enough cards and the value is tied ie consecutive wars
				{
					
					warCount.push_back(deck1.front());		//we push the cards onto the vector

					warCount.push_back(deck2.front());

					deck1.pop();							//and pop them off the front
					deck2.pop();

					cout << "facedown player1: " << deck1.front().getCardValue() << endl;	//printing facedown cards, putting them in vector, popping off queue
					warCount.push_back(deck1.front());
					deck1.pop();

					cout << "facedown player1: " << deck1.front().getCardValue() << endl;
					warCount.push_back(deck1.front());
					deck1.pop();

					cout << "facedown player2: " << deck2.front().getCardValue() << endl;
					warCount.push_back(deck2.front());
					deck2.pop();

					cout << "facedown player2: " << deck2.front().getCardValue() << endl;
					warCount.push_back(deck2.front());
					deck2.pop();

					cout << "-- " << deck1.front().getCardValue() << " vs " << deck2.front().getCardValue() << endl;	//showdown


					if (deck1.front().getCardValue() > deck2.front().getCardValue())	//if deck1 wins war, they get the vector of cards
					{
						for (unsigned int i = 0; i < warCount.size(); i++)
						{
							deck1.push(warCount[i]);		//pushing the contents of war vector onto deck 1
					
						}
						warCount.clear();			//erasing war vector
						deck1.push(deck1.front());	//pushing the revealed showdown war cards onto deck one
						deck1.push(deck2.front());
						deck1.pop();				//popping them off their respective decks
						deck2.pop();
					}
					else if (deck1.front().getCardValue() < deck2.front().getCardValue())		//if deck 2 wins war...
					{
						for (unsigned int i = 0; i < warCount.size(); i++)		
						{
							deck2.push(warCount[i]);			//deck2 gets vector of warcount
							
						}
						warCount.clear();			//clears the vector warcount for future wars
						deck2.push(deck2.front());		//putting everything onto deck2
						deck2.push(deck1.front());
						deck1.pop();
						deck2.pop();
					}
				}//while the game is still tied
			} //while there are enough cards to WAR
		}	//if it's a tie
	}	//while neither of the decks are empty
}	//end of play Function

int main()
{
	Card playCard;
	queue<Card>deck1;
	queue<Card>deck2;
	int choice;

	for (int i = 0; i < 13; i++)	//filling the two decks with two copies each of 0-12.
	{
		playCard.setCardValue(i);
		deck1.push(playCard);	
		deck1.push(playCard);
		deck2.push(playCard);
		deck2.push(playCard);
	}

	cout << "What seed would you like?: ";
	cin >> choice;
	srand(choice);	//before shuffle deck, randomizes the deck in a specific way.

	shuffleDeck(deck1);
	shuffleDeck(deck2);

	playGame(deck1, deck2);

	if (deck1.empty())		//if deck 1 is empty, player 2 wins
	{
		cout << "Player 2 wins!" << endl;
	}
	else if (deck2.empty())		//if deck 2 empty, player 1 wins
	{
		cout << "Player 1 wins!" << endl;
	}

	cin.ignore(2);
}
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

// todo:

// 1: create list of visible cards.
// 2: Finish player functions to play cards, and attack.
// 3: return actions
// changes

// kill opponent
/// summon creatures
//// Mana,

/// attack
//// what cards can attack.

using namespace std;

enum eCardType
{
    eCreature = 0,
    eGreenItem = 1,
    eRedItem = 2,
    eBlueItem = 3

};

enum eLocation
{
    ePlayerHand = 0,
    ePlayerBoard = 1,
    eEnemyBoard = -1
    // eNAMEOFVARIABLE: NUMBER
};

///////////// Classes /////////////

// class Deck
// {
//     // keep track of entire deck for both players.
// };

class Card
{
public:
    int cardNumber;
    int instanceId;
    eLocation location; // 0,1,-1 for player hand, player side of board, opponent board.
    eCardType cardType;
    int cost;
    int attack;
    int defense;
    string abilities;
    int myHealthChange;
    int opponentHealthChange;
    int cardDraw;
    bool abilityBreakthrough;
    bool abilityCharge;
    bool abilityGuard;
    Card(int cardNumber_, int instanceId_, eLocation location_, eCardType cardType_, int cost_, int attack_, int defense_, string abilities_, int myHealthChange_, int opponentHealthChange_, int cardDraw_)
    {
        cardNumber = cardNumber_;
        instanceId = instanceId_;
        location = location_;
        cardType = cardType_;
        cost = cost_;
        attack = attack_;
        defense = defense_;
        abilities = abilities_;
        myHealthChange = myHealthChange_;
        opponentHealthChange = opponentHealthChange_;
        cardDraw = cardDraw_;

        // Check abilities
        abilityBreakthrough = checkAbility('B');
        abilityCharge = checkAbility('C');
        abilityGuard = checkAbility('G');
    }

    bool checkAbility(char ability)
    {
        return abilities.find(ability) != string::npos;
    }
};

class Player
{
public:
    int maxMana;
    int remainingMana;
    int health;
    // visibleCards list of pointers to cards.
    std::vector<Card *> visibleCards;
    // make choices
    string getAllActions()
    {
        string allActions = "";

        for (size_t i = 0; i < visibleCards.size(); i++)
        {
            // cards in hand

            if (visibleCards[i]->location == ePlayerHand && visibleCards[i]->cardType == eCreature)
            {
                allActions += summonCard(visibleCards[i]);
            }
            if (visibleCards[i]->location == ePlayerBoard)
            {
                allActions += attack(visibleCards[i]);
            }
        }

        return allActions;
    }

    int findTarget()
    {
        // output =  either player -1 or enemy creature.
        //loop through all visible cards.
        for (size_t i = 0; i < visibleCards.size(); i++)
        {
            if (visibleCards[i]->location == eEnemyBoard && visibleCards[i]->abilityGuard)
            {
                return visibleCards[i]->instanceId;
            }
        }
        return -1;
    }

    string summonCard(Card *playableCard)
    {
        string action = "SUMMON";
        // get_mana
        // get_playable cards
        //
        if (playableCard->cost <= remainingMana)
        {
            cerr << "Summon Cardnumber: " << playableCard->cardNumber << " Cardtype: " << playableCard->cardType << " Cost: " << playableCard->cost << " location: " << playableCard->location << endl;

            //cerr << "Summon Mana Before: " << remainingMana << endl;
            action += " " + to_string(playableCard->instanceId) + ";";
            //cerr << "Action: " << action << endl;
            remainingMana -= playableCard->cost;
            //cerr << "Summon Mana After: " << remainingMana << endl;
        }
        else
        { // Not sure if cardNumber or other id.
            action = "";
        }

        return action;
    }

    string attack(Card *playableCard) //target could be enum
    {
        //later check opponent creatures and decide if to attack them or opponent.
        string action = "ATTACK"; // ATTACK from to
        //

        action += " " + to_string(playableCard->instanceId) + " " + to_string(findTarget()) + ";";
        return action;
        // else if (targetType == "Creature")
        // {
        //     action += " " + to_string(playableCard->cardNumber) + " " + to_string(targetID);
        // }
    }

    //place holder for getting use actions.
    //string use(){
    //
    //}
};

int main()
{
    //define player classes around here.
    array<Player *, 2> players{new Player, new Player};
    // game loop
    while (1)
    {
        for (int i = 0; i < 2; i++)
        {
            int playerHealth;
            int playerMana;
            int playerDeck;
            int playerRune;
            int playerDraw;
            cin >> playerHealth >> playerMana >> playerDeck >> playerRune >> playerDraw;
            cin.ignore();

            //populate player class

            auto player = players[i];
            player->health = playerHealth;
            player->maxMana = playerMana;
            player->remainingMana = playerMana; // this might cause issues later.
        }

        int opponentHand;
        int opponentActions;
        cin >> opponentHand >> opponentActions;
        cin.ignore();
        for (int i = 0; i < opponentActions; i++)
        {
            string cardNumberAndAction;
            getline(cin, cardNumberAndAction);
        }
        int cardCount;
        cin >> cardCount;
        cin.ignore();
        //array<Card *, cardCount> cards{new , new Player};
        vector<Card *> currentVisibleCards;
        for (int i = 0; i < cardCount; i++)
        {
            int cardNumber;
            int instanceId;
            int location; // playercards 0 = player hand, 1 = player side of board.
            int cardType; // 0 = creature
            int cost;
            int attack;
            int defense;
            string abilities;
            int myHealthChange;
            int opponentHealthChange;
            int cardDraw;
            cin >> cardNumber >> instanceId >> location >> cardType >> cost >> attack >> defense >> abilities >> myHealthChange >> opponentHealthChange >> cardDraw;
            cin.ignore();
            cerr << "Abilities: " << abilities << endl;

            eLocation loc;
            switch (location)
            {
            case ePlayerHand:
                loc = ePlayerHand;
                break;
            case ePlayerBoard:
                loc = ePlayerBoard;
                break;
            case eEnemyBoard:
                loc = eEnemyBoard;
                break;
            default:
                break;
            }

            eCardType cT;
            switch (cardType)
            {
            case eCreature:
                cT = eCreature;
                break;
            case eGreenItem:
                cT = eGreenItem;
                break;
            case eRedItem:
                cT = eRedItem;
                break;
            case eBlueItem:
                cT = eBlueItem;
                break;
            default:
                break;
            }
            currentVisibleCards.push_back(new Card(cardNumber, instanceId, loc, cT, cost, attack, defense, abilities, myHealthChange, opponentHealthChange, cardDraw));

            //cerr << "currentVisibleCards[1]: " << currentVisibleCards[1]->cost << endl;
            //cerr << "currentVisibleCards size: " << currentVisibleCards.size << endl;
        }

        players[0]->visibleCards = currentVisibleCards;
        //cerr << "cardNumber: " << cardNumber << " instanceIDS: " << instanceId << " location: " << location << " cost: " << cost << endl;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        string output;
        if (players[0]->maxMana > 0)
        {
            output = players[0]->getAllActions();
        }
        else
        {
            output = "PASS";
        }

        cout << output << endl;
        //SUMMON id to summon the creature of instanceId id from the player's hand.
        //ATTACK idAttacker idTarget to attack an opposing creature or opposing player of instanceId idTarget with a creature on the board of instanceId idAttacker.
        //idTarget can be the "no-creature" identifier -1. It is used to attack the opponent directly.
        //PASS to do nothing.
        //SUMMON 3;ATTACK 4 5 yolo; ATTACK 8 -1 no fear.
    }
}
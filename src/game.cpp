// game.h
// Simeon Ng
// Jason Herning
// Updated: 2/26/19
// Game Class Source File

#include "game.h"

// ---- Game: Ctor ----

Game::Game() = default;

// ---- Game : Public Member Functions

void Game::gameLoop()
{
    cout << "Game started" << endl;

    // Player 1 places ships
    cout << "Player 1, place your ships!" << endl;
    placeDefaultShips(_playerOne);

    printTopBoardPlayer1();

    // Player 2 places ships
    cout << "Player 2, place your ships!" << endl;
    placeDefaultShips(_playerTwo);
    printTopBoardPlayer1();

    while(true) {
        // ---- PLAYER 1'S TURN ----

        cout << "Player 1's Turn" << endl;
        Coords c1 = getUserCoordFire(_playerOne);
        if(_playerTwo.hit(c1)) {
            cout << "HIT!" << endl;
        }
        else {
            cout << "MISS!" << endl;
        }

        if(_playerTwo.getAllSunk()) {
            cout << "PLAYER 1 WINS!!!" << endl;
            break;
        }

        // ---- PLAYER 2'S TURN ----

        cout << "Player 2's Turn" << endl;

        printTopBoardPlayer1();
        Coords c2 = getUserCoordFire(_playerTwo);
        if(_playerOne.hit(c1)) {
            cout << "HIT!" << endl;
        }
        else {
            cout << "MISS!" << endl;
        }

        if(_playerOne.getAllSunk()) {
            cout << "PLAYER 2 WINS !!!" << endl;
            break;
        }

        printTopBoardPlayer2();
    }
}

void Game::placeDefaultShips(Player & player) {
    Ships ship1 = CARRIER;
    Ships ship2 = BATTLESHIP;
    Ships ship3 = DESTROYER;
    Ships ship4 = SUBMARINE;
    Ships ship5 = PATROL;

    placeShip(player, ship1);
    placeShip(player, ship2);
    placeShip(player, ship3);
    placeShip(player, ship4);
    placeShip(player, ship5);
}

Coords Game::getUserCoordFire(Player & player){
    while(true) {
        size_t coordX = getUserCoordX();
        size_t coordY = getUserCoordY();

        Coords c(coordX, coordY);
        if(player.isCoordTakenFired(c)) {
            cout << "You have already fired at this coordinate!" << endl;
            cout << "Enter another coordinate";
            continue;
        }
        else {
            return c;
        }
    }
}

Coords Game::getUserCoordShip(Player & player) {
    while(true) {
        size_t coordX = getUserCoordX();
        size_t coordY = getUserCoordY();

        Coords c(coordX, coordY);
        if(player.isCoordTakenShip(c)) {
            cout << "Another ship is already there!" << endl;
            cout << "Enter another coordinate." << endl;
            continue;
        }
        else {
            return c;
        }
    }
}

size_t Game::getUserCoordX() {
    while(true) {
        string inputX;
        cout << "Enter X coordinate [0-" << _playerOne.getLength() - 1 << "]: ";
        getline(cin, inputX);
        if(!cin) {
            std::cout << "Input error. Try again." << endl;
            continue;
        }
        istringstream iss(inputX);
        size_t coordX;
        iss >> coordX;
        if(!iss || coordX >= _playerOne.getLength()) {
            std::cout << "X coordinate must be an integer between [0-" << _playerOne.getLength() - 1 << "]" << endl;
            continue;
        }
        return coordX;
    }
}

size_t Game::getUserCoordY() {
    while(true) {
        string inputY;
        cout << "Enter Y coordinate [0-" << _playerOne.getWidth() - 1 << "]: ";
        getline(cin, inputY);
        if (!cin) {
            std::cout << "Input error. Try again." << endl;
            continue;
        }
        istringstream iss(inputY);
        iss.str(inputY);
        size_t coordY;
        iss >> coordY;
        if (!iss || coordY >= _playerOne.getWidth()) {
            std::cout << "Y coordinate must be an integer between [0-" << _playerOne.getWidth() - 1 << "]" << endl;
            continue;
        }
        return coordY;
    }
}

bool Game::getUserOrientation() {
    while(true) {
        string orientation;
        cout << "[H]orizontal or [V]ertical?: ";
        getline(cin, orientation);
        if (!cin) {
            std::cout << "Input error. Try again." << endl;
            continue;
        }
        switch(orientation[0]) {
            case 'H': return true;
            case 'V': return false;
            case 'h': return true;
            case 'v': return false;
            default:
                cout << "Not a valid orientation." << endl;
                continue;
        }
    }
}

void Game::placeShip(Player & player, Game::Ships ship) {
    string shipType;
    size_t shipValue = 0;
    switch(ship) {
        case CARRIER: shipType = "Carrier"; shipValue = 4; break;
        case BATTLESHIP: shipType = "Battleship"; shipValue = 3; break;
        case DESTROYER: shipType = "Destroyer"; shipValue = 2; break;
        case SUBMARINE: shipType = "Submarine"; shipValue = 2; break;
        case PATROL: shipType = "Patrol"; shipValue = 1; break;
    }

    while (true) {
        cout << "Place the front of your " << shipType << ":" << endl;
        Coords c1 = getUserCoordShip(player);
        bool orientation = getUserOrientation();
        Coords c2 = {0, 0};

        if (orientation) {
            if (c1.x + shipValue < player.getLength()) {
                c2 = {c1.x + shipValue, c1.y};
            }
            else if (c1.y + shipValue < player.getWidth()) {
                cout << "No space. Ship has been placed vertically instead.";
                c2 = {c1.x, c1.y + shipValue};
            }
            else {
                cout << "Unable to place ship try again." << endl;
                continue;
            }
        }
        else {
            if (c1.y + shipValue < player.getWidth()) {
                c2 = {c1.x, c1.y + shipValue};
            }
            else if (c1.x + shipValue < player.getLength()) {
                cout << "No space. Ship has been placed horizontally instead.";
                c2 = {c1.x + shipValue, c1.y};
            }
            else {
                cout << "Unable to place ship try again." << endl;
                continue;
            }
        }
        Ship ship(c1, c2);
        player.addShip(ship);
        break;
    }
}

void Game::printTopBoardPlayer1() {
    cout << _playerOne.getBoard();
}

void Game::printTopBoardPlayer2(){
    cout << _playerTwo.getBoard();
}

void Game::clearBoard() const {
    cout << endl << endl << endl << endl << endl
         << endl << endl << endl << endl << endl;
}





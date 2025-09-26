#pragma once

#include <iostream>
#include <algorithm>
#include <random>
#include <array>
#include <map>

struct SlotRow
{
    std::array<char, 5> RowNumbers;
};

class SlotMachine
{
private:
    /* data */
public:
    SlotMachine(/* args */);
    ~SlotMachine();

    int coins = 10;

    void displayMenu();

    void addCoins();

    bool activateMachine();

    void displaySlots(const std::array<SlotRow, 3> &slotsArr);

    bool checkForRewards(const std::array<SlotRow, 3> &slots);

    void gameOver();

    std::array<SlotRow, 3> generateSlots();
};

SlotMachine::SlotMachine(/* args */)
{
}

SlotMachine::~SlotMachine()
{
}

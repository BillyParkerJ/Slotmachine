#include "SlotMachine.h"

std::map<std::string, int> winningCombos =
    {
        {"#####", 4500}, {"####", 1500}, {"###", 300}, {"+++++", 1200}, {"++++", 300}, {"+++", 60}, {"?????", 240}, {"????", 60}, {"???", 15}, {"$$$$$", 60}, {"$$$$", 15}, {"$$$", 5}, {"@@@@@", 20}, {"@@@@", 5}, {"@@@", 1}};

int main()
{
    SlotMachine slotMachine;

    std::cout << "TEST!!!!" << "\n";

    slotMachine.displayMenu();

    return 0;
}

bool SlotMachine::activateMachine()
{
    // DIsplay Rewards
    std::cout << " ##### = 4500 Coins  | +++++ = 1200 Coins | ????? = 240 Coins | $$$$$ = 60 Coins  | @@@@@ = 20 Coins  \n";
    std::cout << " ####  = 1500 Coins  | ++++  = 300  Coins | ????  = 60  Coins | $$$$  = 15 Coins  | @@@@  = 5  Coins  \n";
    std::cout << " ###   = 300  Coins  | +++   = 60   Coins | ???   = 15  Coins | $$$   = 5  Coins  | @@@   = 1  Coin   \n";

    std::cout << "Your Coins: " << coins << "\n";

    bool isPlaying = true;
    std::cout << "Press Q to quit. Press any other Key to play. \n";
    std::string answer;
    std::cin >> answer;

    if (answer == "Q" || answer == "q")
    {
        isPlaying = false;
    }

    while (isPlaying)
    {
        if (coins > 0)
        {
            // Generate
            auto slots = SlotMachine::generateSlots();

            // Display Slots
            displaySlots(slots);

            // Check for Rewards
            checkForRewards(slots);

            bool playAgain = false;

            while (!playAgain)
            {
                std::cout << "Do you want to play again? Y/N" << "\n";
                std::cin >> answer;

                if (answer == "Y" || answer == "y")
                {
                    playAgain = true;
                    continue;
                }
                else if (answer == "N" || answer == "n")
                {
                    isPlaying = false;
                    break;
                }
                else
                {
                    std::cout << "Invalid Input" << "\n";
                }
            }
        }
        else
        {
            std::cout << "No Coins left. Please add more to play again! \n";
            return true;
        }
    }
    return true;
}

std::array<SlotRow, 3> SlotMachine::generateSlots()
{
    std::array<char, 5> slotSymbols = {'#', '+', '?', '$', '@'};
    std::array<SlotRow, 3> slots;

    std::random_device rd; // non-deterministic generator
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, slotSymbols.size() - 1);

    std::array<char, 5> randomRow;

    for (size_t slotRow = 0; slotRow < 3; ++slotRow)
    {
        for (size_t symbol = 0; symbol < 5; ++symbol)
        {
            randomRow[symbol] = slotSymbols[dis(gen)]; // array[index] = random symbol from slotSymbols
        }
        slots[slotRow].RowNumbers = randomRow;
    }
    return slots;
}

void SlotMachine::displayMenu()
{

    std::vector<std::string> quitInputs = {"3", "Q", "q"};

    bool inMenu = true;

    while (inMenu)
    {
        std::string uInput;
        std::cout << "What do you want to do? \n";
        std::string menuText = " 1. Add Coins \n 2. Play Slots \n 3. Quit \n";
        std::cout << menuText;

        std::cin >> uInput;

        if (uInput == "1") // Add Coins
        {
            SlotMachine::addCoins();
        }
        else if (uInput == "2") // Play the Game
        {
            SlotMachine::activateMachine();
            /* code */
        }
        else if (std::find(quitInputs.begin(), quitInputs.end(), uInput) != quitInputs.end()) // Quit
        {
            std::cout << "Quitting..." << "\n";
            inMenu = false;
        }
        else
        {
            std::cout << "Invalid input!" << "\n";
        }
    }
}

void SlotMachine::addCoins()
{
    bool isValidNumber = false;

    while (!isValidNumber)
    {
        std::cout << "How many Coins do you want to add?\n ";
        std::cout << ":";

        std::string coinInput;
        int newAmount;

        std::cin >> coinInput;

        try
        {
            newAmount = std::stoi(coinInput);
            coins += newAmount;
            isValidNumber = true;
            break;
        }
        catch (const std::exception &e)
        {
            std::cout << "Invalid Input!" << "\n";
            isValidNumber = false;
            break;
        }
    }
}

void SlotMachine::displaySlots(const std::array<SlotRow, 3> &slotsArr)
{
    for (auto &row : slotsArr)
    {
        std::string currentRowDisplay = "";
        for (auto sRow : row.RowNumbers)
        {
            currentRowDisplay += sRow;
        }
        std::cout << " |-| " << currentRowDisplay << " |-| " << "\n";
    }
}

bool SlotMachine::checkForRewards(const std::array<SlotRow, 3> &slots)
{
    // #', ' + ', ' ? ', ' $ ', ' @'

    for (const auto row : slots)
    {
        std::string resultRow(row.RowNumbers.begin(), row.RowNumbers.end());
        for (const auto &[combo, value] : winningCombos)
        {
            if (resultRow.find(combo) != std::string::npos)
            {
                std::cout << "Got " << combo << "\n";
                std::cout << "You won " << value << " Coins! \n";
                coins += value;
                std::cout << "Your coins: " << coins << "\n";
            }
        }
    }

    return true;
}

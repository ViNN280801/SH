#include <iostream>

#include "train.hpp"

int main()
{
    TrainList tl;
    tl.push_back(tl.createTrainDataTest("Moscow", "10:00:00", "4:00:00", tl.int_to_train_type(1)));
    tl.push_back(tl.createTrainDataTest("Saint-Petersburg", "23:45:0", "6:15:00", tl.int_to_train_type(2)));
    tl.push_back(tl.createTrainDataTest("Vladikavkaz", "9:10:00", "3:30:0", tl.int_to_train_type(1)));
    tl.push_back(tl.createTrainDataTest("Moscow", "17:25:00", "7:35:0", tl.int_to_train_type(0)));
    tl.push_back(tl.createTrainDataTest("Rostov", "7:05:0", "10:30:00", tl.int_to_train_type(2)));
    tl.push_back(tl.createTrainDataTest("Perm", "4:45:0", "4:10:00", tl.int_to_train_type(2)));
    tl.push_back(tl.createTrainDataTest("Moscow", "13:20:00", "5:35:0", tl.int_to_train_type(2)));
    tl.push_back(tl.createTrainDataTest("Saint-Petersburg", "14:45:0", "3:20:00", tl.int_to_train_type(0)));
    tl.push_back(tl.createTrainDataTest("Saint-Petersburg", "15:30:0", "3:20:00", tl.int_to_train_type(0)));
    tl.push_back(tl.createTrainDataTest("Kazan", "18:20:0", "7:20:00", tl.int_to_train_type(10)));
    tl.push_back(tl.createTrainDataTest("Ekaterinburg", "8:45:0", "2:05:0", tl.int_to_train_type(5)));
    tl.push_back(tl.createTrainDataTest("Samara", "5:55:0", "6:05:0", tl.int_to_train_type(1)));
    tl.push_back(tl.createTrainDataTest("Moscow", "15:25:0", "5:00:0", tl.int_to_train_type(1)));
    tl.push_back(tl.createTrainDataTest("Moscow", "11:40:0", "3:05:0", tl.int_to_train_type(1)));
    tl.printAllData();

    std::cout << "Trains to Moscow for the period: 10:00:00 - 15:00:00\n";
    tl.printTrainsToMoscow("10:00:00", "15:00:00");

    /* std::cout << "Enter your time interval\nTime 1 = ";
    std::string time1(tl.getUsersTime());
    std::cout << "Time 2 = ";
    std::string time2(tl.getUsersTime());
    tl.printTrainsToMoscow(time1.c_str(), time2.c_str()); */

    tl.printMinTimeInRoadOfTrainCertainType(tl.int_to_train_type(1));

    int userTT{};
    for (;;)
    {
        std::cout << "1. Fast\n2. Express\n3. Passenger\nEnter type of train: ";
        std::cin >> userTT;
        if (userTT != 1 && userTT != 2 && userTT != 3)
            std::cout << "Error. Incorrect input. Try again." << std::endl;
        else
            break;
    }

    switch (userTT)
    {
    case 1:
        tl.printMinTimeInRoadOfTrainCertainType(tl.int_to_train_type(0));
        break;
    case 2:
        tl.printMinTimeInRoadOfTrainCertainType(tl.int_to_train_type(1));
        break;
    case 3:
        tl.printMinTimeInRoadOfTrainCertainType(tl.int_to_train_type(2));
        break;
    default:
        std::cout << "Incorrect input. Try again...\n";
        break;
    }

    return EXIT_SUCCESS;
}

#include <iostream>
#include <iomanip>

#include "wagons.hpp"

struct Services
{
public:
    unsigned m_waterPrice{40};
    unsigned m_teaPrice{50};
    unsigned m_coffeePrice{75};
    unsigned m_foodPrice{300};
    unsigned m_winePrice{750};
} m_serv;

void Wagon::copyObj(Wagon const &w)
{
    m_ID = w.m_ID;
}

void Wagon::clearObj(Wagon &w)
{
    w.m_ID = 0U;
}

Wagon::Wagon() : m_ID(0U) {}

Wagon::Wagon(unsigned const &newID) : m_ID(newID) {}

Wagon::Wagon(Wagon const &w) { copyObj(w); }

Wagon::Wagon(Wagon &&w)
{
    copyObj(w);
    clearObj(w);
}

Wagon &Wagon::operator=(Wagon const &w)
{
    if (this == &w)
        return *this;

    copyObj(w);

    return *this;
}

Wagon &Wagon::operator=(Wagon &&w) noexcept
{
    if (this == &w)
        return *this;

    clearObj(*this);
    copyObj(w);
    clearObj(w);

    return *this;
}

Wagon::~Wagon() { clearObj(*this); }

unsigned Wagon::getID() const { return m_ID; }
void Wagon::setID(unsigned const &newID) { m_ID = newID; }

void Wagon::printInfo() const
{
    PRINT("Wagon ID: ", m_ID);
}

Services Wagon::getServices() const { return m_serv; }

void Wagon::printPriceList() const
{
    PRINT_PRICE(NAME_WATER, m_serv.m_waterPrice);
    PRINT_PRICE(NAME_TEA, m_serv.m_teaPrice);
    PRINT_PRICE(NAME_COFFEE, m_serv.m_coffeePrice);
    PRINT_PRICE(NAME_FOOD, m_serv.m_foodPrice);
    PRINT_PRICE(NAME_WINE, m_serv.m_winePrice);
}

void KupeWagon::copyObj(KupeWagon const &w)
{
    m_seatsNum = w.m_seatsNum;
    m_availableSeatsNum = w.m_availableSeatsNum;
    m_priceOfSeat = w.m_priceOfSeat;
}

void KupeWagon::clearObj(KupeWagon &w)
{
    w.setID(0);
    w.m_seatsNum = 0U;
    w.m_availableSeatsNum = 0U;
    w.m_priceOfSeat = 0.0;
}

KupeWagon::KupeWagon() : m_seatsNum(kdefault_seatsNum),
                         m_availableSeatsNum(kdefault_availableSeatsNum),
                         m_priceOfSeat(kdefault_priceOfSeat) { setID(1); }

KupeWagon::KupeWagon(unsigned const &newID,
                     unsigned const &newSeatsNum,
                     unsigned const &newAvailableSeatsNum,
                     double const &newPriceOfSeat) : m_seatsNum(newSeatsNum),
                                                     m_availableSeatsNum(newAvailableSeatsNum),
                                                     m_priceOfSeat(newPriceOfSeat)
{
    if (newAvailableSeatsNum > newSeatsNum)
    {
        PRINT("ERROR. Count of available seats can't be greater than total count of seats\n",
              "Exiting with status \'1\'");
        exit(EXIT_FAILURE);
    }
    setID(newID);
}

KupeWagon::KupeWagon(KupeWagon const &w) : Wagon(w.getID()) { copyObj(w); }

KupeWagon::KupeWagon(KupeWagon &&w)
{
    copyObj(w);
    clearObj(w);
}

KupeWagon &KupeWagon::operator=(KupeWagon const &w)
{
    if (this == &w)
        return *this;

    copyObj(w);

    return *this;
}

KupeWagon &KupeWagon::operator=(KupeWagon &&w) noexcept
{
    if (this == &w)
        return *this;

    clearObj(*this);
    copyObj(w);
    clearObj(w);

    return *this;
}

KupeWagon::~KupeWagon() { clearObj(*this); }

void KupeWagon::printInfo() const
{
    PRINT("\n/*------ This is a kupe wagon ------*/", "");
    PRINT("Wagon ID: ", getID());
    PRINT("Count of seats: ", m_seatsNum);
    PRINT("Count of available seats: ", m_availableSeatsNum);
    PRINT("Price of 1 seat: ", m_priceOfSeat);
    PRINT("Total amount of seats: ", TO_DOUBLE(m_seatsNum) * m_priceOfSeat);
    PRINT("Total amount of the available seats: ", TO_DOUBLE(m_availableSeatsNum) * m_priceOfSeat);
}

unsigned KupeWagon::getSeatsNum() const { return m_seatsNum; }
void KupeWagon::setSeatsNum(unsigned const &newSeatsNum) { m_seatsNum = newSeatsNum; }

unsigned KupeWagon::getAvailableSeatsNum() const { return m_availableSeatsNum; }
void KupeWagon::setAvailableSeatsNum(unsigned const &newAvailableSeatsNum) { m_availableSeatsNum = newAvailableSeatsNum; }

double KupeWagon::getPriceOfSeat() const { return m_priceOfSeat; }
void KupeWagon::setPriceOfSeat(double const &newPriceOfSeat) { m_priceOfSeat = newPriceOfSeat; }

void KupeWagon::saleTicket()
{
    if (m_availableSeatsNum == 0U)
    {
        PRINT("\nERROR\nWe can't sale any more tickets, because there is no free space in the wagon", '\n');
        return;
    }
    m_availableSeatsNum--;

    PRINT("Amount to be paid - ", m_priceOfSeat);
}

void KupeWagon::saleTickets(unsigned const &count)
{
    unsigned innerCounter{};
    while (m_availableSeatsNum != 0U)
    {
        m_availableSeatsNum--;
        innerCounter++;

        if (innerCounter == count)
            break;
    }

    PRINT("Count of sold tickets: ", innerCounter);
    PRINT("Amount to be paid - ", m_priceOfSeat * TO_DOUBLE(innerCounter));
    PRINT("", "");

    if (innerCounter < count)
    {
        PRINT("\nERROR\nSorry, but we are haven't any space in the wagon", "");
        PRINT("We had seats: ", innerCounter);
        PRINT("Requested quantity: ", count);
        PRINT("", "");
    }
}

void KupeWagon::printPriceList() const
{
    PRINT("\n/*------ This is a kupe wagon ------*/", "");
    std::cout << "Prices\nTicket: " << m_priceOfSeat << " rubles\n"
              << "Count of available seats: " << m_availableSeatsNum
              << "\nAvailable services and prices on them:\n";
    Wagon::printPriceList();
}

SleepWagon::SleepWagon() : m_seatsNum(kdefault_seatsNum),
                           m_availableSeatsNum(kdefault_availableSeatsNum),
                           m_priceOfSeat(kdefault_priceOfSeat) {}

SleepWagon::SleepWagon(unsigned const &newID,
                       unsigned const &newSeatsNum,
                       unsigned const &newAvailableSeatsNum,
                       double const &newPriceOfSeat) : m_seatsNum(newSeatsNum),
                                                       m_availableSeatsNum(newAvailableSeatsNum),
                                                       m_priceOfSeat(newPriceOfSeat)
{
    if (newAvailableSeatsNum > newSeatsNum)
    {
        PRINT("ERROR. Count of available seats can't be greater than total count of seats\n",
              "Exiting with status \'1\'");
        exit(EXIT_FAILURE);
    }
    setID(newID);
}

SleepWagon::~SleepWagon() { clearObj(*this); }

void SleepWagon::printInfo() const
{
    PRINT("\n/*====== This is a sleep wagon ======*/ ", "");
    PRINT("Wagon ID: ", getID());
    PRINT("Count of seats: ", m_seatsNum);
    PRINT("Count of available seats: ", m_availableSeatsNum);
    PRINT("Price of 1 seat: ", m_priceOfSeat);
    PRINT("Total amount of seats: ", TO_DOUBLE(m_seatsNum) * m_priceOfSeat);
    PRINT("Total amount of the available seats: ", TO_DOUBLE(m_availableSeatsNum) * m_priceOfSeat);
}

unsigned SleepWagon::getSeatsNum() const { return m_seatsNum; }
void SleepWagon::setSeatsNum(unsigned const &newSeatsNum) { m_seatsNum = newSeatsNum; }

unsigned SleepWagon::getAvailableSeatsNum() const { return m_availableSeatsNum; }
void SleepWagon::setAvailableSeatsNum(unsigned const &newAvailableSeatsNum) { m_availableSeatsNum = newAvailableSeatsNum; }

double SleepWagon::getPriceOfSeat() const { return m_priceOfSeat; }
void SleepWagon::setPriceOfSeat(double const &newPriceOfSeat) { m_priceOfSeat = newPriceOfSeat; }

void SleepWagon::saleTicket()
{
    if (m_availableSeatsNum == 0U)
    {
        PRINT("\nERROR\nWe can't sale any more tickets, because there is no free space in the wagon", '\n');
        return;
    }
    m_availableSeatsNum--;

    PRINT("Amount to be paid - ", m_priceOfSeat);
}

void SleepWagon::saleTickets(unsigned const &count)
{
    unsigned innerCounter{};
    while (m_availableSeatsNum != 0U)
    {
        m_availableSeatsNum--;
        innerCounter++;

        if (innerCounter == count)
            break;
    }

    PRINT("Count of sold tickets: ", innerCounter);
    PRINT("Amount to be paid - ", m_priceOfSeat * TO_DOUBLE(innerCounter));
    PRINT("", "");

    if (innerCounter < count)
    {
        PRINT("\nERROR\nSorry, but we are haven't any space in the wagon", "");
        PRINT("We had seats: ", innerCounter);
        PRINT("Requested quantity: ", count);
        PRINT("", "");
    }
}

void SleepWagon::printPriceList() const
{
    PRINT("\n/*====== This is a sleep wagon ======*/ ", "");
    std::cout << "Prices\nTicket: " << m_priceOfSeat << " rubles\n"
              << "Count of available seats: " << m_availableSeatsNum
              << "\nAvailable services and prices on them:\n";

    m_serv.m_waterPrice += PRICE_SURCHARGE_WATER;
    m_serv.m_teaPrice += PRICE_SURCHARGE_TEA;
    m_serv.m_coffeePrice += PRICE_SURCHARGE_COFFEE;
    m_serv.m_foodPrice += PRICE_SURCHARGE_FOOD;
    m_serv.m_winePrice += PRICE_SURCHARGE_WINE;

    Wagon::printPriceList();
}

GoodsWagon::GoodsWagon() : TYPE(GoodsWagon::types::COVERED_CARRIAGE) { setID(0); }
GoodsWagon::GoodsWagon(unsigned const &newID,
                       GoodsWagon::types const &newType) : TYPE(newType) { setID(newID); }
GoodsWagon::~GoodsWagon() {}

void GoodsWagon::printInfo() const
{
    PRINT("\n@@<<<<<< This is a goods wagon >>>>>>@@", "");
    PRINT("Wagon ID: ", getID());

    switch (TYPE)
    {
    case GoodsWagon::COVERED_CARRIAGE:
        PRINT("This is a covered carriage", "");
        break;
    case GoodsWagon::TANKER:
        PRINT("This is a tanker", "");
        break;
    case GoodsWagon::DUMPCAR:
        PRINT("This is a dumpcar", "");
        break;
    case GoodsWagon::TRANSPORTER:
        PRINT("This is a transporter", "");
        break;
    case GoodsWagon::CAR_CARRIAGE:
        PRINT("This is a car carriage", "");
        break;
    default:
        break;
    }
}

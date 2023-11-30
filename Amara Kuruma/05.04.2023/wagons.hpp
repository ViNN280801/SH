#ifndef WAGONS_HPP
#define WAGONS_HPP

#define PRINT(msg, x) std::cout << msg << x << std::endl
#define TO_DOUBLE(x) static_cast<double>(x)

#define NAME_WATER "Water"
#define NAME_TEA "Tea"
#define NAME_COFFEE "Coffee"
#define NAME_FOOD "Food (Potatoes with beef, buckwheat with chicken)"
#define NAME_WINE "Wine (Red, White)"

#define PRINT_PRICE(name, price) std::cout << name << " - " << price << " rub" << std::endl;

#define PRICE_SURCHARGE_WATER 50
#define PRICE_SURCHARGE_TEA 45
#define PRICE_SURCHARGE_COFFEE 30
#define PRICE_SURCHARGE_FOOD 150
#define PRICE_SURCHARGE_WINE 2500

struct Services;

class Wagon
{
private:
    unsigned m_ID;

protected:
    virtual void copyObj(Wagon const &);
    virtual void clearObj(Wagon &);

public:
    // Default constructor
    explicit Wagon();

    // Constructor with parameter
    explicit Wagon(unsigned const &);

    // Copy constructor
    explicit Wagon(Wagon const &);

    // Move constructor
    explicit Wagon(Wagon &&);

    // Assignment operator
    Wagon &operator=(Wagon const &);

    // Move assignment operator
    Wagon &operator=(Wagon &&) noexcept;

    // Destructor
    virtual ~Wagon();

    inline unsigned getID() const;
    inline void setID(unsigned const &);

    virtual void printInfo() const;

    virtual void saleTicket() = 0;
    virtual void saleTickets(unsigned const &) = 0;

    struct Services getServices() const;
    virtual void printPriceList() const;
};

class KupeWagon : Wagon
{
private:
    unsigned m_seatsNum;
    unsigned m_availableSeatsNum;
    double m_priceOfSeat;

    static const unsigned kdefault_seatsNum{36U};
    static const unsigned kdefault_availableSeatsNum{36U};
    static constexpr double kdefault_priceOfSeat{2000.0}; // in rubles

protected:
    virtual void copyObj(KupeWagon const &);
    virtual void clearObj(KupeWagon &);

public:
    explicit KupeWagon();
    explicit KupeWagon(unsigned const &, unsigned const &, unsigned const &, double const &);
    explicit KupeWagon(KupeWagon const &);
    explicit KupeWagon(KupeWagon &&w);

    KupeWagon &operator=(Wagon const &);
    KupeWagon &operator=(KupeWagon const &);
    KupeWagon &operator=(KupeWagon &&) noexcept;

    virtual ~KupeWagon();

    virtual void printInfo() const final;

    inline unsigned getSeatsNum() const;
    inline void setSeatsNum(unsigned const &);

    inline unsigned getAvailableSeatsNum() const;
    inline void setAvailableSeatsNum(unsigned const &);

    inline double getPriceOfSeat() const;
    inline void setPriceOfSeat(double const &);

    void saleTicket();
    void saleTickets(unsigned const &);

    virtual void printPriceList() const;
};

class SleepWagon : Wagon
{
private:
    unsigned m_seatsNum;
    unsigned m_availableSeatsNum;
    double m_priceOfSeat;

    static const unsigned kdefault_seatsNum{8U};
    static const unsigned kdefault_availableSeatsNum{8U};
    static constexpr double kdefault_priceOfSeat{3500.0}; // in rubles

public:
    explicit SleepWagon();
    explicit SleepWagon(unsigned const &, unsigned const &, unsigned const &, double const &);
    virtual ~SleepWagon();

    virtual void printInfo() const final;

    inline unsigned getSeatsNum() const;
    inline void setSeatsNum(unsigned const &);

    inline unsigned getAvailableSeatsNum() const;
    inline void setAvailableSeatsNum(unsigned const &);

    inline double getPriceOfSeat() const;
    inline void setPriceOfSeat(double const &);

    void saleTicket();
    void saleTickets(unsigned const &);

    virtual void printPriceList() const;
};

class GoodsWagon : Wagon
{
public:
    enum types
    {
        COVERED_CARRIAGE,
        TANKER,
        DUMPCAR,
        TRANSPORTER,
        CAR_CARRIAGE
    } TYPE;

    explicit GoodsWagon();
    explicit GoodsWagon(unsigned const &, GoodsWagon::types const &);
    virtual ~GoodsWagon();

    virtual void printInfo() const;
};

#endif // WAGONS_HPP

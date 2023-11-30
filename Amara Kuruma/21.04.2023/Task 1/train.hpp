#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <ctime>
#include <string>

class TrainList
{
private:
    struct Node
    {
        // Number of train
        int m_ID;

        // Destination (city)
        std::string m_destination;

        /* Format: "HH:MM:SS" */
        // Time of the departure
        std::string m_departureTime;

        // Time of train in the road
        std::string m_timeInRoad;
        /* ------------------ */

        enum TYPE
        {
            FAST,
            EXPRESS,
            PASSENGER
        } m_type;

        // Pointer to the next link of list
        Node *m_next;

    protected:
        // Zeroing out all data members
        void clear(Node &);

        // Copying all data members from one node to another
        void copy(const Node &);

        // "Moves" all data members from one node to another
        void move(Node &&);

    public:
        // Default ctor
        explicit Node() { clear(*this); }

        // Copy ctor
        explicit Node(const Node &node) { copy(node); }

        // Move ctor
        explicit Node(Node &&node) { move(std::move(node)); }

        // Ctor with 2 'Node' params. 'next' just zeroing out (special use)
        explicit Node(Node *nodeToClear, const Node &nodeToCopy)
        {
            clear(*nodeToClear);
            copy(nodeToCopy);
        }

        // Ctor with 2 'Node' params. 'next' just zeroing out (special use)
        explicit Node(Node *nodeToClear, Node &&nodeToCopy)
        {
            clear(*nodeToClear);
            copy(std::move(nodeToCopy));
        }

        // Copy-assignment operator
        Node &operator=(const Node &);

        // Move-assignment operator
        Node &operator=(Node &&);

        // Virtual destructor
        virtual ~Node();

        /* --- Getters and setters for all data members --- */
        inline int getID() const { return m_ID; }
        inline std::string getDest() const { return m_destination; }
        inline std::string getDepTime() const { return m_departureTime; }
        inline std::string getTimeInRoad() const { return m_timeInRoad; }
        inline TYPE getTrainType() const { return m_type; }

        inline void setID(int id) { m_ID = id; }
        inline void setDest(const std::string &dest) { m_destination = dest; }
        inline void setDepTime(const std::string &deptime) { m_departureTime = deptime; }
        inline void setTimeInRoad(const std::string &roadtime) { m_timeInRoad = roadtime; }
        inline void setTrainType(TYPE traintype) { m_type = traintype; }
        /* --- End of getters and setters --- */
    };

    // Points on the beginning of the list
    Node *m_head;

    // Size of list
    size_t m_size;

    // Helper variable. To create user's 'Node' object
    Node m_helperNode;

protected:
    // Helper method. Converts string to a time
    std::time_t str_to_time_t(const std::string &, const char *format = "%H:%M:%S") const;

    // Helper method. Converts time to a string
    std::string time_t_to_str(const std::time_t &, const char *format = "%H:%M:%S") const;

    // Helper method. Returns time represented as a string
    std::string getTime(const std::string &, const char *format = "%H:%M:%S") const;

    // Helper method. Prints data of 'Node' object
    void printNodeData(const Node &) const;

public:
    explicit TrainList() = default;
    explicit TrainList(const TrainList &) = default;
    explicit TrainList(TrainList &&) = default;
    TrainList &operator=(const TrainList &) = default;
    TrainList &operator=(TrainList &&) noexcept = default;
    virtual ~TrainList() = default;

    // Returns time represented as a string from user's input
    std::string getUsersTime(const char *format = "%H:%M:%S") const;

    // Checks if list is empty
    // Returns "true" if list is empty, otherwise - "false"
    inline bool empty() const;

    // Returns size of the list
    inline size_t size() const;

    // Erases all elements from the list
    void clear();

    // Adding element to the end of the list
    void push_back(const Node &);

    // Adding element to the end of the list
    void push_back(Node &&);

    // Adding element to the beginning of the list
    void push_front(const Node &);

    // Adding element to the beginning of the list
    void push_front(Node &&);

    // Inserting element on index position
    void insert(const Node &, size_t);

    // Removes last element
    void pop_back();

    // Removes first element
    void pop_front();

    // Removes element by index
    void remove_at(size_t);

    // Returns 'Node' object by index using operator[]
    Node &operator[](const size_t &index) const;

    // Prints node data by it's index
    void printData(size_t) const;

    // Prints all list data
    void printAllData() const;

    // User's inputted data will be added to the 'm_helperNode'
    Node &createTrainData();

    // Returns type of train represented as a 'Node::TYPE' type
    // 1 - Fast
    // 2 - Express
    // 3 - Passenger
    Node::TYPE int_to_train_type(int traintype) const;

    // User's inputted data will be added to the 'm_helperNode'
    Node &createTrainDataTest(const char *dest,
                              const char *deptime,
                              const char *timeinroad,
                              Node::TYPE trainType);

    // Prints only trains which are being sent to the Moscow city for a certain time period
    void printTrainsToMoscow(const char *, const char *) const;

    // Prints data of the train of train which destination point is Moscow by default
    void printMinTimeInRoadOfTrainCertainType(int traintype, char const *dest = "Moscow") const;
};

#endif // !TRAIN_HPP
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

#include "train.hpp"

void TrainList::Node::clear(Node &node)
{
    node.m_next = nullptr;
    node.m_ID = 0;
    node.m_destination = "";
    node.m_departureTime = "";
    node.m_timeInRoad = "";
    node.m_type = TYPE::FAST;
}

void TrainList::Node::copy(const Node &node)
{
    m_next = node.m_next;
    m_ID = node.m_ID;
    m_destination = node.m_destination;
    m_departureTime = node.m_departureTime;
    m_timeInRoad = node.m_timeInRoad;
    m_type = node.m_type;
}

void TrainList::Node::move(Node &&node)
{
    m_next = std::move(node.m_next);
    m_ID = std::move(node.m_ID);
    m_destination = std::move(node.m_destination);
    m_departureTime = std::move(node.m_departureTime);
    m_timeInRoad = std::move(node.m_timeInRoad);
    m_type = std::move(node.m_type);
}

TrainList::Node &TrainList::Node::operator=(const Node &node)
{
    // Self-assignment checking
    if (this == &node)
        return *this;

    // Copying all data to current object
    copy(node);

    return *this;
}

TrainList::Node &TrainList::Node::operator=(Node &&node)
{
    // Self-assignment checking
    if (this == &node)
        return *this;

    // "Moving" all data to current object
    move(std::move(node));

    return *this;
}

TrainList::Node::~Node()
{
    // Deallocating memory
    delete[] m_next;
    // Zeroing out all data members
    clear(*this);
}

std::time_t TrainList::str_to_time_t(const std::string &str, const char *format) const
{
    struct std::tm tm;
    std::istringstream ss(str);
    ss >> std::get_time(&tm, format);
    return mktime(&tm);
}

std::string TrainList::time_t_to_str(const std::time_t &time, const char *format) const
{
    char buf[32];
    std::strftime(buf, 32, format, std::localtime(&time));
    return buf;
}

std::string TrainList::getTime(const std::string &str, const char *format) const
{
    return time_t_to_str(str_to_time_t(str, format), format);
}

void TrainList::printNodeData(const Node &node) const
{
    std::cout << "Train ID: " << node.m_ID
              << "\nDestination point: " << node.m_destination
              << "\nDeparture time: " << getTime(node.m_departureTime)
              << "\nTime in road: " << getTime(node.m_timeInRoad) << std::endl;
    switch (node.m_type)
    {
    case Node::TYPE::FAST:
        std::cout << "Train type is fast\n\n";
        break;
    case Node::TYPE::EXPRESS:
        std::cout << "Train type is express\n\n";
        break;
    case Node::TYPE::PASSENGER:
        std::cout << "Train type is passenger\n\n";
        break;
    default:
        std::cout << "Train type is unknown\n\n";
        break;
    }
}

std::string TrainList::getUsersTime(const char *format) const
{
    std::string str;
    std::getline(std::cin, str, '\n');
    return getTime(str, format);
}

bool TrainList::empty() const { return m_size == 0; }

size_t TrainList::size() const { return m_size; }

void TrainList::clear()
{
    // Until size of list not null
    while (m_size)
        // Removing elements
        pop_front();
}

void TrainList::push_back(const Node &data)
{
    // If 1st element of list is empty
    if (!m_head)
        // Calling constructor of 'Node' struct
        m_head = new Node(data);
    // Otherwise 1st element is not empty
    else
    {
        // Initializing current pointer on object with head of list
        Node *pCurr{m_head};

        // Until we find last element which is points to null
        while (pCurr->m_next)
            // Assigning next link to current link of list
            pCurr = pCurr->m_next;

        // Writing data to next link of list
        pCurr->m_next = new Node(data);

        // Recording ID of train
        pCurr->m_next->m_ID = m_size;
    }

    // Incremeting size when we add element
    m_size++;
}

void TrainList::push_back(Node &&data)
{
    if (!m_head)
        m_head = new Node(std::move(data));
    else
    {
        Node *pCurr{m_head};
        while (pCurr->m_next)
            pCurr = pCurr->m_next;
        pCurr->m_next = new Node(data);
        pCurr->m_next->m_ID = m_size;
    }
    m_size++;
}

void TrainList::push_front(const Node &data)
{
    // Calling constructor of class 'Node' to initialize new head element
    m_head = new Node(m_head, data);

    // Incrementing size of list
    m_size++;
}

void TrainList::push_front(Node &&data)
{
    // Calling constructor of class 'Node' to initialize new head element
    m_head = new Node(m_head, std::move(data));

    // Incrementing size of list
    m_size++;
}

void TrainList::insert(const Node &data, size_t index)
{
    // If specified index is 0 -> pushing data to head of the list
    if (index == 0)
        push_front(data);
    // Otherwise -> find specified index -> pushing element to previous
    else
    {
        // Initializing previous pointer as head of the list
        Node *pPrev{m_head};

        // Iteration by indeces in list
        for (size_t index{}; index < index - 1UL; index++)
            // Assigning next pointer of to previous
            pPrev = pPrev->m_next;

        // Calling constructor of 'Node'
        // Assigning temporaly pointer to next link of list (from previous)
        pPrev->m_next = new Node(pPrev->m_next, data);

        // Incrementing size of list
        m_size++;
    }
}

void TrainList::pop_back()
{
    // Deleting last link of list
    remove_at(m_size - 1);
}

void TrainList::pop_front()
{
    // Initializing variable to store reference on first link of list
    Node *temp_head{m_head};

    // Assigning next element to head element, then we can delete head link
    m_head = m_head->m_next;

    // Deallocating memory of temporaly head of list
    delete temp_head;

    // Zeroing out this temporaly pointer
    temp_head = nullptr;

    // Decrementing size of list, because we are removing link of list
    m_size--;
}

void TrainList::remove_at(size_t _index)
{
    // If specified index is 0 -> deleting head of the list
    if (_index == 0)
        pop_front();
    // Otherwise -> find specified index -> deleting desired element
    else
    {
        // Initializing previous pointer as head of the list
        Node *pPrev{m_head};

        // Iteration by indeces in list
        for (size_t index{}; index < _index - 1; index++)
            // Assigning next pointer of to previous
            pPrev = pPrev->m_next;

        // Initializing pointer at element which we want to delete, which will points on next link of list
        Node *pDel{pPrev->m_next};

        // Assigning
        pPrev->m_next = pDel->m_next;

        // Deallocating memory from pointer at desired element to delete
        delete pDel;

        // Zeroing out this pointer
        pDel = nullptr;

        // Decrementing size of list
        m_size--;
    }
}

TrainList::Node &TrainList::operator[](const size_t &index) const
{
    // Initializing couter for iterate in list
    size_t counter{};

    // Initializing current pointer on object with head of list
    Node *pCurr{m_head};

    // Until we find last element which is points to null
    while (pCurr != nullptr)
    {
        // If we found desired element -> return it's data
        if (counter == index)
            return *pCurr;
        // Otherwise -> move to next link of list
        pCurr = pCurr->m_next;
        // And incrementing counter
        counter++;
    }
    // Throwing exception about out of range
    throw std::out_of_range("Error: out of range: there is no element with specifeid index");
}

void TrainList::printData(size_t index) const
{
    // Initializing couter for iterate in list
    size_t counter{};

    // Initializing current pointer on object with head of list
    Node *pCurr{m_head};

    // Until we find last element which is points to null
    while (pCurr)
    {
        // If we found desired element -> print it's data
        if (counter == index)
            printNodeData(*pCurr);
        // Otherwise -> move to next link of list
        pCurr = pCurr->m_next;
        // And incrementing counter
        counter++;
    }
}

void TrainList::printAllData() const
{
    // Initializing current pointer on object with head of list
    Node *pCurr{m_head};

    // Until we find last element which is points to null
    while (pCurr)
    {
        printNodeData(*pCurr);
        // Moving to next link of list
        pCurr = pCurr->m_next;
    }
}

TrainList::Node &TrainList::createTrainData()
{
    std::cout << "Enter destination point: ";
    std::getline(std::cin, m_helperNode.m_destination, '\n');
    std::cout << "Enter departure time (hh:mm:ss): ";
    m_helperNode.m_departureTime = getUsersTime();
    std::cout << "Enter time in road (hh:mm:ss): ";
    m_helperNode.m_timeInRoad = getUsersTime();

    int trainType{};
    for (;;)
    {
        std::cout << "1. Fast\n2. Express\n3. Passenger\nEnter type of train: ";
        std::cin >> trainType;
        if (trainType != 1 && trainType != 2 && trainType != 3)
            std::cout << "Error. Incorrect input. Try again." << std::endl;
        else
            break;
    }
    return m_helperNode;
}

TrainList::Node::TYPE TrainList::int_to_train_type(int traintype) const { return static_cast<TrainList::Node::TYPE>(traintype); }

TrainList::Node &TrainList::createTrainDataTest(const char *dest,
                                                const char *deptime,
                                                const char *timeinroad,
                                                Node::TYPE trainType)
{
    m_helperNode.m_destination = dest;
    m_helperNode.m_departureTime = getTime(deptime);
    m_helperNode.m_timeInRoad = getTime(timeinroad);
    m_helperNode.m_type = trainType;
    return m_helperNode;
}

void TrainList::printTrainsToMoscow(const char *time1, const char *time2) const
{
    unsigned counter{};

    // Initializing current pointer on object with head of list
    Node *pCurr{m_head};

    // Until we find last element which is points to null
    while (pCurr)
    {
        // If destination city is Moscow and departure time responds
        // to specified time interval -> print data
        if (pCurr->getDest() == "Moscow" &&
            (pCurr->getDepTime() >= time1 && pCurr->getDepTime() <= time2))
        {
            counter++;
            printNodeData(*pCurr);
        }
        // Moving to next link of list
        pCurr = pCurr->m_next;
    }

    if (counter == 0)
        std::cout << "There is no trains to Moscow with specified time interval" << std::endl;
}

void TrainList::printMinTimeInRoadOfTrainCertainType(int traintype, char const *dest) const
{
    unsigned counter{};
    Node *pCurr{m_head};
    std::vector<std::string> minTimeVec;
    while (pCurr)
    {
        if (pCurr->getDest() == dest && pCurr->getTrainType() == int_to_train_type(traintype))
        {
            minTimeVec.push_back(pCurr->getTimeInRoad());
            counter++;
        }
        pCurr = pCurr->m_next;
    }

    if (counter == 0)
    {
        std::cout << "There is no trains to " << dest << " with specified type of train" << std::endl;
        return;
    }

    std::string minTime{*minTimeVec.cbegin()};

    // Find min time in vector
    for (size_t i{}; i < minTimeVec.size(); i++)
    {
        if (minTimeVec.at(i) < minTime)
            minTime = minTimeVec.at(i);
    }

    pCurr = m_head;
    while (pCurr)
    {
        if (pCurr->getDest() == dest &&
            pCurr->getTrainType() == int_to_train_type(traintype) &&
            pCurr->getTimeInRoad() == minTime)
        {
            std::cout << "Minimal time in road: " << std::endl;
            printNodeData(*pCurr);
        }
        pCurr = pCurr->m_next;
    }
}

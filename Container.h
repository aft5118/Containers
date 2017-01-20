// Header file for Abstract Containers
// Instead of "container" referring to a linked list
// here it refers to the more literal box or bag
// 
// This header file describes a class hierarchy for
// various$ kinds of containers with different behaviors,
// but all sharing the same overall interface,
// which represents what it means to be a container.
#include <iostream>
#include <list>		// just for convenience in this tutorial
#include <iterator>	// just for convenience in this file
using namespace std;

class Container
{
	// protected: accessible to this class and derived classes
protected:			// good practice to protect this data
	string name;		// what is this container called
	int size;		// how big is it now?
	int capacity;		// how much can it hold?
	int filled;		// how much of that capacity is filled?

private:			// only for Container class and its methods
	Container *heldBy;		// what is this within?
	list<Container *> contents;	// what is inside (initially empty)
	void transferTo(Container *dest);// private method for internal use only

public:			// the public interface
	Container(string n, int s, int c) :	// constructor to initialize
		name(n), size(s), capacity(c), 	// initialize with givens
		filled(0), heldBy(NULL) {}	// and clear the rest
	Container(Container *things[], int numItems) :
		name("room"), size(10000), capacity(10000),   // big room
		filled(0), heldBy(NULL)
	{
		for (int i = 1; i < numItems; i++)	// special initializer
		{
			contents.push_back(things[i]);//	for room, to start
			things[i]->heldBy = this;	//      item is in room
		}
	}

	// a few accessor methods if we need them
	string getName() const
	{
		return name;		// good to publicize this
	}
	int getSize() const
	{
		return size;
	}
	Container *getHolder() const
	{
		return heldBy;
	}
	Container *first() const
	{
		return contents.front();
	}
	void printInventory() const;
	bool isInside(Container *holder) const;
	virtual bool insert(Container *thing);
	virtual bool remove(Container *thing, Container *room);
};

class Bag : public Container		// a Bag is container
{					// almost the same constructor
public:
	Bag(string n, int s, int c) : Container(n, s, c) { }
	// overriding these two methods
	bool insert(Container *thing);
	bool remove(Container *thing, Container *room);
};

class Chest : public Container		// a chest is container
{
private:
	Container *chestKey;		// may or may not require a key
public:				// a little more to initialize
	Chest(string n, int s, int c, Container *k) :
		Container(n, s, c), chestKey(k) { }
	bool remove(Container *thing, Container *room);
};

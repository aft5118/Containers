// Containers Implementation file
// An abstraction of containers in the more literal sense.
// This solution uses inheritance to share common behaviors
// and derived classes for modifying behaviors
#include "container.h"
#include <string>

// insert
// try to put the specified thing into this container
// Parameters:
// 	thing 	(modified Container)	item to insert
bool Container::insert(Container *thing)
{
	bool success = false;
	if (capacity == 0)
		cout << "The " << name << " is not a container! " << endl;
	else if (thing == this)
		cout << "The " << name << " cannot be placed inside itself." << endl;
	else if (thing->isInside(this))
		cout << "The " << thing->getName() << " is already inside the " << name << endl;
	else if (isInside(thing))
		cout << "The " << name << " is currently inside the " << thing->getName() << endl;
	else if (thing->size + filled > capacity)
		cout << "The " << thing->getName() << " would not fit in the " << name << endl;
	else
	{
		cout << "Putting " << thing->getName() << " into " << name << endl;
		thing->transferTo(this);
		success = true;
	}
	return success;
}

// remove
// try to remove an item from a container
// Parameters:
// 	thing 	(modified Container)	item to insert
// 	room	(modified Container)	where to place item afterwards
bool Container::remove(Container *thing, Container *room)
{
	bool success = false;
	if (thing->getHolder() != this)
		cout << "The " << thing->getName() << " is not inside the " << name << endl;
	else
	{
		cout << "Getting " << thing->getName() << " out of " << name << endl;
		thing->transferTo(room);
		success = true;
	}
	return success;
}

//  These methods will be overridden to support new features
//  An empty bag takes very little space, since it can be flattened
//  But the volume of the bag increases as things are placed inside it.
bool Bag::insert(Container *thing)
{
	bool success = Container::insert(thing);
	if (success)				// bag increases in size
		size += thing->getSize();	//    as things are placed inside it
	return success;
}

bool Bag::remove(Container *thing, Container *room)
{
	bool success = thing->getHolder() == this;
	Container *firstThing, *temp;
	if (success)
	{
		firstThing = first();
		temp = new Container("temporary stack", 10000, 10000);
		while (first() != thing)
			Container::remove(first(), temp);
		Container::remove(thing, room);
		if (firstThing != thing)		// return anything we took out
			while (first() != firstThing)
				Container::insert(temp->first());
		size -= thing->getSize();
	}
	else
		cout << "The " << thing->getName() << " is not in the " << name << endl;
	return success;
}

//  A chest can only be unlocked if there is a key available
//  For this case, the key must be out in the open (not in another object)
bool Chest::remove(Container *thing, Container *room)
{
	bool success = false;
	if (chestKey != NULL && chestKey->getHolder() == room)
		success = Container::remove(thing, room);
	else
		cout << "The key to this chest is missing." << endl;
	return success;
}

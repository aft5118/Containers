// A driver program to try out the Container class
// It would be user friendly to allow input along the lines of
// "get item from bag" or "put item in bag", but that step
// will be skipped to keep the important relatively simple.
// A later topic would facilitate accessing items by their name.

#include "container.h"

//  Just a couple short wrapper functions to shorten main()
void put(Container *, Container *);
void get(Container *, Container *, Container *);

int main()
{
	Container *things[11] =
	{ NULL,					// do the room last
	new Container("elephant", 1000, 0),	// the elephant in the room
	new Container("crate", 120, 100),	// a crate to hold things
	new Container("television", 60, 0),	// sizable television
	new Container("stereo", 60, 0),	// sizable stereo
	new Bag("sack", 2, 150),		// a simple bag to hold things
	new Bag("coin purse", 2, 1),		// a much smaller bag
	new Chest("packing box", 70, 65, NULL),
	new Bag("bag of gold!", 5, 0),	// treasure for a chest
	new Container("unmarked key", 1, 0) };// a key for the chest

	// doing these separately, since they refer to other Things
	things[10] = new Chest("treasure chest", 12, 10, things[9]);
	things[0] = new Container(things, 11);

	put(things[8], things[10]);	// load up the treasure
	put(things[9], things[6]);	// put key in purse
	put(things[4], things[7]);	// put stereo in packing box
	put(things[7], things[2]);	// put packed stereo into crate
	put(things[1], things[5]);	// put elephant in the sack
	put(things[3], things[2]);	// put TV into crate with the stereo
	things[2]->printInventory();	// let's see what we have
	cout << endl;

	//return 0;				// first checkpoint

	put(things[5], things[2]);	// put the sack into the crate too
	put(things[2], things[5]);	// and put the crate into the sack
	put(things[5], things[2]);	// and put the sack into the crate again
	things[2]->printInventory();	// let's see what we have
	things[5]->printInventory();	// is the sack empty?
	cout << endl;

	// 0;				// second checkpoint

	put(things[6], things[2]);	// toss in the purse with the key
	put(things[9], things[2]);	// and try to insert the key again
	things[6]->printInventory();	// is the count purse empty?
	cout << endl;

	//return 0;				// third checkpoint

	get(things[5], things[2], things[0]);	// take the sack back out
	put(things[3], things[2]);		// TV should not fit
	put(things[3], things[5]);		// put the TV in the sack
	put(things[5], things[2]);		// TV still should not fit
	get(things[3], things[5], things[0]);	// unwrap the TV
	put(things[5], things[2]);		// empty bag still fits
	things[2]->printInventory();		// what do we have now?
	things[0]->printInventory();		// see what is not stored
	cout << endl;

	//return 0;					// fourth checkpoint

	get(things[8], things[10], things[0]);	// and try to get it out
	get(things[6], things[2], things[0]);	// get the coin purse out
	get(things[9], things[6], things[0]);	// so we can get the key
	get(things[8], things[10], things[0]);	// so we can get the treasure
	things[0]->printInventory();		// more things in the room
	return 0;
}

//  A couple short function to try the functionality of 
//  putting things into other things.   A more real program
//  would have an interface more resembling a human language,
//  but that's a problem for another day.
//
//  put:
//  put one item into another, using the array subscripts from above
void put(Container *item, Container *holder)
{
	if (holder->insert(item))
		cout << "Succeeded" << endl;
	else
		cout << "Failed" << endl;
}

//  get:
//  get one item out of another, using the array subscripts from above
//  obtained items will be transferred to the room (array element 0)
void get(Container *item, Container *holder, Container *room)
{
	if (holder->remove(item, room))
		cout << "Succeeded" << endl;
	else
		cout << "Failed" << endl;
}

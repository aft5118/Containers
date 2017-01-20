// Containers Implementation file
// An abstraction of containers in the more literal sense.
// This solution uses inheritance to share common behaviors
// and derived classes for modifying behaviors
#include "container.h"
#include <string>

// transferTo
// transfers one item to a new container,
// updating the data structures as necessary.
// This is a private method for Container class only,
// which updates the other private data structures.
// The public interface is through the other methods.
void Container::transferTo(Container *dest)
{
	heldBy->contents.remove(this);	// not in that container
	heldBy->filled -= size;		// less space occupied there
	dest->contents.push_front(this);	// but in that one
	dest->filled += size;		// more space occupied here
	heldBy = dest;			// update containing location
}

// isInside
// Is this thing inside the one defined in the argument?
bool Container::isInside(Container *other) const
{
	return heldBy == other || (heldBy != NULL && heldBy->isInside(other));
}

void Container::printInventory() const
{
	cout << name << "(" << capacity << ") contains: ";
	for (list<Container *>::const_iterator p = contents.begin();
		p != contents.end(); ++p)
		cout << (*p)->getName() << "(" << (*p)->size << "), ";
	if (contents.begin() == contents.end())
		cout << "Nothing!";
	cout << endl;
}

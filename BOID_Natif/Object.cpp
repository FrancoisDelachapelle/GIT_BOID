#include "Object.h"

bool Object::Equals(const Object& o)
{
	return this == &o;
}
bool Object::Equals(const Object* o)
{
	return this == o;
}

bool Object::operator==(const Object& o)
{
	return Equals(o);
}
bool Object::operator==(const Object* o)
{
	return Equals(o);
}
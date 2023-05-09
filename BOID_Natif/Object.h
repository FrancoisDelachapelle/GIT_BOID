#pragma once

class Object
{
public:
	Object() = default;
	Object(Object&&) = default;
	Object(const Object&) = default;
public:
	virtual bool Equals(const Object& o);
	virtual bool Equals(const Object* o);

public:
	bool operator==(const Object& o);
	bool operator==(const Object* o);
};
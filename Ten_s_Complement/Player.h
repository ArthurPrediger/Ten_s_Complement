#pragma once

#include "Location2D.h"

class World;

class Player
{
public:
	Player(Location2D location, World* world);

	void UpdateWorldLocation(Location2D displacement);
	Location2D GetLocation() const
	{
		return loc_;
	}
	int GetNumber() const
	{
		return number_;
	}
	void SetNumber(int number)
	{
		number_ = number;
	}
private:
	Location2D loc_;
	char number_;
	World* world_;
};
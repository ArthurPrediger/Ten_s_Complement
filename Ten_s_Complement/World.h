#pragma once

#include <string>
#include "Location2D.h"

class World
{
public:
	World(Location2D extent);

	void Draw() const;
	Location2D GetExtent() const
	{
		return extent_;
	}
	std::string& GetContentRef()
	{
		return content_;
	}
private:
	Location2D extent_;
	std::string content_;
};
#pragma once
#include "Common.hpp"
#include "PetitGame.hpp"

class InterMisson
{
public:
	virtual void update();
	virtual void draw(const RenderTexture& gamescene,double fade) const;
};

# pragma once
# include "PetitGame.hpp"

class SaveTheEarth : public PetitGame
{
public:
	const Texture earth{ U"🌏"_emoji };
	const Texture moon{ U"🌝"_emoji };
	const Texture comet{ U"☄️_emoji" };
	double time = 0;

	SaveTheEarth():PetitGame{ U"地球救済" } {}
	void init() override;
	void update(double t, double gameSpeed) override;
	void draw() const override;
	bool isClear() override { return true; }
};



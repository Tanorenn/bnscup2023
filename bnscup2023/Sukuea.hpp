#pragma once
# include "PetitGame.hpp"

class Sukuea : public PetitGame
{
public:
	Sukuea();
	void init() override;
	void update(double t, double gameSpeed) override;
	void draw() const override;
	bool isClear() override;

private:

};

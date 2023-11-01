# pragma once
# include "PetitGame.hpp"

class FireFighting : public PetitGame
{
public:
	const Texture fire{ U"🔥"_emoji };
	const Texture drop{ U"💦"_emoji };
	const Array<Point> dxy = { {0,1},{1,0},{0,-1},{-1,0} };
	const int32 width = 3;
	const int32 height = 3;
	bool isSaved;
	Grid<int32> map;
	Font font{ 24, Typeface::Regular };
	const Point size{50,50 };
	FireFighting();
	void init() override;
	void update(double t, double gameSpeed) override;
	void draw(double t, double gameSpeed) const override;
	Point getPos(const Point p) const;
	bool isClear() override;
	int32 p2i(const Point p) const;
	Grid<bool> isConnected() const;
	bool isSolved() const;
};



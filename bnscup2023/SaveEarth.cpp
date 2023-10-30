# include "SaveEarth.hpp"

SaveTheEarth::SaveTheEarth()
	:PetitGame{ U"地球救済"}
{}

void SaveTheEarth::init() {
}

void SaveTheEarth::update(double t, double gameSpeed) {
	double dt = Scene::DeltaTime() * gameSpeed;
	time = t;
}

void SaveTheEarth::draw() const {
	Rect(0, 0, 256, 256).draw(Palette::Black);
	Print << time;
	earth.scaled(0.4).rotated(360_deg * time).drawAt(128, 128);
	const double rad = Atan2(128 - Cursor::Pos().y, 128 - Cursor::Pos().x) - 90_deg;
	const Vec2 moon_pos = OffsetCircular(Vec2(128, 128), 64, rad);
	moon.scaled(0.3).drawAt(moon_pos);
}

bool SaveTheEarth::isClear() {
	return true;
}

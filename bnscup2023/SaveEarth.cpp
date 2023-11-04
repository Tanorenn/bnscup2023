# include "SaveEarth.hpp"

SaveTheEarth::SaveTheEarth()
	:PetitGame{ U"地球救済",U"SaveTheEarthBGM"}
{}

void SaveTheEarth::init() {
	ballRad = Random(360) * 1_deg;
	ballDist = 200;
	time = 0;
	isSaved = false;
	isBurn = false;
	stopwatch.reset();
	clearT = 0;

	starPos.clear();
	starSize.clear();
	for (auto i : step(10))
	{
		starPos << Vec2{ Random(0, 255), Random(0, 255) };
		starSize << Random(0.5, 2.0);
	}

	CursorStyle = U"Point";
}

void SaveTheEarth::update(double t, double gameSpeed) {
	double dt = Scene::DeltaTime() * gameSpeed;
	if (isSaved) {
		ballDist += dt * 500;
	}
	else {
		ballDist = 200 * (1 - t);
	}
	
	ballRad += 90_deg * dt;
	const double mouseRad = Atan2(128 - Cursor::Pos().y, 128 - Cursor::Pos().x) - 90_deg;
	moonPos = OffsetCircular(Vec2(128, 128), 64, mouseRad);
	ballPos = OffsetCircular(Vec2(128, 128), ballDist, ballRad);
	Circle moonCircle(moonPos, 64 * 0.3);
	Circle ballCircle(ballPos, 64 * 0.2);
	Circle earthCircle(128, 128, 64 * 0.3);
	if (moonCircle.intersects(ballCircle)){
		isSaved = true;
		stopwatch.start();
	}
	if (t > 0.8 && earthCircle.intersects(ballCircle)) {
		isBurn = true;
	}
	clearT = Min(stopwatch.sF() * 4 * gameSpeed, 1.0);
}


void SaveTheEarth::draw(double t, double gameSpeed) const {
	Rect(0, 0, 256, 256).draw(Palette::Black);
	for (auto i : step(starPos.size()))
	{
		Circle{ starPos[i], starSize[i] }.draw(Palette::White.withAlpha(100));
	}

	if (isBurn) {
		earth.scaled(0.3).rotated(360_deg * t).drawAt(Vec2(128, 128).moveBy(Random(-10, 10), Random(-10, 10)), ColorF{1.0f, 1.0f - (t-0.8f)/0.2f,1.0f - (t - 0.8f) / 0.2f });
	}else {
		earth.scaled(0.3).rotated(360_deg * t).drawAt(128, 128);
	}


	moon.scaled(0.3).drawAt(moonPos, ColorF(1, 1 - clearT));
	leftMoon.scaled(0.3).rotated(30_deg).drawAt(moonPos, ColorF(1, clearT));
	soccerBall.scaled(0.2).drawAt(ballPos);
	sun.resized(150, 150).drawAt(-75 + clearT * 75, -50 + clearT * 75);

}

bool SaveTheEarth::isClear() {
	return isSaved;
}

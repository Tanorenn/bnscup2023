# include "SaveEarth.hpp"

SaveTheEarth::SaveTheEarth()
	:PetitGame{ U"地球救済"}
{}

void SaveTheEarth::init() {
	ballRad = Random(0, 360) * 1_deg;
	ballDist = 200;
	time = 0;
	// ボールの角度
	ballRad = 0;
	// ボールの中心からの距離
	ballDist = 0;
	isSaved = false;
	isBurn = false;
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
	}
	if (t > 0.8 && earthCircle.intersects(ballCircle)) {
		isBurn = true;
	}
}


void SaveTheEarth::draw(double t, double gameSpeed) const {
	Rect(0, 0, 256, 256).draw(Palette::Black);
	if (isBurn) {
		earth.scaled(0.3).rotated(360_deg * t).drawAt(Vec2(128, 128).moveBy(Random(-10, 10), Random(-10, 10)), ColorF{1.0f, 1.0f - (t-0.8f)/0.2f,1.0f - (t - 0.8f) / 0.2f });
	}else {
		earth.scaled(0.3).rotated(360_deg * t).drawAt(128, 128);
	}


	moon.scaled(0.3).drawAt(moonPos);
	soccerBall.scaled(0.2).drawAt(ballPos);

}

bool SaveTheEarth::isClear() {
	return isSaved;
}

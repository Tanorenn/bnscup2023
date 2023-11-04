# include "Rain.hpp"

DreamyRainy::DreamyRainy()
	:PetitGame{ U"DreamyRainy", U"DreamyRainyBGM" }
{}

void DreamyRainy::init() {
	reajuPos = Vec2{0, 200};
	reajuSize = 32;
	cloudSize = { 48, 48 };
	umbrellaSize = 72;
	dropX = Random(128, 256-32);
	dropTime = 0.1;
	dropPos.clear();
	dropSize = 8;
	isSaved = true;
	manPos = reajuPos;
}


void DreamyRainy::update(double t, double gameSpeed) {
	double dt = Scene::DeltaTime() * gameSpeed;
	reajuPos.x = 256 * t;
	if (isSaved) {
		manPos.x = reajuPos.x;
	}
	else {
		manPos.x -= dt*300;
	}
	umbrellaPos = {Cursor::Pos().x, 140};
	if (dropTime < t){
		dropTime += 0.0125f;
		dropPos << Vec2{ dropX + Random(-40,40), 32};
	}
	Circle u(umbrellaPos, umbrellaSize/3); //アンブレラ
	Circle r(reajuPos, reajuSize / 2); //レアジュ
	for (Vec2& p : dropPos) {
		p.moveBy(0, dt * 1500);
		Circle c(p, dropSize);
		if (u.intersects(c)) {
			p.y = 300;
		}
		if (r.intersects(c)) {
			isSaved = false;
		}
	}
}


void DreamyRainy::draw(double t, double gameSpeed) const {
	Rect(0, 0, 256, 256).draw(Palette::Darkblue);
	umbrella.resized(umbrellaSize).drawAt(umbrellaPos);
	if (isSaved) {
		reaju.resized(reajuSize).drawAt(reajuPos);
	}
	else {
		woman.resized(reajuSize).drawAt(reajuPos);
		man.resized(reajuSize).drawAt(manPos);
	}
	(isSaved?love:brokenLove).resized(reajuSize).drawAt(reajuPos.movedBy(0, - 20 + Periodic::Jump0_1(1s)*-10));
	for (int32 x = 0; x <= 256; x += 32) {
		const double theta = (x + t * 360_deg);
		const Vec2 pos = OffsetCircular{ Vec2{0,0}, 5, theta };
		const Vec2 origin{ x,32 };
		(Abs(dropX - x) < 48 ? cloudRain : cloud).resized(cloudSize).drawAt(origin.movedBy(pos));
	}
	for (const Vec2& p : dropPos) {
		drop.resized(dropSize).drawAt(p, ColorF(1,1,1, p.y<64?(p.y-32)/32.0:1.0));
	}

	Rect(0, reajuPos.y + reajuSize / 2, 256, reajuPos.y + reajuSize / 2).draw(Palette::Brown);
}

bool DreamyRainy::isClear() {
	return isSaved;
}

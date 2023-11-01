# include "Explosion.hpp"

Explosion::Explosion()
	:PetitGame{ U"爆弾停止"}
	,words{width, height}
{}

void Explosion::init() {
	correctPos = { Random(width-1), Random(height-1) };
	size = 120;
	width = 2;
	height = 2;
	clicked = { -1,-1 };
	isSaved = false;
	for (Point p : step({ width, height })) {
		words[p] = correctPos == p ? correct.choice() : wrong.choice();
	}
}

void Explosion::update(double t, double gameSpeed) {
	double dt = Scene::DeltaTime() * gameSpeed;
	for (Point p : step({ width, height }))
	{
		Rect rect(getPos(p), size, size);
		if (t < 0.1) continue;
		if (rect.leftClicked() || rect.rightClicked()){
			clicked = p;
		}
	}
	if (isNearEnd(t)) {
		isSaved = (clicked == correctPos);
	}
}


void Explosion::draw(double t, double gameSpeed) const {
	int16 time = 8 - Ceil(t * 8);
	// String rest = U"0:0" + Format(time);
	// boldFont(rest).drawAt(Point(128 + 54, 148), Palette::Tomato);
	if (isNearEnd(t) && not isSaved){
		collision.resized(300*EaseOutBack((t-7.0f/8.0f)*8.0f)).drawAt(Point(128, 128).movedBy(RandomVec2()*4));
	}
	else {
		bomb.resized(256 - time * 10).drawAt(Point(128, 128).movedBy(isSaved ? Vec2(0,0) : RandomVec2() * 2), ColorF(1.0f, isSaved ? 1.0f :Periodic::Jump0_1(1s), isSaved?1.0f:Periodic::Jump0_1(1s)));
	}
	for (Point p : step({ width, height }))
	{
		if (p == clicked) {
			button2.resized(size).draw(getPos(p),ColorF(1.0f,1.0f,1.0f,0.8f));
		}
		else {
			button1.resized(size).draw(getPos(p), ColorF(1.0f, 1.0f, 1.0f, 0.8f));
		}
		font(words[p]).drawAt(getPos(p) + Point(size / 2, size / 2), ColorF(1.0f, 0.1f, 0.1f, 0.8f));
	}
	
}

Point Explosion::getPos(const Point p) const{
	return p* size + Point(8, 8);
}


bool Explosion::isClear() {
	return isSaved;
}

bool Explosion::isNearEnd(const double &t) const{
	return (t > 7.0f/ 8.0f);
}

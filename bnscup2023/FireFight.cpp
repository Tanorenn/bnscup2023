# include "FireFIght.hpp"

FireFighting::FireFighting()
	:PetitGame{ U"戦略鎮火" }
	, map{ width,height }
{}

void FireFighting::init() {
	Array<int32> id = { 0b1100, 0b0110, 0b0011, 0b1101, 0b1110, 0b0111, 0b1011, 0b1101, 0b0000 };
	id.shuffle();
	isSaved = false;
	assert(id.size() == width * height);
	for (int32 i = 0; i < width; ++i) {
		for (int32 j = 0; j < height; ++j) {
			map[Point(i,j)] = id[(i * width + j)];
		}
	}
}

void FireFighting::update(double t, double gameSpeed) {
	double dt = Scene::DeltaTime() * gameSpeed;

	if (isSaved)return;
	// クリックされたところが空欄に隣り合っていれば交換する
	Point blank;
	Point click(-99824,-4353);
	for (Point p : step({ width, height })) {
		if (map[p] == 0) {
			blank = p;
		}
		Rect rect(getPos(p), size);
		if (rect.leftClicked()) {
			click = p;
		}
	}
	// マンハッタン距離
	int32 dist = blank.manhattanDistanceFrom(click);
	if (dist == 1) {
		map[blank] = map[click];
		map[click] = 0;
	}
	const auto connected = isConnected();
	bool c = false;
	// 右端の列を見て、水が入っているかどうかを判定する
	for (int32 i = 0; i < height; ++i) {
		if (connected[Point(width-1,i)] && (map[Point(width - 1, i)] & (1 << 1))) {
			c = true;
		}
	}
	if (c) {
		isSaved = true;
	}
}


void FireFighting::draw(double t, double gameSpeed) const {
	const auto connected = isConnected();

	Point firePos{ 220,128 };
	int32 fireSize = 96;
	if (isSaved) {
		for (int32 i = 0; i < 10; ++i) {
			drop.resized(96).drawAt(firePos.movedBy(RandomVec2() * 10));
		}
		fireSize = 96*(1.0f - t);
	}
	else {
		font(U"炎上").drawAt(firePos, ColorF(0.8f, 0.1f, 0.1f, Periodic::Sine0_1(1.5s)));
	}
	fire.resized(fireSize).drawAt(firePos.movedBy(-20,40).movedBy(RandomVec2() * 10));
	fire.resized(fireSize).drawAt(firePos.movedBy(20,40).movedBy(RandomVec2() * 10));
	fire.resized(fireSize).drawAt(firePos.movedBy(0,-40).movedBy(RandomVec2() * 10));

	// 0,0の左から水が入る
	Line(getPos(Point(-1, 0)) + size / 2, getPos(Point(-1, 0)) + size / 2 + Point(1, 0) * size / 2).draw(8, Palette::Black).draw(6, Palette::Lightskyblue);
	for (int32 i = 0; i < height; ++i)Line(getPos(Point(width, i)) + size / 2, getPos(Point(width, i)) + size / 2 + Point(-1, 0) * size / 2).draw(8, Palette::Black).draw(6, connected[Point(width-1,i)] && (map[Point(width-1,i)] & (1 << 1)) ? Palette::Lightskyblue : Palette::Black);
	for (Point p : step({ width, height }))

	{
		if (map[p] == 0) {
			Rect(getPos(p), size).draw(Palette::Darkgray).drawFrame(3, 0, Palette::Black);
		}
		else {
			Rect(getPos(p), size).draw(Palette::White).drawFrame(2, 0, Palette::Black);
			// map[p]に応じて描画
			for (int32 i = 0; i < 4; ++i) {
				if (map[p] & (1 << i)) {
					Line(getPos(p) + size / 2, getPos(p) + size / 2 + dxy[i] * size / 2).draw(8, Palette::Black).draw(6, connected[p] ? Palette::Lightskyblue : Palette::Black);
				}
				Circle(getPos(p) + size / 2, 8).draw(connected[p] ? Palette::Lightskyblue : Palette::Gray).drawFrame(1, 0, Palette::Black);
			}
		}
	}
}


Point FireFighting::getPos(const Point p) const {
	return p * size + Point(20, 53);
}


bool FireFighting::isClear() {
	return true;
}

Grid<bool> FireFighting::isConnected() const{
	DisjointSet<int32> ds(width * height + 1);

	for (Point p : step({ width,height })) {
		for (int32 i = 0; i < 4; ++i) {
			if (map[p] & (1 << i)) {
				Point q = p + dxy[i];
				// qの反対側があるか
				int32 j = (i + 2) % 4;
				if (p2i(q) < 0 )continue;
				if (map[q] & (1 << j)) {
					Print << p << U" " << q;
					ds.merge(p2i(p), p2i(q));
				}
			}
		}
	}
	Grid<bool> res(width,height);
	for (Point p : step({ width, height })) {
		res[p] = (map[0][0] & (1 << 3)) && ds.connected(p2i({0,0}), p2i(p));
	}
	return res;
}

int32 FireFighting::p2i(const Point p) const{
	if (p.x < 0 || p.y < 0 || p.x >= width || p.y >= height)return -1;
	return p.x * width + p.y;
}


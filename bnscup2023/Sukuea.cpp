# include "Sukuea.hpp"

Sukuea::Sukuea()
	:PetitGame{ U"すくえあ",U"すくえあ" },
	polygons{ 5 },
	colors{ 5 }
{}

void Sukuea::init() {
	Array<Point> pos{
		Point{ 50, 50 },
		Point{ 90, 90 },
		Point{ 140, 50 },
		Point{ 50, 140 },
		Point{ 140, 140 }
	};
	pos.shuffle();
	const Size Areasize{ 50, 50 };
	for (int i = 0; i < polygons.size(); i++){
		polygons[i] = Shape2D::Ngon(i + 3, Random(25, 50), RandomPoint(Rect{ pos[i],Areasize }));
		colors[i] = HSV{ Random(360),Random(0.7,1.0),Random(0.7,1.0) };
	}
	dig = 0;
}

void Sukuea::update(double t, double gameSpeed) {
	for (int i = 0; i < polygons.size(); i++) {
		polygons[i].rotateAt(polygons[i].centroid(), dig);
	}
}

void Sukuea::draw(double t, double gameSpeed) const {
	double dig = 12_deg * (1.0 - t) * (1.0 - t);
	for (int i = 0; i < polygons.size(); i++) {
		polygons[i].rotatedAt(polygons[i].centroid(), dig).draw(HSV{colors[i],0.6}).drawFrame(5, colors[i]);
	}
}

bool Sukuea::isClear() {
	return true;
}

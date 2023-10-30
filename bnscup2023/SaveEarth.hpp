# include "PetitGame.hpp"

class SaveTheEarth : public PetitGame
{
public:
	Texture texture;
	const Texture earth{ U"🌏"_emoji };
	const Texture moon{ U"🌝"_emoji };
	const Texture comet{ U"☄️_emoji" };
	double time = 0;

	SaveTheEarth()
		:PetitGame{ U"地球救済" },
		texture{ TextureAsset(U"example_test") } {
	}
	void init() override {}
	void update(double t, double gameSpeed) override {
		double dt = Scene::DeltaTime() * gameSpeed;
		time = t;
	}
	void draw() const override {
		Rect(0, 0, 256, 256).draw(Palette::Black);
		Print << time;
		earth.scaled(0.4).rotated(360_deg * time).drawAt(128, 128);
		const double rad = Atan2(128 - Cursor::Pos().y, 128 - Cursor::Pos().x) - 90_deg;
		const Vec2 moon_pos = OffsetCircular(Vec2(128, 128), 64, rad);
		moon.scaled(0.3).drawAt(moon_pos);

	}
	bool isClear() override { return true; }
	//bool loadAssets() override {
	//	if (not TextureAsset::IsRegistered(U"example_test")) {
	//		TextureAsset::Register(U"example_test", U"example/windmill.png");
	//	}
	//	TextureAsset::LoadAsync(U"example_test");
	//	return TextureAsset::IsReady(U"example_test");
	//}
	//void releaseAssets() override {
	//	TextureAsset::Release(U"example_test");
	//}

};



#pragma once
# include "PetitGame.hpp"

class Kingyo : public PetitGame
{
public:
	Kingyo() :PetitGame{ U"金魚すくいだドン！" }
	{}

	void init() override
	{
		const Array<Array<double>> timings = {
			{0.5,0.75},
			{0.5625,0.8125},
			{0.375,0.5625,0.75}
		};
		timing = timings.choice();
		isGet = Array<double>(timing.size(), -1);
		misst = -1;
	}

	void update(double t, double gameSpeed) override
	{
		if (MouseL.down()) {
			for (auto i : step(timing.size())) {
				if (isGet[i]>0) continue;
				if (Abs(timing[i] - t) < 0.1) {
					isGet[i] = t;
					break;
				}
			}
		}
		for (auto i : step(timing.size())) {
			if ((isGet[i] < 0) and t - timing[i] >= 0.1 and misst < 0) {
				misst = t;
			}
		}
		
	}

	void draw(double t, double gameSpeed) const override
	{
		Rect{ 0,0,SceneSize }.draw(Palette::Lemonchiffon);
		Size s = { 256,112 };
		for (Vec2 p : step(s / 4))
		{
			Vec2 q{ noise.normalizedOctave2D0_1(p.x / 4.0 + t, p.y / 4.0 + t, 4),
					noise.normalizedOctave2D0_1(p.x / 4.0 + t * 1.2, p.y / 4.0 + t * 1.5, 4) };
			double v = noise.normalizedOctave2D0_1(p.x / 10 + q.x, p.y / 10 + q.y, 4);
			RectF{ p.x * 4, 70 + p.y * 4, 4 }.draw(HSV(200, 0.5, v * 1.3));
		}
		if (MouseL.pressed()) {
			TextureAsset(U"ポイ").resized(53).rotated(-45_deg).drawAt(basePos.movedBy(7,10), ColorF{ 0,0.2 });
			TextureAsset(U"ポイ").resized(50).rotated(-45_deg).drawAt(basePos);
		}
		else {
			TextureAsset(U"ポイ").resized(50).rotated(-45_deg).drawAt(basePos.movedBy(2,10), ColorF{0,0.7});
			TextureAsset(U"ポイ").resized(50).rotated(-45_deg).drawAt(basePos.movedBy(0,9));

		}
		TextureAsset(U"コップ下").resized(60,40).rotated(45_deg).drawAt(0, SceneCenter.y - 25);

		for (auto i : step(timing.size())) {
			if (isGet[i]) {
				TextureAsset(U"金魚").resized(53).mirrored().flipped((int32)(t * 16) % 2 == 0).drawAt(basePos.x + 2 + 400 * (timing[i] - t), SceneCenter.y + 5, ColorF{ 0,0.3 - Max(0.0,t - timing[i]) });
				TextureAsset(U"金魚").resized(50).mirrored().flipped((int32)(t * 16) % 2 == 0).drawAt(basePos.x + 400 * (timing[i] - t), SceneCenter.y + 2 - EaseOutCirc((isGet[i]>0 ? Clamp((t-isGet[i])*10,0.0,1.0):0.0 ))*30);
			}
			else {
				TextureAsset(U"金魚").resized(50).mirrored().flipped((int32)(t * 16) % 2 == 0).drawAt(basePos.x + 2 + 400 * (timing[i] - t), SceneCenter.y + 2, ColorF{0,0.5});
				TextureAsset(U"金魚").resized(50).mirrored().flipped((int32)(t * 16) % 2 == 0).drawAt(basePos.x + 400 * (timing[i] - t), SceneCenter.y);
			}
		}
		TextureAsset(U"コップ上").resized(60, 40).rotated(45_deg).drawAt(0, SceneCenter.y - 25);

		for (auto i : step(3)) {
			double y = 220 - Periodic::Jump0_1(0.25, t) * 10;
			if (misst > 0)y += (t - misst) * (t - misst) * 100 * 100;
			TextureAsset(U"Siv3dくん").resized(70).mirrored((int32)(t*4)%2==0).drawAt(64 * (i + 1),y );
		}

		int32 count = 0;
		for (auto tt : isGet)if (tt > 0)count++;
		Rect{ 128,55,110,12 }.draw(Palette::Gray);
		Rect{ 128,55,110 *count/isGet.size(),12}.draw(Palette::Red);
		if(count == isGet.size())Rect{ 128,55,110,12 }.draw(HSV{ Periodic::Sawtooth0_1(1.0)*360});
	}
	bool isClear() override {
		return misst < 0;
		//return true;
	}
private:
	const Vec2 basePos{ 60,SceneCenter.y };
	Array<double> timing;
	Array<double> isGet;
	double  misst;
	PerlinNoise noise;
};

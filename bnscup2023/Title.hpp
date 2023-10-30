# pragma once
# include "Common.hpp"

//タイトルの背景で流れてる文字
class TitleBGText
{
private:
	Vec2 pos = Vec2{ 0, 0 };
	String text = U"";
	double speed = 50.0;

	//数々の"すくう"たち
	const Array<String> Texts
	{
		U"救",
		U"掬",
		U"巣食",
		U"梳く",
		U"SUKU",
		U"すく",
		U"スク"
	};

public:
	SIV3D_NODISCARD_CXX20
		TitleBGText() = default;

	TitleBGText(Vec2 pos)
		:pos{ pos },
		text{ U"救" },
		speed{ 50.0 } {}

	TitleBGText(Vec2 pos, double speed)
		:pos{ pos },
		text{ U"救" },
		speed{ speed } {}


	void update()
	{
		//座標更新
		pos.x += speed * Scene::DeltaTime();
		pos.y -= speed * Scene::DeltaTime();
		//上か横についたら表示するテキストをランダムにして初期位置に戻す
		if (pos.x >= SceneWidth + 50)
		{
			text = Texts[Random(6)];
			pos.x = -50;
		}
		if (pos.y <= -50)
		{
			text = Texts[Random(6)];
			pos.y = SceneHeight + 50;
		}
	}

	void draw() const
	{
		FontAsset(U"TitleBGFont")(text).drawAt(pos, Palette::Black);
	}
};

// タイトルシーン
class Title : public App::Scene
{
public:

	Title(const InitData& init);

	void update() override;

	void draw() const override;

private:
	Array<TitleBGText> bgtexts;
	Array<Vec2> SelectTrianglePoint;


	Vec2 SukuuLeftTopTrianglePoint = SceneCenter.movedBy(-65, 70);
	Vec2 SukuuLeftBottomTrianglePoint = SceneCenter.movedBy(-65, 70);
	Vec2 SukuuLeftCenterTrianglePoint = SceneCenter.movedBy(-50, 70);
};

# pragma once
# include <Siv3D.hpp>
# include "Effect.hpp"

namespace
{
	constexpr uint32 SceneWidth = 256;
	constexpr uint32 SceneHeight = 256;
	constexpr Size SceneSize{ SceneWidth, SceneHeight };
	constexpr Vec2 SceneCenter{ SceneSize.x / 2, SceneSize.y / 2 };
}



class PetitGame
{
public:
	/// @brief ゲームのタイトル
	const String title = U"タイトル";

	/// @brief ゲーム開始時の一言説明
	const String startCall = U"すくえ！";

	/// @brief ゲームの説明文(使わないと思う)
	const String description = U"ゲームの説明文";

	/// @brief 表示するカーソルの名前
	String CursorStyle = U"Point";

	/// @brief ゲームの初期化
	PetitGame(const String& _title, const String& _startCall = U"すくえ！", const String& _description = U"")
		:title{ _title }, startCall{ _startCall }, description{ _description } {};

	/// @brief ゲームの初期化
	virtual void init() = 0;

	/// @brief ゲームの更新
	/// @param t 経過時間(0.0<= t <= 1.0)
	/// @param gameSpeed ゲームのスピード(1.0で通常)
	virtual void update(double t,double gameSpeed) = 0;

	/// @brief ゲームの描画
	virtual void draw(double t, double gameSpeed) const = 0;

	/// @brief ゲームクリア判定
	virtual bool isClear() = 0;

	///// @brief ゲームのアセットの読み込み
	//virtual bool loadAssets() { return true; };

	///// @brief ゲームのアセットの解放
	//virtual void releaseAssets() {};
};

class example : public PetitGame
{
public:
	Texture texture;
	example()
		:PetitGame{ U"てすと" },
		texture{ TextureAsset(U"example_test") }
	{
	}
	void init() override {}
	void update(double t, double gameSpeed) override {
		double dt = Scene::DeltaTime() * gameSpeed;
		Print << Cursor::Pos();
	}
	void draw(double t, double gameSpeed) const override {
		Print << U"hello";
		Circle{ Cursor::Pos(),50 }.draw(Palette::Red);
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

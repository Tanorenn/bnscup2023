#pragma once
# include <Siv3D.hpp>

class PuchiGame
{
public:
	/// @brief ゲームのタイトル
	const String title = U"タイトル";

	/// @brief ゲーム開始時の一言説明
	const String startCall = U"すくえ！";

	/// @brief ゲームの説明文(使わないと思う)
	const String description = U"ゲームの説明文";

	/// @brief ゲームの初期化
	PuchiGame(const String& _title, const String& _startCall = U"すくえ！", const String& _description = U"")
		:title{ _title }, startCall{ _startCall }, description{ _description } {};

	/// @brief ゲームの初期化
	virtual void init() = 0;

	/// @brief ゲームの更新
	/// @param t 経過時間(0.0<= t <= 1.0)
	/// @param gameSpeed ゲームのスピード(1.0で通常)
	virtual void update(double t,double gameSpeed) = 0;

	/// @brief ゲームの描画
	virtual void draw() const = 0;

	/// @brief ゲームクリア判定
	virtual bool isClear() = 0;
};

class example : public PuchiGame
{
public:
	example()
		:PuchiGame{U"てすと"} {}
	void init() override {}
	void update(double t, double gameSpeed) override { double dt = Scene::DeltaTime() * gameSpeed; }
	void draw() const override {}
	bool isClear() override { return true; }

};

# pragma once
# include <Siv3D.hpp>
# include "PetitGames.hpp"
# include "MyCursor.hpp"


// シーンの名前
enum class State
{
	Title,
	Loading,
	Game,
};

// 共有するデータ
struct GameData
{
	//オリジナルのカーソル
	MyCursor myCursor;

	//ゲーム一覧
	Array<PetitGame*> petitGames
	{
		/*
		new SaveTheEarth(),
		new HundredYen(),
		new Explosion(),
		new FireFighting(),
		new SaveFood(),
		new FireFighting(),
		new GYARRA(),*/
		new DreamyRainy(),
	};
};

using App = SceneManager<State, GameData>;

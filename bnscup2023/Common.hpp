# pragma once
# include <Siv3D.hpp>
# include "PetitGames.hpp"


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
	//ゲーム一覧
	Array<PetitGame*> petitGames
	{
		// new example(),
		new SaveTheEarth(),
		new Explosion(),
		new FireFighting()
	};
};

using App = SceneManager<State, GameData>;

# pragma once
# include <Siv3D.hpp>
# include "PetitGames.hpp"

namespace
{
	constexpr uint32 SceneWidth = 256;
	constexpr uint32 SceneHeight = 256;
	constexpr Size SceneSize{ SceneWidth, SceneHeight };
	constexpr Vec2 SceneCenter{ SceneSize.x / 2, SceneSize.y / 2 };
}


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
		new example(),
		new SaveTheEarth()
	};
};

using App = SceneManager<State, GameData>;

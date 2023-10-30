# include "Game.hpp"

Game::Game(const InitData& init)
	: IScene{ init },
	games{ getData().petitGames },
	gameIndex{getData().petitGames.size()},
	gameScene{ SceneSize, Palette::White }
{
	gameIndex = Array<size_t>(getData().petitGames.size(), 0);
	for (int i = 0; i < gameIndex.size(); i++)gameIndex[i] = i;
	gameIndex.shuffle();
	for (int i = 0; i < Min(5, (int32)getData().petitGames.size()); i++) {
		games[gameIndex[i]]->init();
	}
	finishTime = 60.0 * 8 / tempo;
	gameSpeed = 1.0 / finishTime;
	gameTime = -0.5;

}

void Game::update()
{
	gameTime += gameSpeed * Scene::DeltaTime();
	auto& game = games[gameIndex[gameCount]];
	game->update(Clamp(gameTime,0.0,1.0), gameSpeed);
	if (KeyEnter.down() or gameTime>=1.5) {
		if (gameCount < Min(playGames, (int32)gameIndex.size()) - 1) {
			gameCount++;
			if (gameCount % 5)tempo += 10.0;
			finishTime = 60.0 * 8 / tempo;
			gameSpeed = 1.0 / finishTime;
			gameTime = -0.5;
		}
		else changeScene(State::Title);
	}
}

void Game::draw() const
{
	const auto& game = getData().petitGames[gameIndex[gameCount]];
	Print << game->title;
	game->draw(Clamp(gameTime, 0.0, 1.0), gameSpeed);
	if (gameTime < 0) {
		FontAsset(U"TitleSelectFont")(game->startCall).drawAt(60,SceneCenter.movedBy(2, 2), ColorF{ 0.0,0.4 });
		FontAsset(U"TitleSelectFont")(game->startCall).drawAt(60,SceneCenter);
	}
}

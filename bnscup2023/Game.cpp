# include "Game.hpp"

Game::Game(const InitData& init)
	: IScene{ init },
	m_games{ getData().petitGames },
	m_gameIndex{getData().petitGames.size()},
	gameScene{ 256,256, Palette::White }
{
	for (int i = 0; i < m_gameIndex.size(); i++)m_gameIndex[i] = i;
	m_gameIndex.shuffle();
	for (int i = 0; i < Min(5, (int32)getData().petitGames.size()); i++) {
		m_games[i]->init();
	}
	m_isLoaded = true;
	m_gameIndex[0] = 1;
	//m_petitGame->loadAssets();
}

void Game::update()
{
	gameTime += gameSpeed * Scene::DeltaTime();
	auto& game = m_games[m_gameIndex[m_gameCount]];
	game->update(0, 0);
	if (KeyEnter.down()) {
		if(m_gameCount < Min(playGames,(int32)m_gameIndex.size()) - 1)m_gameCount++;
		else changeScene(State::Title);
	}
}

void Game::draw() const
{
	const auto& game = getData().petitGames[m_gameIndex[m_gameCount]];
	Print << game->title;
	game->draw();
}

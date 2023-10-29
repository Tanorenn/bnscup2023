# include "Game.hpp"

Game::Game(const InitData& init)
	: IScene{ init },
	m_petitGame{ getData().petitGames.choice() }
{
	m_petitGame->init();
	m_isLoaded = true;
	//m_petitGame->loadAssets();
}

void Game::update()
{
	//if (m_petitGame->loadAssets())
	//{
	//	m_isLoaded = true;
	//}
	if (m_isLoaded)
		m_petitGame->update(0, 0);
	if (KeyEnter.down()) {
		//m_petitGame->releaseAssets();
		changeScene(State::Title);
	}
}

void Game::draw() const
{
	Print << m_petitGame->title;
	if (m_isLoaded)
	{
		m_petitGame->draw();
	}
}

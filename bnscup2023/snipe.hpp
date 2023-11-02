# pragma once
# include "PetitGame.hpp"

class Snipe : public PetitGame
{
	struct Enemy {
		size_t enemyIndex;
		Vec2 pos;
	};

	const Array<Texture> enemyType{
		Texture{U"👻"_emoji},
		Texture{U"👽"_emoji},
		Texture{U"💀"_emoji},
	};
	const Texture king{ U"🤴"_emoji };
	Array<Enemy> enemies;
public:
	Snipe():PetitGame{U"スナイパー"}
	{
		init();
	}
	void init() override {
		enemies.clear();
		for(int i:step(3)){
			enemies << Enemy{Random(enemyType.size()), OffsetCircular(SceneCenter,Random(40,80),Random(0,360))};
		}
	}
	void update(double t, double GameSpeed) override {
		
	}
	void draw(double t, double GameSpeed) const override;
	bool isClear() override;
};

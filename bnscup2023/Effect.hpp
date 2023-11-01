# pragma once
# include <Siv3D.hpp>

class LightBloom {
public:
	const RenderTexture gaussianA1, gaussianB1;
	const RenderTexture gaussianA4, gaussianB4;
	const RenderTexture gaussianA8, gaussianB8;
	const Size area;
	const ColorF colorA1, colorA4, colorA8;

	LightBloom(const Size& size, const ColorF& colorA1 = ColorF(0.1), const ColorF& colorA4 = ColorF(0.4), const ColorF& colorA8 = ColorF(0.8))
		:area{ size },
		gaussianA1{ size }, gaussianB1{ size },
		gaussianA4{ size / 4 }, gaussianB4{ size / 4 },
		gaussianA8{ size / 8 }, gaussianB8{ size / 8 },
		colorA1{ colorA1 },
		colorA4{ colorA4 },
		colorA8{ colorA8 } {}

	void draw() const
	{
		Shader::GaussianBlur(gaussianA1, gaussianB1, gaussianA1);
		Shader::Downsample(gaussianA1, gaussianA4);
		Shader::GaussianBlur(gaussianA4, gaussianB4, gaussianA4);
		Shader::Downsample(gaussianA4, gaussianA8);
		Shader::GaussianBlur(gaussianA8, gaussianB8, gaussianA8);
		const ScopedRenderStates2D blend{ BlendState::Additive };
		gaussianA1.resized(area).draw(colorA1);
		gaussianA4.resized(area).draw(colorA4);
		gaussianA8.resized(area).draw(colorA8);
	}
};

struct SmokeEffect : IEffect
{
	const Vec2 m_pos;
	const double m_size;
	const double m_gameSpeed;

	SmokeEffect(const Vec2& pos, double gameSpeed)
		:m_pos{ pos },
		m_size{ Random(25.0, 50.0) },
		m_gameSpeed{ gameSpeed }
	{

	}

	bool update(double t) override
	{
		t *= m_gameSpeed * 8;
		Circle{ m_pos.movedBy(30 + t * 30, -t * 100), m_size - t * m_size }.draw(ColorF(0.75, (1 - t) * 0.5));
		Circle{ m_pos.movedBy(-30 - t * 30, -t * 100), m_size - t * m_size }.draw(ColorF(0.75, (1 - t) * 0.5));

		return t < 1;
	}
};

enum class DrawMountainType : uint8
{
	Dot,
	Line,
	Quad
};

class Mountain
{
private:
	PerlinNoise noise{ RandomUint32() };
	Grid<Vec2> points;
	Grid<ColorF> colors;
	ColormapType colorType;
	DrawMountainType drawType;
	double yStart = Scene::Height() + 100;
	double yEnd = 0;
	double xStart = 20000;
	double xEnd = Scene::Width();
	double noiseXStart = 0.0;
	double noiseYStart = 0.0;
	double scale = 10.0;
	double variation = 10.0;
	uint8 octave = 1;
	double (*EasingFunc)(double);

public:
	Mountain()
		:yStart{ Scene::Height() + 100.0 },
		yEnd{ 0 },
		points{ Grid<Vec2>(500, 200, Vec2(0, 0)) },
		colors{ Grid<ColorF>(500, 200, Palette::White) },
		colorType{ ColormapType::Turbo },
		drawType{ DrawMountainType::Dot },
		xEnd{ (double)Scene::Width() },
		xStart{ 20000 },
		noiseXStart{ 0.0 },
		noiseYStart{ 0.0 },
		scale{ 10.0 },
		variation{ 10.0 },
		EasingFunc{ EaseOutSine }
	{}

	Mountain(uint32 xDivisionNum, uint32 yDivisionNum)
		:yStart{ Scene::Height() + 100.0 },
		yEnd{ 0 },
		points{ Grid<Vec2>(xDivisionNum, yDivisionNum, Vec2(0, 0)) },
		colors{ Grid<ColorF>(xDivisionNum, yDivisionNum, Palette::White) },
		colorType{ ColormapType::Turbo },
		drawType{ DrawMountainType::Dot },
		xEnd{ (double)Scene::Width() },
		xStart{ 20000 },
		noiseXStart{ 0.0 },
		noiseYStart{ 0.0 },
		scale{ 10.0 },
		variation{ 10.0 },
		EasingFunc{ EaseOutSine }
	{}

	Mountain& _setYStart(double yStart)
	{
		this->yStart = yStart;
		return *this;
	}

	Mountain& _setYEnd(double yEnd)
	{
		this->yEnd = yEnd;
		return *this;
	}

	Mountain& _setXEnd(double xEnd)
	{
		this->xEnd = xEnd;
		return *this;
	}

	Mountain& _setXStart(double xStart)
	{
		this->xStart = xStart;
		return *this;
	}

	Mountain& _setNoiseXStart(double noiseXStart)
	{
		this->noiseXStart = noiseXStart;
		return *this;
	}

	Mountain& _setNoiseYStart(double noiseYStart)
	{
		this->noiseYStart = noiseYStart;
		return *this;
	}

	Mountain& _setScale(double scale)
	{
		this->scale = scale;
		return *this;
	}

	Mountain& _setVariation(double variation)
	{
		this->variation = variation;
		return *this;
	}

	Mountain& _setOctave(uint8 octave)
	{
		this->octave = octave;
		return *this;
	}

	Mountain& _setEasingFunc(double (*func)(double))
	{
		this->EasingFunc = func;
		return *this;
	}

	Mountain& _setColorType(ColormapType colorType)
	{
		this->colorType = colorType;
		return *this;
	}

	void setScale(double scale)
	{
		this->scale = scale;
	}

	void setVariation(double variation)
	{
		this->variation = variation;
	}

	void setEasingFunc(double (*func)(double))
	{
		this->EasingFunc = func;
	}

	void setColorType(ColormapType colorType)
	{
		this->colorType = colorType;
	}

	void setDivisionNum(uint32 xDivisionNum, uint32 yDivisionNum)
	{
		points.clear();
		colors.clear();
		points = Grid<Vec2>(xDivisionNum, yDivisionNum);
		colors = Grid<ColorF>(xDivisionNum, yDivisionNum);
	}

	void setDrawType(DrawMountainType drawType)
	{
		this->drawType = drawType;
	}

	void updateNoiseX(double x)
	{
		noiseXStart = x;
	}

	void updateNoiseY(double y)
	{
		noiseYStart = y;
	}

	void regenerate()
	{
		noise = PerlinNoise{ RandomUint32() };
	}

	void update()
	{
		for (auto y : step(points.height()))
		{
			// y座標(0.0～1.0)を計算 イージングで3Dっぽい変化に見せてる
			double yRatio = EasingFunc((double)y / (points.height()));
			// そのy座標での横線の幅を計算 y座標で0.0～1.0にしたものをxEndとxStartの範囲にMapしてる
			double xWidth = Math::Map(yRatio, 0.0, 1.0, xStart, xEnd);
			// 横幅を計算 求めた横線の幅をGridの列の数で分割
			double width = xWidth / points.width();
			// y座標を計算
			double yPos = yStart - (yRatio * (yStart - yEnd));

			for (auto x : step(points.width()))
			{
				points[y][x].x = xEnd / 2.0 - xWidth / 2.0 + width * x;
				points[y][x].y = yPos - (20 * EasingFunc(1 - yRatio)) - noise.octave2D(noiseXStart + x / scale, noiseYStart + y / scale, octave) * variation;
				colors[y][x] = Colormap01(noise.octave2D0_1(noiseXStart + x / scale, noiseYStart + y / scale, octave), colorType);
			}
		}
	}

	void drawDot(double thick = 1) const
	{
		for (size_t y = points.height() - 1; y > 0; y--)
		{
			for (auto x : step(points.width()))
			{
				Circle{ points[y][x], thick }.draw(colors[y][x]);
			}
		}
	}

	void drawDot(double thick, ColorF color) const
	{
		for (size_t y = points.height() - 1; y > 0; y--)
		{
			for (auto x : step(points.width()))
			{
				Circle{ points[y][x], thick }.draw(color);
			}
		}
	}

	void drawLine(double thick = 1) const
	{
		for (size_t y = points.height() - 1; y > 0; y--)
		{
			for (auto x : step(points.width()))
			{
				// 横線
				if (x < points.width() - 1) Line(points[y][x], points[y][x + 1]).draw(thick, colors[y][x]);
				// 縦線
				if (y < points.height() - 1) Line(points[y][x], points[y + 1][x]).draw(thick, colors[y][x]);
			}
		}
	}

	void drawLine(double thick, ColorF color) const
	{
		for (size_t y = points.height() - 1; y > 0; y--)
		{
			for (auto x : step(points.width()))
			{
				// 横線
				if (x < points.width() - 1) Line(points[y][x], points[y][x + 1]).draw(thick, color);
				// 縦線
				if (y < points.height() - 1) Line(points[y][x], points[y + 1][x]).draw(thick, color);
			}
		}
	}

	void drawQuad() const
	{
		for (size_t y = points.height() - 2; y > 0; y--)
		{
			for (auto x : step(points.width()))
			{
				if (x < points.width() - 1 && y < points.height() - 1)
				{
					Quad(points[y][x], points[y][x + 1], points[y + 1][x + 1], points[y + 1][x]).draw(colors[y][x]);
				}
			}
		}
	}

	void drawQuad(ColorF color) const
	{
		for (size_t y = points.height() - 2; y > 0; y--)
		{
			for (auto x : step(points.width()))
			{
				if (x < points.width() - 1 && y < points.height() - 1)
				{
					Quad(points[y][x], points[y][x + 1], points[y + 1][x + 1], points[y + 1][x]).draw(color);
				}
			}
		}
	}

	void draw(Optional<ColorF> color) const
	{
		switch (drawType)
		{

		case DrawMountainType::Dot:
			if (color.has_value())
			{
				drawDot(1, *color);
			}
			else
			{
				drawDot();
			}
			break;

		case DrawMountainType::Line:
			if (color.has_value())
			{
				drawLine(1, *color);
			}
			else
			{
				drawLine();
			}
			break;

		case DrawMountainType::Quad:
			if (color.has_value())
			{
				drawQuad(*color);
			}
			else
			{
				drawQuad();
			}
			break;

		default:
			break;
		}
	}
};

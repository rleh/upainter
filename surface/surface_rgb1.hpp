
#ifndef MODM_GES_SURFACE_HPP
#	error	"Don't include this file directly, use 'surface.hpp' instead!"
#endif

#include <cstring>
#include <algorithm>

namespace modm
{

namespace ges
{

template<>
class Surface<PixelFormat::RGB1>
{
	friend class QSurface;
	static constexpr PixelFormat Format = PixelFormat::RGB1;
public:
	using UnderlyingColor = ColorRGB1;

	template< uint16_t Width, uint16_t Height >
	using Buffer = PixelBuffer<Width, Height, Format>;

public:
	Surface(uint8_t *const buffer, const uint16_t width, const uint16_t height) :
		width(width), height(height), buffer(buffer)
	{}

	template< uint16_t Width, uint16_t Height >
	Surface(PixelBuffer<Width, Height, Format> &buffer) :
		Surface(buffer.getData(), Width, Height)
	{}

	uint16_t
	getWidth() const
	{ return width; }

	uint16_t
	getHeight() const
	{ return height; }

	static constexpr PixelFormat
	getPixelFormat()
	{ return Format; }

	void
	clear()
	{
		std::memset(buffer, 0, std::size_t(width) * height);
	}

	void
	clear(UnderlyingColor color)
	{
		std::memset(buffer, color.getValue(), std::size_t(width) * height);
	}

	bool
	setPixel(uint16_t x, uint16_t y, UnderlyingColor color)
	{
		if (x < width and y < height)
		{
			buffer[y * width + x] = color.getValue();
			return true;
		}
		return false;
	}

	bool
	clearPixel(uint16_t x, uint16_t y)
	{
		return setPixel(x, y, UnderlyingColor(0));
	}

	Color
	getPixel(uint16_t x, uint16_t y) const
	{
		if (x < width and y < height)
		{
			return Color(UnderlyingColor(buffer[y * width + x]));
		}
		return Color::Black;
	}

protected:
	const uint16_t width;
	const uint16_t height;
	uint8_t *const buffer;
};

} // namespace ges

} // namespace modm


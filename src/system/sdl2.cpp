#include "sdl2.hpp"

void oop::system::draw_circle(SDL_Renderer* surface, int n_cx, int n_cy, int radius)
{
	// if the first pixel in the screen is represented by (0,0) (which is in sdl)
	// remember that the beginning of the circle is not in the middle of the pixel
	// but to the left-top from it:

	double error = -radius;
	auto x = radius - 0.5;
	auto y = 0.5;
	const auto cx = n_cx - 0.5;
	const auto cy = n_cy - 0.5;

	while (x >= y)
	{
		SDL_RenderDrawPoint(surface, int(cx + x), int(cy + y));
		SDL_RenderDrawPoint(surface, int(cx + y), int(cy + x));

		if (x != 0)
		{
			SDL_RenderDrawPoint(surface, int(cx - x), int(cy + y));
			SDL_RenderDrawPoint(surface, int(cx + y), int(cy - x));
		}

		if (y != 0)
		{
			SDL_RenderDrawPoint(surface, int(cx + x), int(cy - y));
			SDL_RenderDrawPoint(surface, int(cx - y), int(cy + x));
		}

		if (x != 0 && y != 0)
		{
			SDL_RenderDrawPoint(surface, int(cx - x), int(cy - y));
			SDL_RenderDrawPoint(surface, int(cx - y), int(cy - x));
		}

		error += y;
		++y;
		error += y;

		if (error >= 0)
		{
			--x;
			error -= x;
			error -= x;
		}
	}
}
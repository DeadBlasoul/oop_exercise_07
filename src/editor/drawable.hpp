#pragma once

#include "system/renderer.hpp"

namespace oop::editor
{
	struct i_drawable
	{
		i_drawable() = default;
		i_drawable(const i_drawable&) = default;
		i_drawable(i_drawable&&) noexcept = default;
		i_drawable& operator=(const i_drawable&) = default;
		i_drawable& operator=(i_drawable&&) noexcept = default;
	    virtual ~i_drawable() = 0;

		virtual void draw(system::renderer& renderer) = 0;
	};

	inline i_drawable::~i_drawable() = default;

}
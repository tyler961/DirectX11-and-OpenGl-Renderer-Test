#pragma once

#include "MTX/Core.h"
#include <string>

namespace MTX {

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
}
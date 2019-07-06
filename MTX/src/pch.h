#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

// Used for ComPtr, smart pointer for COM objects. Because unique_ptrs call delete, and COM objects cannot, this is a simpler solution
#include <wrl.h>

#include "MTX/Log.h"

#ifdef MTX_PLATFORM_WINDOWS
	#include "WindowsInclude.h"
#endif
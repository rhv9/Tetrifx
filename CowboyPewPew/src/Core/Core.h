#pragma once

#ifdef EMSCRIPTEN
#define PLATFORM_BROWSER
#endif

#ifdef DEBUG
#define CORE_ASSERT
#endif

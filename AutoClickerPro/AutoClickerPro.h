#pragma once

#ifdef AUTOCLICKERPRO_EXPORTS
#define AUTOCLICKERPRO_API __declspec(dllexport)
#else
#define AUTOCLICKERPRO_API __declspec(dllimport)
#endif

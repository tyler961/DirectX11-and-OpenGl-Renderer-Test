#pragma once

#define _WIN32_WINNT 0x0601
#include <sdkddkver.h>

// The following #defines disable a bunch of unused windows stuff. They
// help to remove weird erros when doing windows stuff
#define WIN32_LEAN_AND_MEAN
#define	NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUES
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNAL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE

#define STRICT

#include <Windows.h>
#include <windowsx.h>
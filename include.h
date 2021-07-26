
#include <Windows.h>
#include <vector>

template <typename t>
t getvfunc(void* class_pointer, size_t index)
{
	return (*(t**)class_pointer)[index];
}

#include "vector.h"
#include "math.h"
#include "recvprop.h"
#include "baseentity.h"
#include "engineclient.h"
#include "surface.h"
#include "materials.h"
#include "panels.h"
#include "usercmd.h"
#include "hitgroup.h"
#include "enginetrace.h"
#include "globalvars.h"
#include "modelsinfo.h"
#include "viewsetup.h"
#include "interfaces.h"
#include "drawing.h"
#include "mouse.h"
#include "menu.h"
#include "visuals.h"
#include "aimbot.h"
#include "exploit.h"
#include "nospread.h"
#include "variables.h"
#include "hooking.hpp"

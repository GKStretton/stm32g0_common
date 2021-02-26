#include "compFilter.h"
#include "math.h"

int firstUpdate = 1;

void updateCompFilter(float timeElapsed, float Gx, float Gy, float Gz, float Ax, float Ay, float Az, float Mx, float My, float Mz)
{
	Rz += timeElapsed * (Gz + Gx * sinf(Rz) * sinf(Rx)/cosf(Rx) + Gy * cosf(Rz) * sinf(Rx)/cosf(Rx));
	Rx += timeElapsed * (Gx * cosf(Rz) - Gy * sinf(Rz));
	Ry += timeElapsed * (Gx * sinf(Rz) / cosf(Rx) + Gy * cosf(Rz) / cosf(Rx));
}

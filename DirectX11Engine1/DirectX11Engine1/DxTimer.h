#ifndef _DXTIMER_H_
#define _DXTIMER_H_

#include<chrono>

class DxTimer
{
public:
	DxTimer();
	//前のフレームから今のフレームまでの差分を返す
	float Mark();
	//今の時間からlastの差分を返す
	float Peek()const;
private:
	std::chrono::steady_clock::time_point last;
};

#endif
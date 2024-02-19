#pragma once


class UTime
{
public:
	UTime();
	void OnUpdate();

	static float GetDeltaTime() { return sDeltaTime; }
	static double GetTime();

private:
	float TimeLastFrame;
	static float sDeltaTime;
};
#pragma once
constexpr int Scale = 50;
class Particle
{
private:
	double PosX;
	double PosY;
	double XSize;
	double YSize;
	double UpPos;
	int Trans = -1;
	int Transfer;
	bool Flag;
	int particle;

public:
	Particle(const int Handle, double PosX, double PosY, double MinSize, double MaxSize);
	void Draw();
	bool GetFlag();
};


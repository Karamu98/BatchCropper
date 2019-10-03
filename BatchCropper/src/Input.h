#pragma once

#include <memory>
#include <vector>
#include <string>

enum ConsoleColour
{
	FBlue = 1,
	FGreen = 2,
	FRed = 4,
	FIntensity = 8,
	BBlue = 10,
	BGreen = 20,
	BRed = 40,
	BIntensity = 80
};

inline ConsoleColour operator|(ConsoleColour a, ConsoleColour b)
{
	return static_cast<ConsoleColour>(static_cast<int>(a) | static_cast<int>(b));
}

class IO
{
public:
	static void DisplayMessage(const std::string& a_message, bool a_nl = true);
	static void NewLine();
	static void ClearConsole();
	static void WaitForUser();
	static void SetTextColour(ConsoleColour a_newColour);
	static void ResetColour();
	static std::string CaptureString();
	static std::string CapturePath();
	static int CaptureInt();
	static std::shared_ptr<std::vector<std::string>> GetFilesInDir(const std::string& a_rootDir);

private:
	static std::shared_ptr<void> sm_stdHandle;
};
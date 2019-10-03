#include "Input.h"

#include <iostream>
#include <filesystem>
#include <fstream>

#define NOMINMAX
#include <Windows.h>

void IO::DisplayMessage(const std::string& a_message, bool a_nl)
{
	std::cout << a_message;
	if (!a_nl)
	{
		return;
	}
	std::cout << std::endl;
}

void IO::NewLine()
{
	std::cout << std::endl;
}

void IO::ClearConsole()
{
	system("cls");
}

void IO::WaitForUser()
{
	system("pause");
}

void IO::SetTextColour(ConsoleColour a_newColour)
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hstdout, a_newColour);
}

void IO::ResetColour()
{

}

std::string IO::CaptureString()
{
	std::string newVal = "";
	while (newVal == "")
	{
		std::getline(std::cin, newVal);
	}
	return newVal;
}

std::string IO::CapturePath()
{
	std::string newStr = CaptureString();

	if (newStr[0] == '"')
	{
		newStr = newStr.substr(1, newStr.size() - 2);
	}

	return newStr;
}

int IO::CaptureInt()
{
	int newVal = std::numeric_limits<int>::min();
	while (newVal == std::numeric_limits<int>::min())
	{
		std::cin >> newVal;
	}
	return newVal;
}

std::shared_ptr<std::vector<std::string>> IO::GetFilesInDir(const std::string& a_rootDir)
{
	std::shared_ptr<std::vector<std::string>> listOfFiles;

	// Check if given path exists and points to a directory
	if (std::experimental::filesystem::exists(a_rootDir) && std::experimental::filesystem::is_directory(a_rootDir))
	{
		// Create a Recursive Directory Iterator object and points to the starting of directory
		std::experimental::filesystem::recursive_directory_iterator iter(a_rootDir);

		// Create a Recursive Directory Iterator object pointing to end.
		std::experimental::filesystem::recursive_directory_iterator end;

		listOfFiles = std::make_shared<std::vector<std::string>>();
		listOfFiles->reserve(std::distance(iter, end));

		for (auto& p : std::experimental::filesystem::recursive_directory_iterator(a_rootDir))
		{
			// Add the name in vector
			listOfFiles->push_back(p.path().string());
		}
	}

	return listOfFiles;
}
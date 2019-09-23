// BatchCropper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vld.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "Image.h"

std::vector<std::string>* GetAllFilesInDir(const std::string& dirPath);


int Intput();
std::string Strput();

int main()
{
	std::string inDir;
	std::cout << "Drag folder of images here\n";
	inDir = Strput();
	inDir = inDir.substr(1, inDir.size() - 2);

	std::string outDir;
	std::cout << "\nDrag output folder here\n";
	outDir = Strput();
	outDir = outDir.substr(1, outDir.size() - 2);

	int left, right, top, bottom;
	std::cout << "\nEnter trim amount in the following order: Left, Right, Top, Bottom.\n";
	left = Intput();
	right = Intput();
	top = Intput();
	bottom = Intput();

	std::cout << "\nLoading...\n";

	// Grab all the filepaths for images in the buffer
	std::vector<std::string>* imagePaths = GetAllFilesInDir(inDir);

	// Grab all image files and create memory pool
	unsigned int imageCount = imagePaths->size();
	if (imageCount <= 0)
	{
		std::cout << "\nNo images found at " << inDir << "\n";
		std::cin;
		return 1;
	}

	std::vector<Image> images;
	images.reserve(imageCount);

	// Load images into buffer
	for (int i = 0; i < imageCount; i++)
	{
		images.push_back(Image((*imagePaths)[i]));
	}

	delete imagePaths;

	std::cout << "\nProcessing...\n";

	// Trim images 
	for (int i = 0; i < imageCount; i++)
	{
		if(!images[i].Trim(left, right, top, bottom))
		{
			// Fail
			std::cout << "Failed\n";
			std::cin;
			return 1;
		}
	}

	std::cout << "\nWriting to " << outDir << std::endl;

	// Save images 
	for (int i = 0; i < imageCount; i++)
	{
		images[i].Write(outDir);
		images[i].Destroy();
	}


	std::cout << "\nComplete\n";
	std::cin;
}

std::vector<std::string>* GetAllFilesInDir(const std::string& dirPath)
{
	std::vector<std::string>* listOfFiles = new std::vector<std::string>();

	// Check if given path exists and points to a directory
	if (std::experimental::filesystem::exists(dirPath) && std::experimental::filesystem::is_directory(dirPath))
	{
		// Create a Recursive Directory Iterator object and points to the starting of directory
		std::experimental::filesystem::recursive_directory_iterator iter(dirPath);

		// Create a Recursive Directory Iterator object pointing to end.
		std::experimental::filesystem::recursive_directory_iterator end;

		listOfFiles->reserve(std::distance(iter, end));

		for (auto& p : std::experimental::filesystem::recursive_directory_iterator(dirPath))
		{
			// Add the name in vector
			listOfFiles->push_back(p.path().string());
		}
	}

	return listOfFiles;
}

int Intput()
{
	int newVal = std::numeric_limits<int>::min();
	while (newVal == std::numeric_limits<int>::min())
	{
		std::cin >> newVal;
	}
	return newVal;
}

std::string Strput()
{
	std::string newVal = "";
	while (newVal == "")
	{
		std::getline(std::cin, newVal);
	}
	return newVal;
}

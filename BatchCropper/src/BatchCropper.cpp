#include "Image.h"
#include "Input.h"

int main()
{
	IO::SetTextColour(FGreen |FIntensity | BBlue | BIntensity);

	IO::DisplayMessage("Drag folder of images here");
	std::string inDir = IO::CapturePath();

	IO::DisplayMessage("Drag output folder here");
	std::string outDir = IO::CapturePath();

	IO::DisplayMessage("Enter trim amount in the following order: Left, Right, Top, Bottom.");
	int left = IO::CaptureInt();
	int right = IO::CaptureInt();
	int top = IO::CaptureInt();
	int bottom = IO::CaptureInt();

	IO::ClearConsole();
	IO::DisplayMessage("Loading...");
	IO::NewLine();

	// Grab all the filepaths for images in the buffer
	auto imagePaths = IO::GetFilesInDir(inDir);

	// Grab all files paths, if none, close
	unsigned int imageCount = (unsigned int)imagePaths->size();
	if (imageCount <= 0)
	{
		IO::DisplayMessage("No images found at ", false);
		IO::DisplayMessage(outDir);
		IO::WaitForUser();
		return 1;
	}

	Image currentImage;
	// Load, process and save image then delete
	for (unsigned int i = 0; i < imageCount; i++)
	{
		// Create an image using the path at 'i'
		currentImage = Image((*imagePaths)[i]);
		if (currentImage.Trim(left, right, top, bottom))
		{
			currentImage.Write(outDir);
			currentImage.Destroy();
		}
	}

	// Signal complete and wait for user to close
	IO::NewLine();
	IO::DisplayMessage("Complete");
	IO::WaitForUser();
}
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <iostream>

Image::Image() : m_isValid(false), m_selfAlloc(false), m_height(0), m_imageData(nullptr), m_width(0), m_channels(0)
{
}

Image::Image(const std::string& a_filePath) : m_isValid(false), m_selfAlloc(false), m_height(0), m_imageData(nullptr), m_width(0), m_channels(0)
{
	LoadImage(a_filePath);
}

Image::~Image()
{

}

void Image::Load(const std::string& a_imagePath)
{
	LoadImage(a_imagePath);
}

bool Image::Trim(unsigned int a_fromLeft, unsigned int a_fromRight, unsigned int a_fromTop, unsigned int a_fromBottom)
{
	if (!m_isValid)
	{
		std::cout << "Image " << m_filePath << "is invalid\n";
		return false;
	}
	int newWidth = (m_width - a_fromLeft) - a_fromRight;
	int newHeight = (m_height - a_fromTop) - a_fromBottom;
	int newSize = (newWidth * newHeight) * m_channels;
	unsigned char* tempImage = new unsigned char[newSize * sizeof(unsigned char)]; // create pool for new image

	int newY = 0;
	// Iterate of each row and copy
	for (unsigned int y = a_fromTop; y < m_height - a_fromBottom; y++)
	{
		memcpy(&tempImage[(newWidth * m_channels) * newY], &m_imageData[((m_width * m_channels) * y) + (a_fromLeft * m_channels)], (size_t)(newWidth * m_channels));
		newY++;
	}

	// Mark allocation as ours and free the old image to set edited
	Unload();
	m_selfAlloc = true;
	m_isValid = true;
	m_width = newWidth;
	m_height = newHeight;
	m_imageData = tempImage;
	return true;
}

void Image::Write(const std::string& a_fileDir)
{
	if (!m_isValid)
	{
		return;
	}
	stbi_write_png((a_fileDir + m_fileName).c_str(), m_width, m_height, m_channels, m_imageData, m_width * m_channels);
}

void Image::Destroy()
{
	Unload();
}

void Image::LoadImage(const std::string& a_imagePath)
{
	Unload();

	// Load image
	m_imageData = stbi_load(a_imagePath.c_str(), &m_width, &m_height, &m_channels, 0);
	if (m_imageData)
	{
		std::cout << "Loaded image at: " << a_imagePath << std::endl;
		m_isValid = true;
		m_selfAlloc = false;
		m_filePath = a_imagePath;
		size_t last = a_imagePath.find_last_of("\\/");
		m_fileName = a_imagePath.substr(last, a_imagePath.size() - last + 1);
	}
	else
	{
		std::cout << "Failed to load image at: " << a_imagePath << std::endl;
	}
}

void Image::Unload()
{
	if (m_isValid && !m_selfAlloc)
	{
		stbi_image_free(m_imageData);
	}
	else if (m_isValid && m_selfAlloc)
	{
		delete[] m_imageData;
	}
	m_isValid = false;
}
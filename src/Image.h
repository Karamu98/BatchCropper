#pragma once

#include <string>

class Image
{
public:
	Image();
	Image(const std::string& a_filePath);
	~Image();

	void Load(const std::string& a_imagePath);
	bool Trim(unsigned int a_fromLeft, unsigned int a_fromRight, unsigned int a_fromTop, unsigned int a_fromBottom);
	void Write(const std::string& a_fileDir);
	void Destroy();
private:
	void LoadImage(const std::string& a_imagePath);
	void Unload();

private:
	std::string m_filePath, m_fileName;
	int m_width, m_height, m_channels;
	unsigned char* m_imageData;
	bool m_isValid, m_selfAlloc;

};

// TODO: Create a static pool for loaded images and pool for edited image
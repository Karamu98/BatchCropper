workspace "BatchCropper"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["stb"] = "deps/stb"

project "BatchCropper"
	kind "ConsoleApp"
	location "BatchCropper"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/" .. outputdir .. "/obj/%{prj.name}")

	files
	{
		"BatchCropper/src/**.h", 
		"BatchCropper/src/**.c", 
		"BatchCropper/src/**.hpp", 
		"BatchCropper/src/**.cpp" 
	}

	includedirs
	{
		"%{IncludeDir.stb}"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
  
	 filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
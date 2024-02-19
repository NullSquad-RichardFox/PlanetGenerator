project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "off"
    
    targetdir ("Binaries/" .. outputdir)
    objdir ("Intermediate/" .. outputdir)

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }